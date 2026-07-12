#pragma once

#include "../Includes.h"
#include "../Core/DataTypes.h"

namespace Utility
{
	class RadianceFieldsUtility
	{
	public:
		template<int BasisSize>
		inline static void CopySphericalHarmonics(const float* sourceData, float* destinationData)
		{
			std::copy(sourceData, sourceData + BasisSize, destinationData);
		};

		inline static float4x4 BuildViewMatrix(const float3& position, const float3& direction, const float3& upVector);

		inline static void ThrowRunTimeError(const char* message,
			const std::source_location location = std::source_location::current());
	};
}
