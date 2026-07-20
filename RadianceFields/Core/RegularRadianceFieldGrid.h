#pragma once

#include "../Includes.h"
#include "Cell.h"
#include "GridInfo.h"
#include "IRadianceFieldGrid.h"

namespace Core
{
	class RegularRadianceFieldGrid final : public IRadianceFieldGrid
	{
	public:
		RegularRadianceFieldGrid();
		RegularRadianceFieldGrid(const std::vector<Cell>& rawData, const GridInfo& gridIndo);

		~RegularRadianceFieldGrid() override;

		float SampleDensity(const Ray& ray) override;
		float3 SampleColor(const Ray& ray) override;

	private:
		std::vector<float> densities;
		std::vector<float> rHarmonics;
		std::vector<float> gHarmonics;
		std::vector<float> bHarmonics;

		GridInfo _gridIndo;
	};
}
