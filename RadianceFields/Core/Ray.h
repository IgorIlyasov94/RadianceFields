#pragma once

#include "../Includes.h"
#include "../Utility/RadianceFieldsUtility.h"
#include "DataTypes.h"
#include "Viewport.h"
#include "Math.h"

namespace Core
{
	struct Ray
	{
	public:
		float3 origin;
		float3 direction;

		constexpr Ray()
			: origin{}, direction{}
		{

		}

		constexpr Ray(float3 _origin, float3 _direction)
			: origin(_origin), direction(_direction)
		{

		}

		inline static Ray Build(uint32_t rayIndex, float3 origin, const Viewport& viewport, const float4x4& unprojectionMatrix)
		{
			uint2 ray2DIndex = Utility::RadianceFieldsUtility::Get2DIndex(rayIndex, viewport.Size.x);

			float4 clipPosition = float4((ray2DIndex.x * 2.0f + 1.0f) / viewport.Size.x - 1.0f,
				1.0f - (ray2DIndex.y * 2.0f + 1.0f) / viewport.Size.y,
				0.0f,
				1.0f);

			float4 worldCoord = Math::Mul(unprojectionMatrix, clipPosition);
			worldCoord.x /= worldCoord.w;
			worldCoord.y /= worldCoord.w;
			worldCoord.z /= worldCoord.w;

			Ray ray = Ray(origin, Math::Normalize(float3(worldCoord.x, worldCoord.y, worldCoord.z) - origin));

			return ray;
		}
	};
}
