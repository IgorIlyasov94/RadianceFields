#include "RegularRadianceFieldGrid.h"
#include "../Utility/RadianceFieldsUtility.h"

using namespace Utility;

Core::RegularRadianceFieldGrid::RegularRadianceFieldGrid()
{

}

Core::RegularRadianceFieldGrid::RegularRadianceFieldGrid(const std::vector<Cell>& data, const GridInfo& gridIndo)
	: _gridIndo(gridIndo)
{
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

float Core::RegularRadianceFieldGrid::SampleDensity(const Ray& ray)
{
	return 0.0f;
}

float3 Core::RegularRadianceFieldGrid::SampleColor(const Ray& ray)
{
	return {};
}
