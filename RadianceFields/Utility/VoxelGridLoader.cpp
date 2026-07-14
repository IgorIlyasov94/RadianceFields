#include "VoxelGridLoader.h"

void Utility::VoxelGridLoader::LoadGrid(std::filesystem::path path, Core::GridInfo& info, std::vector<Core::Cell>& grid)
{
	std::ifstream gridFile(path, std::ios::binary);

	gridFile.read(reinterpret_cast<char*>(&info), sizeof(Core::GridInfo));

	size_t cellNumber = static_cast<size_t>(info.GridSize.x) * info.GridSize.y * info.GridSize.z;
	grid.resize(cellNumber);

	size_t dataSize = cellNumber * sizeof(Core::Cell);
	gridFile.read(reinterpret_cast<char*>(grid.data()), dataSize);
}
