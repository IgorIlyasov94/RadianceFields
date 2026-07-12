#include "Math.h"

inline float3 Core::Math::Normalize(const float3& vector0) noexcept
{
	float length = Length(vector0);
	float3 result = vector0 / length;

	return result;
}

inline float Core::Math::Dot(const float3& vector0, const float3& vector1) noexcept
{
	float result = vector0.x * vector1.x + vector0.y * vector1.y + vector0.z * vector1.z;

	return result;
}

inline float Core::Math::Length(const float3& vector0) noexcept
{
	float result = std::sqrt(Dot(vector0, vector0));

	return result;
}
