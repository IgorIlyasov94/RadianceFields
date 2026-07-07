#include "RegularRadianceFieldGrid.h"
#include "../Utility/RadianceFieldsUtility.h"

using namespace Utility;

Core::RegularRadianceFieldGrid::RegularRadianceFieldGrid()
{

}

Core::RegularRadianceFieldGrid::RegularRadianceFieldGrid(const std::vector<Cell>& data)
{
	const size_t cellArraySize = data.size();
	const size_t shArraySize = cellArraySize * Cell::SH_WIDTH;

	densities.resize(cellArraySize);
	sh_r.resize(shArraySize);
	sh_g.resize(shArraySize);
	sh_b.resize(shArraySize);

	for (size_t cellIndex = 0u; cellIndex < cellArraySize; cellIndex++)
	{
		const Cell& cell = data[cellIndex];

		densities[cellIndex] = cell.density;
		RadianceFieldsUtility::CopySphericalHarmonics<Cell::SH_WIDTH>(&cell.sh_r[0], &sh_r[cellIndex * Cell::SH_WIDTH]);
		RadianceFieldsUtility::CopySphericalHarmonics<Cell::SH_WIDTH>(&cell.sh_g[0], &sh_g[cellIndex * Cell::SH_WIDTH]);
		RadianceFieldsUtility::CopySphericalHarmonics<Cell::SH_WIDTH>(&cell.sh_b[0], &sh_b[cellIndex * Cell::SH_WIDTH]);
	}
}

Core::RegularRadianceFieldGrid::~RegularRadianceFieldGrid()
{
	densities.clear();
	densities.shrink_to_fit();
	sh_r.clear();
	sh_r.shrink_to_fit();
	sh_g.clear();
	sh_g.shrink_to_fit();
	sh_b.clear();
	sh_b.shrink_to_fit();
}
