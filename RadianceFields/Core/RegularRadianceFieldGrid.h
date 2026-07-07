#pragma once

#include "../Includes.h"
#include "Cell.h"

namespace Core
{
	class RegularRadianceFieldGrid
	{
	public:
		RegularRadianceFieldGrid();
		RegularRadianceFieldGrid(const std::vector<Cell>& data);

		~RegularRadianceFieldGrid();

	private:
		std::vector<float> densities;
		std::vector<float> sh_r;
		std::vector<float> sh_g;
		std::vector<float> sh_b;
	};
}
