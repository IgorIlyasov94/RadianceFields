#pragma once

#include "../Includes.h"
#include "Float3Hasher.h"
#include "Cell.h"
#include "CellChunkView.h"

namespace Core
{
	class HashRadianceFieldGrid
	{
	public:
		HashRadianceFieldGrid();
		HashRadianceFieldGrid(const std::vector<Cell>& cells);

		~HashRadianceFieldGrid();

	private:
		inline uint32_t GetLinearIndex(const uint3& chunkCoord) const noexcept;

		std::vector<float> densities;
		std::vector<float> rHarmonics;
		std::vector<float> gHarmonics;
		std::vector<float> bHarmonics;

		std::unordered_map<CellChunkView, uint64_t, Float3Hasher> chunkIndices;
	};
}
