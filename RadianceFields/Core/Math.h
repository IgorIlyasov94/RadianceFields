#pragma once

#include "../Includes.h"
#include "DataTypes.h"

namespace Core
{
	class Math
	{
	public:
		inline static float3 Normalize(const float3& vector0) noexcept;
		inline static float Dot(const float3& vector0, const float3& vector1) noexcept;
		inline static float Length(const float3& vector0) noexcept;
	};
}
