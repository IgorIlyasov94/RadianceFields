#pragma once

#include "../Includes.h"
#include "DataTypes.h"

namespace Core
{
	class Float3Hasher
	{
	public:
		static constexpr uint32_t GRID_STANDARD_SIZE = 256u;

		static constexpr uint64_t HASH_COEFF0 = 73856093;
		static constexpr uint64_t HASH_COEFF1 = 19349663;
		static constexpr uint64_t HASH_COEFF2 = 83492791;

		uint64_t operator()(const float3& value)
		{
			uint64_t hash = static_cast<uint64_t>(std::floor(value.x / GRID_STANDARD_SIZE)) * HASH_COEFF0;
			hash ^= static_cast<uint64_t>(std::floor(value.y / GRID_STANDARD_SIZE)) * HASH_COEFF1;
			hash ^= static_cast<uint64_t>(std::floor(value.z / GRID_STANDARD_SIZE)) * HASH_COEFF2;

            return static_cast<size_t>(hash);
		}
	};
}
