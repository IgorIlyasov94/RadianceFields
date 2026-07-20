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

		Viewport()
			: Size{}, ZNear{}, ZFar{}
		{

		}

		Viewport(uint2 size, float zNear, float zFar)
			: Size(size), ZNear(zNear), ZFar(zFar)
		{

		}
	};
}
