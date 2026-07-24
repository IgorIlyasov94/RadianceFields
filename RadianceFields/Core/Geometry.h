#pragma once

#include "../Includes.h"
#include "DataTypes.h"
#include "Math.h"
#include "Ray.h"
#include "BoundingBox.h"

namespace Core
{
	class Geometry
	{
	public:
		inline constexpr static bool RayBoxIntersection(const Ray& ray, const BoundingBox& box,
			float3& intersectionPoint0, float3& intersectionPoint1) noexcept
		{
			float3 invDirection = 1.0f / ray.Direction;
			float3 t0 = (box.Min - ray.Origin) * invDirection;
			float3 t1 = (box.Max - ray.Origin) * invDirection;

			float3 minTv = Math::Min(t0, t1);
			float3 maxTv = Math::Max(t0, t1);

			float minT = minTv.x < minTv.y ? minTv.x : minTv.y;
			minT = minT < minTv.z ? minT : minTv.z;

			float maxT = maxTv.x > maxTv.y ? maxTv.x : maxTv.y;
			maxT = maxT > maxTv.z ? maxT : maxTv.z;

			bool hasIntersection = (minT <= maxT) && (maxT >= 0.0f);
			intersectionPoint0 = ray.Origin + ray.Direction * minT;
			intersectionPoint1 = ray.Origin + ray.Direction * maxT;

			return hasIntersection;
		}
	};
}
