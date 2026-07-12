#pragma once

#include "../Includes.h"
#include "RegularRadianceFieldGrid.h"
#include "HashRadianceFieldGrid.h"

namespace Core
{
	class CpuRenderer
	{
	public:
		CpuRenderer();
		~CpuRenderer();

		void RenderVoxels();

	private:
	};
}
