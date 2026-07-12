#pragma once

#include "../Includes.h"
#include "DataTypes.h"

namespace Core
{
	struct Viewport
	{
	public:
		uint2 size;
		float zNear;
		float zFar;
	};
}
