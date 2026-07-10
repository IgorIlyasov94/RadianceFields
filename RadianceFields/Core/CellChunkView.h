#pragma once

#include "../Includes.h"
#include "Cell.h"

namespace Core
{
	struct CellChunkView
	{
	public:
		static constexpr uint32_t CHUNK_PADDING = 2u;

		static constexpr uint32_t CHUNK_SIZE_X = 8u;
		static constexpr uint32_t CHUNK_SIZE_Y = 8u;
		static constexpr uint32_t CHUNK_SIZE_Z = 8u;

		static constexpr uint32_t CHUNK_PADDED_SIZE_X = CHUNK_SIZE_X + CHUNK_PADDING;
		static constexpr uint32_t CHUNK_PADDED_SIZE_Y = CHUNK_SIZE_Y + CHUNK_PADDING;
		static constexpr uint32_t CHUNK_PADDED_SIZE_Z = CHUNK_SIZE_Z + CHUNK_PADDING;

		static constexpr uint32_t CHUNK_SIZE = CHUNK_PADDED_SIZE_X * CHUNK_PADDED_SIZE_Y * CHUNK_PADDED_SIZE_Z;
		static constexpr uint32_t CHUNK_SH_SIZE = CHUNK_SIZE * Cell::SH_WIDTH;

		float* densities;
		float* sh_r;
		float* sh_g;
		float* sh_b;
	};
}
