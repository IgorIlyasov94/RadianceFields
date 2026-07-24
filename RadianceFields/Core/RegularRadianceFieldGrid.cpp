#include "RegularRadianceFieldGrid.h"
#include "Geometry.h"

using namespace Utility;

Core::RegularRadianceFieldGrid::RegularRadianceFieldGrid()
	: _gridIndo{}, bounds{}
{

}

Core::RegularRadianceFieldGrid::RegularRadianceFieldGrid(const std::vector<Cell>& data, const GridInfo& gridIndo)
	: _gridIndo(gridIndo)
{
	float3 boundsExtents = (static_cast<float3>(gridIndo.GridSize) * gridIndo.VoxelSize) * 0.5f;
	bounds = BoundingBox(gridIndo.Origin - boundsExtents, gridIndo.Origin + boundsExtents);

	const size_t cellArraySize = data.size();
	const size_t shArraySize = cellArraySize * Cell::SH_WIDTH;

	densities.resize(cellArraySize);
	rHarmonics.resize(shArraySize);
	gHarmonics.resize(shArraySize);
	bHarmonics.resize(shArraySize);

	for (size_t cellIndex = 0u; cellIndex < cellArraySize; cellIndex++)
	{
		const Cell& cell = data[cellIndex];

		densities[cellIndex] = cell.density;
		RadianceFieldsUtility::CopySphericalHarmonics<Cell::SH_WIDTH>(&cell.sh_r[0], &rHarmonics[cellIndex * Cell::SH_WIDTH]);
		RadianceFieldsUtility::CopySphericalHarmonics<Cell::SH_WIDTH>(&cell.sh_g[0], &gHarmonics[cellIndex * Cell::SH_WIDTH]);
		RadianceFieldsUtility::CopySphericalHarmonics<Cell::SH_WIDTH>(&cell.sh_b[0], &bHarmonics[cellIndex * Cell::SH_WIDTH]);
	}
}

Core::RegularRadianceFieldGrid::~RegularRadianceFieldGrid()
{
	densities.clear();
	densities.shrink_to_fit();
	rHarmonics.clear();
	rHarmonics.shrink_to_fit();
	gHarmonics.clear();
	gHarmonics.shrink_to_fit();
	bHarmonics.clear();
	bHarmonics.shrink_to_fit();
}

float4 Core::RegularRadianceFieldGrid::Sample(const Ray& ray, FilterMode filterMode, SampleMode sampleMode)
{
	float3 intersectionPoint0;
	float3 intersectionPoint1;
	bool hasHit = Geometry::RayBoxIntersection(ray, bounds, intersectionPoint0, intersectionPoint1);

	float4 result = float4(0.0f, 0.0f, 0.0f, 0.0f);

	if (!hasHit)
	{
		return result;
	}

	float3 rayStep = ray.Direction / static_cast<float3>(_gridIndo.GridSize);
	float rayStepLength = Math::Length(rayStep);
	uint32_t stepNumber = static_cast<uint32_t>(std::floor(Math::Length(intersectionPoint1 - intersectionPoint0) / rayStepLength));
	
	if (filterMode == FilterMode::POINT)
	{
		if (sampleMode == SampleMode::DENSITY)
		{
			result = Sample<FilterMode::POINT, SampleMode::DENSITY>(intersectionPoint0, rayStepLength, ray.Direction, rayStep, stepNumber);
		}
		else
		{
			result = Sample<FilterMode::POINT, SampleMode::COLOR>(intersectionPoint0, rayStepLength, ray.Direction, rayStep, stepNumber);
		}
	}
	else
	{
		if (sampleMode == SampleMode::DENSITY)
		{
			result = Sample<FilterMode::LINEAR, SampleMode::DENSITY>(intersectionPoint0, rayStepLength, ray.Direction, rayStep, stepNumber);
		}
		else
		{
			result = Sample<FilterMode::LINEAR, SampleMode::COLOR>(intersectionPoint0, rayStepLength, ray.Direction, rayStep, stepNumber);
		}
	}

	return result;
}

inline float Core::RegularRadianceFieldGrid::LerpDensities(const uint4& indices0, const uint4& indices1,
	const float3& lerpCoeff)
{
	float d00 = Math::Lerp(densities[indices0.x], densities[indices0.y], lerpCoeff.z);
	float d01 = Math::Lerp(densities[indices0.z], densities[indices0.w], lerpCoeff.z);
	float d10 = Math::Lerp(densities[indices1.x], densities[indices1.y], lerpCoeff.z);
	float d11 = Math::Lerp(densities[indices1.z], densities[indices1.w], lerpCoeff.z);

	float d0 = Math::Lerp(d00, d01, lerpCoeff.y);
	float d1 = Math::Lerp(d10, d11, lerpCoeff.y);

	float density = Math::Lerp(d0, d1, lerpCoeff.x);

	return density;
}

inline float3 Core::RegularRadianceFieldGrid::LerpSphericalHarmonics(const uint4& indices0, const uint4& indices1,
	const float3& lerpCoeff, const float3& rayDirection)
{
	uint4 currentIndices0 = indices0 * Cell::SH_WIDTH;
	uint4 currentIndices1 = indices1 * Cell::SH_WIDTH;

	float3 averageHarmonics[Cell::SH_WIDTH];

	for (uint32_t coeffIndex = 0u; coeffIndex < Cell::SH_WIDTH; coeffIndex++)
	{
		float3 sh00 = Math::Lerp(float3(rHarmonics[currentIndices0.x], gHarmonics[currentIndices0.x], bHarmonics[currentIndices0.x]),
			float3(rHarmonics[currentIndices0.y], gHarmonics[currentIndices0.y], bHarmonics[currentIndices0.y]),
			lerpCoeff.z);
		float3 sh01 = Math::Lerp(float3(rHarmonics[currentIndices0.z], gHarmonics[currentIndices0.z], bHarmonics[currentIndices0.z]),
			float3(rHarmonics[currentIndices0.w], gHarmonics[currentIndices0.w], bHarmonics[currentIndices0.w]),
			lerpCoeff.z);
		float3 sh10 = Math::Lerp(float3(rHarmonics[currentIndices1.x], gHarmonics[currentIndices1.x], bHarmonics[currentIndices1.x]),
			float3(rHarmonics[currentIndices1.y], gHarmonics[currentIndices1.y], bHarmonics[currentIndices1.y]),
			lerpCoeff.z);
		float3 sh11 = Math::Lerp(float3(rHarmonics[currentIndices1.z], gHarmonics[currentIndices1.z], bHarmonics[currentIndices1.z]),
			float3(rHarmonics[currentIndices1.w], gHarmonics[currentIndices1.w], bHarmonics[currentIndices1.w]),
			lerpCoeff.z);

		float3 sh0 = Math::Lerp(sh00, sh01, lerpCoeff.y);
		float3 sh1 = Math::Lerp(sh10, sh11, lerpCoeff.y);

		averageHarmonics[coeffIndex] = Math::Lerp(sh0, sh1, lerpCoeff.x);
	}

	float3 color = Math::EvaluateSH9(averageHarmonics, rayDirection);

	return color;
}
