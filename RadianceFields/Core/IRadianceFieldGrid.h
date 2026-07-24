#pragma once

#include "../Includes.h"
#include "DataTypes.h"
#include "Ray.h"
#include "FilterMode.h"
#include "SampleMode.h"

namespace Core
{
	class IRadianceFieldGrid
	{
	public:
		virtual ~IRadianceFieldGrid() = 0 {};

		virtual float4 Sample(const Ray& ray, FilterMode filterMode, SampleMode sampleMode) = 0;
	};
}
