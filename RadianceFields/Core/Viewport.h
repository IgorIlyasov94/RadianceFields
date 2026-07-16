#pragma once

#include "../Includes.h"
#include "DataTypes.h"

namespace Core
{
	struct Viewport
	{
	public:
		uint2 Size;
		float ZNear;
		float ZFar;
	};
}
