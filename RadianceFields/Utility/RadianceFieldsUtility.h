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

		inline static void ThrowRunTimeError(const char* message,
			const std::source_location location = std::source_location::current())
		{
			std::stringstream strout;
			strout << "runtime_error in file" << location.file_name();
			strout << ", method " << location.function_name();
			strout << ", line " << location.line() << ": " << message << std::endl;

			throw std::runtime_error(strout.str().c_str());
		}

		inline static uint32_t Get1DIndex(uint2 index, uint32_t width)
		{
			uint32_t index1D = index.y * width + index.x;

			return index1D;
		}

		inline static uint32_t Get1DIndex(uint3 index, uint32_t width, uint32_t sliceSize)
		{
			uint32_t index1D = index.z * sliceSize + index.y * width + index.x;

			return index1D;
		}

		inline static uint2 Get2DIndex(uint32_t index, uint32_t width)
		{
			uint2 index2D{};
			index2D.x = index % width;
			index2D.y = index / width;

			return index2D;
		}

		inline static uint3 Get3DIndex(uint32_t index, uint32_t width, uint32_t sliceSize)
		{
			uint3 index3D{};
			index3D.x = index % width;
			index3D.y = (index % sliceSize) / width;
			index3D.z = index / sliceSize;

			return index3D;
		}
	};
}
