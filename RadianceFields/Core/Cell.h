#pragma once

#include "../Includes.h"

namespace Core
{
	struct Cell
	{
	public:
		static constexpr uint32_t SH_WIDTH = 9u;

		float density;
		float sh_r[SH_WIDTH];
		float sh_g[SH_WIDTH];
		float sh_b[SH_WIDTH];
	};
}
