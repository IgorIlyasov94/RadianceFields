#pragma once

#include "../Includes.h"
#include "Float3Hasher.h"
#include "Cell.h"
#include "CellChunkView.h"
#include "IRadianceFieldGrid.h"

namespace Core
{
	class HashRadianceFieldGrid final : public IRadianceFieldGrid
	{
	public:
		HashRadianceFieldGrid();
		HashRadianceFieldGrid(const std::vector<Cell>& cells);

		~HashRadianceFieldGrid() override;

		float SampleDensity(const Ray& ray) override;
		float3 SampleColor(const Ray& ray) override;

	private:
		inline uint32_t GetLinearIndex(const uint3& chunkCoord) const noexcept;

		std::vector<float> densities;
		std::vector<float> rHarmonics;
		std::vector<float> gHarmonics;
		std::vector<float> bHarmonics;

		std::unordered_map<float3, CellChunkView, Float3Hasher> chunkIndices;
	};
}
