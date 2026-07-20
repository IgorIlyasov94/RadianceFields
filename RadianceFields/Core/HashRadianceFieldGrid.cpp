#include "HashRadianceFieldGrid.h"

Core::HashRadianceFieldGrid::HashRadianceFieldGrid()
{

}

Core::HashRadianceFieldGrid::HashRadianceFieldGrid(const std::vector<Cell>& cells)
{

}

Core::HashRadianceFieldGrid::~HashRadianceFieldGrid()
{
	chunkIndices.clear();
}

float Core::HashRadianceFieldGrid::SampleDensity(const Ray& ray)
{
	return 0.0f;
}

float3 Core::HashRadianceFieldGrid::SampleColor(const Ray& ray)
{
	return {};
}

inline uint32_t Core::HashRadianceFieldGrid::GetLinearIndex(const uint3& chunkCoord) const noexcept
{
	uint32_t index = chunkCoord.x;
	index += chunkCoord.y * CellChunkView::CHUNK_PADDED_SIZE_X;
	index += chunkCoord.z * (CellChunkView::CHUNK_PADDED_SIZE_X * CellChunkView::CHUNK_PADDED_SIZE_Y);

	return index;
}
