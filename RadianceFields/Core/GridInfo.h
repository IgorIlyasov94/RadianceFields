#pragma once

#include "../Includes.h"
#include "DataTypes.h"

namespace Core
{
	struct GridInfo
	{
	public:
		uint3 GridSize;
		float3 VoxelSize;
		float3 Origin;
		float DensityScale;
	};
}
