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
		};
	};
}
