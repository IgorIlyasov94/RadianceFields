#pragma once

#include "../Includes.h"
#include "../Utility/RadianceFieldsUtility.h"
#include "Cell.h"
#include "GridInfo.h"
#include "FilterMode.h"
#include "SampleMode.h"
#include "BoundingBox.h"
#include "IRadianceFieldGrid.h"

namespace Core
{
	class RegularRadianceFieldGrid final : public IRadianceFieldGrid
	{
	public:
		RegularRadianceFieldGrid();
		RegularRadianceFieldGrid(const std::vector<Cell>& rawData, const GridInfo& gridIndo);

		~RegularRadianceFieldGrid() override;

		float4 Sample(const Ray& ray, FilterMode filterMode, SampleMode sampleMode) override;

	private:
		inline float LerpDensities(const uint4& indices0, const uint4& indices1, const float3& lerpCoeff);
		inline float3 LerpSphericalHarmonics(const uint4& indices0, const uint4& indices1,
			const float3& lerpCoeff, const float3& rayDirection);

		template<FilterMode FMode, SampleMode SMode>
		float4 Sample(const float3& startSamplePosition, float rayStepLength,
			const float3& rayDirection, const float3& rayStep, uint32_t stepNumber)
		{
			float3 samplePosition = startSamplePosition;
			float3 boundsOrigin = bounds.Origin();
			float3 boundsSize = bounds.Size();
			uint3 maxGridIndex = _gridIndo.GridSize - uint3(1u, 1u, 1u);
			uint32_t width = _gridIndo.GridSize.x;
			uint32_t sliceSize = width * _gridIndo.GridSize.y;
			
			float4 result = float4(0.0f, 0.0f, 0.0f, 0.0f);
			float tSum = 0.0f;

			for (uint32_t stepIndex = 0u; stepIndex < stepNumber; stepIndex++)
			{
				float density;
				float3 color;

				float3 clampedPosition = samplePosition - boundsOrigin;
				clampedPosition /= boundsSize;
				clampedPosition = Core::Math::Max(clampedPosition, float3(0.0f, 0.0f, 0.0f));
				clampedPosition *= static_cast<float3>(_gridIndo.GridSize);

				uint3 iMin = static_cast<uint3>(clampedPosition);
				uint4 indices0;
				indices0.x = Utility::RadianceFieldsUtility::Get1DIndex(iMin, width, sliceSize);
				
				if constexpr (FMode == FilterMode::POINT)
				{
					density = densities[indices0.x];

					if constexpr (SMode == SampleMode::COLOR)
					{
						uint32_t shIndex = indices0.x * Cell::SH_WIDTH;

						color.x = Math::EvaluateSH9(&rHarmonics[shIndex], rayDirection);
						color.y = Math::EvaluateSH9(&gHarmonics[shIndex], rayDirection);
						color.z = Math::EvaluateSH9(&bHarmonics[shIndex], rayDirection);
					}
				}
				else
				{
					uint3 iMax = Math::Min(iMin + uint3(1u, 1u, 1u), maxGridIndex);
					uint4 indices1;
					indices0.y = Utility::RadianceFieldsUtility::Get1DIndex(uint3(iMin.x, iMin.y, iMax.z), width, sliceSize);
					indices0.z = Utility::RadianceFieldsUtility::Get1DIndex(uint3(iMin.x, iMax.y, iMin.z), width, sliceSize);
					indices0.w = Utility::RadianceFieldsUtility::Get1DIndex(uint3(iMin.x, iMax.y, iMax.z), width, sliceSize);
					indices1.x = Utility::RadianceFieldsUtility::Get1DIndex(uint3(iMax.x, iMin.y, iMin.z), width, sliceSize);
					indices1.y = Utility::RadianceFieldsUtility::Get1DIndex(uint3(iMax.x, iMin.y, iMax.z), width, sliceSize);
					indices1.z = Utility::RadianceFieldsUtility::Get1DIndex(uint3(iMax.x, iMax.y, iMin.z), width, sliceSize);
					indices1.w = Utility::RadianceFieldsUtility::Get1DIndex(iMax, width, sliceSize);

					float3 lerpCoeff = clampedPosition - samplePosition;
					density = LerpDensities(indices0, indices1, lerpCoeff);

					if constexpr (SMode == SampleMode::COLOR)
					{
						color = LerpSphericalHarmonics(indices0, indices1, lerpCoeff, rayDirection);
					}
				}

				float d_dr = density * rayStepLength;
				float t = std::exp(-tSum);
				float dOpacity = t * (1.0f - std::exp(-d_dr));

				if constexpr (SMode == SampleMode::COLOR)
				{
					result.xyz += dOpacity * color;
				}

				result.w += dOpacity;
				tSum += d_dr;

				samplePosition += rayStep;
			}

			if constexpr (SMode == SampleMode::DENSITY)
			{
				result.x = result.w;
				result.y = result.w;
				result.z = result.w;
			}

			return result;
		}

		std::vector<float> densities;
		std::vector<float> rHarmonics;
		std::vector<float> gHarmonics;
		std::vector<float> bHarmonics;

		GridInfo _gridIndo;
		BoundingBox bounds;
	};
}
