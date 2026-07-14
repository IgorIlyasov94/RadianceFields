#pragma once

#include "../Includes.h"
#include "../Core/Cell.h"
#include "../Core/GridInfo.h"

namespace Utility
{
	class VoxelGridLoader
	{
	public:
		static void LoadGrid(std::filesystem::path path, Core::GridInfo& info, std::vector<Core::Cell>& grid);

	private:
		VoxelGridLoader() = delete;
		VoxelGridLoader(const VoxelGridLoader&) = delete;
		VoxelGridLoader(VoxelGridLoader&&) = delete;
		VoxelGridLoader& operator=(const VoxelGridLoader&) = delete;
		VoxelGridLoader& operator=(VoxelGridLoader&&) = delete;
	};
}
