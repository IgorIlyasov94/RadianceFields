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

		void RenderVoxels(std::vector<uint8_t>& resultImage);

	private:
	};
}
