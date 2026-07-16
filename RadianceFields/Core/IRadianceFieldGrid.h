#pragma once

#include "../Includes.h"
#include "DataTypes.h"
#include "Ray.h"

namespace Core
{
	class IRadianceFieldGrid
	{
	public:
		virtual ~IRadianceFieldGrid() = 0 {};

		virtual float GetVisibleDensity(const Ray& ray) = 0;
		virtual float3 GetVisibleColor(const Ray& ray) = 0;
	};
}
