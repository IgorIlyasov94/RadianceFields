#pragma once

#include "../Includes.h"
#include "../Core/DataTypes.h"

namespace Utility
{
	class RadianceFieldsUtility
	{
	private:
		static constexpr uint64_t HASH_COEFF0 = 73856093;
		static constexpr uint64_t HASH_COEFF1 = 19349663;
		static constexpr uint64_t HASH_COEFF2 = 83492791;

	public:
		template<int BasisSize>
		inline static void CopySphericalHarmonics(const float* sourceData, float* destinationData)
		{
			std::copy(sourceData, sourceData + BasisSize, destinationData);
		};
	};
}
