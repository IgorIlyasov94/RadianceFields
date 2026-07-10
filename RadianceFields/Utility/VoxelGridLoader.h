#pragma once

#include "../Includes.h"
#include "../Core/Cell.h"

namespace Utility
{
	class VoxelGridLoader
	{
	public:
		static void LoadGrid(std::filesystem::path path, std::vector<Core::Cell>& grid);
	private:

	};
}
