#pragma once

#include "../Includes.h"
#include "DataTypes.h"

namespace Core
{
	struct BoundingBox
	{
	public:
		float3 Min;
		float3 Max;

		constexpr BoundingBox()
			: Min{}, Max{}
		{

		}

		constexpr BoundingBox(float3 min, float3 max)
			: Min(min), Max(max)
		{

		}

		constexpr float3 Origin()
		{
			float3 origin = (Min + Max) * 0.5f;

			return origin;
		}

		constexpr float3 Size()
		{
			float3 origin = Max - Min;

			return origin;
		}
	};
}
