#include "RadianceFieldsUtility.h"

inline float4x4 Utility::RadianceFieldsUtility::BuildViewMatrix(const float3& position, const float3& direction, const float3& upVector)
{
	float4x4 viewMatrix;

	return viewMatrix;
}

inline void Utility::RadianceFieldsUtility::ThrowRunTimeError(const char* message, const std::source_location location)
{
	std::stringstream strout;
	strout << "runtime_error in file" << location.file_name();
	strout << ", method " << location.function_name();
	strout << ", line " << location.line() << ": " << message << std::endl;

	throw std::runtime_error(strout.str().c_str());
}
