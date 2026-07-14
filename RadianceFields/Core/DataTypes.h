#pragma once

#include "../Includes.h"

struct vector2
{
};

struct vector3
{
};

struct vector4
{
};

template<typename T>
concept Vector2 = std::derived_from<T, vector2>;

template<typename T>
concept Vector3 = std::derived_from<T, vector3>;

template<typename T>
concept Vector4 = std::derived_from<T, vector4>;

template<typename T>
concept Scalar = std::is_arithmetic_v<T>;

template<typename T>
concept AnyDimensionVector = std::is_arithmetic_v<T> || std::derived_from<T, vector2> || std::derived_from<T, vector3> || std::derived_from<T, vector4>;

struct float2 : public vector2
{
public:
	float x;
	float y;

	constexpr float2()
		: x{}, y{}
	{

	}

	constexpr float2(float _x, float _y)
		: x(_x), y(_y)
	{

	}

	template<Vector2 v2>
	explicit operator v2() const
	{
		v2 p;
		p.x = static_cast<decltype(v2::x)>(x);
		p.y = static_cast<decltype(v2::y)>(y);

		return p;
	}
};

struct float3 : public vector3
{
public:
	float x;
	float y;
	float z;

	constexpr float3()
		: x{}, y{}, z{}
	{

	}

	constexpr float3(float _x, float _y, float _z)
		: x(_x), y(_y), z(_z)
	{

	}

	template<Vector3 v3>
	explicit operator v3() const
	{
		v3 p;
		p.x = static_cast<decltype(v3::x)>(x);
		p.y = static_cast<decltype(v3::y)>(y);
		p.z = static_cast<decltype(v3::z)>(z);

		return p;
	}
};

struct float4 : public vector4
{
public:
	float x;
	float y;
	float z;
	float w;

	constexpr float4()
		: x{}, y{}, z{}, w{}
	{

	}

	constexpr float4(float _x, float _y, float _z, float _w)
		: x(_x), y(_y), z(_z), w(_w)
	{

	}

	template<Vector4 v4>
	explicit operator v4() const
	{
		v4 p;
		p.x = static_cast<decltype(v4::x)>(x);
		p.y = static_cast<decltype(v4::y)>(y);
		p.z = static_cast<decltype(v4::z)>(z);
		p.w = static_cast<decltype(v4::w)>(w);

		return p;
	}
};

struct uint2
{
public:
	uint32_t x;
	uint32_t y;

	template<Vector2 v2>
	explicit operator v2() const
	{
		v2 p;
		p.x = static_cast<decltype(v2::x)>(x);
		p.y = static_cast<decltype(v2::y)>(y);

		return p;
	}
};

struct uint3
{
public:
	uint32_t x;
	uint32_t y;
	uint32_t z;

	template<Vector3 v3>
	explicit operator v3() const
	{
		v3 p;
		p.x = static_cast<decltype(v3::x)>(x);
		p.y = static_cast<decltype(v3::y)>(y);
		p.z = static_cast<decltype(v3::z)>(z);

		return p;
	}
};

struct uint4
{
public:
	uint32_t x;
	uint32_t y;
	uint32_t z;
	uint32_t w;

	template<Vector4 v4>
	explicit operator v4() const
	{
		v4 p;
		p.x = static_cast<decltype(v4::x)>(x);
		p.y = static_cast<decltype(v4::y)>(y);
		p.z = static_cast<decltype(v4::z)>(z);
		p.w = static_cast<decltype(v4::w)>(w);

		return p;
	}
};

struct float4x4
{
public:
	float4 c0;
	float4 c1;
	float4 c2;
	float4 c3;

	constexpr float4x4()
		: c0{}, c1{}, c2{}, c3{}
	{

	}

	constexpr float4x4(float4 _c0, float4 _c1, float4 _c2, float4 _c3)
		: c0(_c0), c1(_c1), c2(_c2), c3(_c3)
	{

	}
};

template<Vector2 v2>
v2& operator+=(v2& p0, const v2& p1) noexcept
{
	p0.x = static_cast<decltype(v2::x)>(p0.x + p1.x);
	p0.y = static_cast<decltype(v2::y)>(p0.y + p1.y);

	return p0;
}

template<Vector2 v2>
v2 operator+(const v2& p0, const v2& p1) noexcept
{
	v2 p = p0;
	p += p1;

	return p;
}

template<Vector2 v2>
v2& operator-=(v2& p0, const v2& p1) noexcept
{
	p0.x = static_cast<decltype(v2::x)>(p0.x - p1.x);
	p0.y = static_cast<decltype(v2::y)>(p0.y - p1.y);

	return p0;
}

template<Vector2 v2>
v2 operator-(const v2& p0, const v2& p1) noexcept
{
	v2 p = p0;
	p -= p1;

	return p;
}

template<Vector2 v2>
v2& operator*=(v2& p0, const v2& p1) noexcept
{
	p0.x = static_cast<decltype(v2::x)>(p0.x * p1.x);
	p0.y = static_cast<decltype(v2::y)>(p0.y * p1.y);

	return p0;
}

template<Vector2 v2>
v2 operator*(const v2& p0, const v2& p1) noexcept
{
	v2 p = p0;
	p *= p1;

	return p;
}

template<Vector2 v2, Scalar v1>
v2& operator*=(v2& p0, const v1& p1) noexcept
{
	p0.x = static_cast<decltype(v2::x)>(p0.x * p1);
	p0.y = static_cast<decltype(v2::y)>(p0.y * p1);

	return p0;
}

template<Vector2 v2, Scalar v1>
v2 operator*(const v2& p0, const v1& p1) noexcept
{
	v2 p = p0;
	p *= p1;

	return p;
}

template<Vector2 v2, Scalar v1>
v2 operator*(const v1& p0, const v2& p1) noexcept
{
	v2 p = p1;
	p *= p0;

	return p;
}

template<Vector2 v2>
v2& operator/=(v2& p0, const v2& p1) noexcept
{
	p0.x = static_cast<decltype(v2::x)>(p0.x / p1.x);
	p0.y = static_cast<decltype(v2::y)>(p0.y / p1.y);

	return p0;
}

template<Vector2 v2, Scalar v1>
v2& operator/=(v2& p0, const v1& p1) noexcept
{
	p0.x = static_cast<decltype(v2::x)>(p0.x / p1);
	p0.y = static_cast<decltype(v2::y)>(p0.y / p1);

	return p0;
}

template<Vector2 v2>
v2 operator/(const v2& p0, const v2& p1) noexcept
{
	v2 p = p0;
	p /= p1;

	return p;
}

template<Vector2 v2, Scalar v1>
v2 operator/(const v2& p0, const v1& p1) noexcept
{
	v2 p = p0;
	p /= p1;

	return p;
}

template<Vector2 v2, Scalar v1>
v2 operator/(const v1& p0, const v2& p1) noexcept
{
	v2 p;
	p.x = static_cast<decltype(v2::x)>(p0 / p1.x);
	p.y = static_cast<decltype(v2::y)>(p0 / p1.y);

	return p;
}

template<Vector2 v2>
bool operator==(const v2& left, const v2& right)
{
	if constexpr (std::is_floating_point_v<decltype(v2::x)>)
	{
		if (!CompareFloats(left.x, right.x) ||
			!CompareFloats(left.y, right.y))
			false;
	}
	else
	{
		if (left.x != right.x ||
			left.y != right.y)
			false;
	}

	return true;
}

template<Vector2 v2>
bool operator!=(const v2& left, const v2& right)
{
	return !(left == right);
}

template<Vector3 v3>
v3& operator+=(v3& p0, const v3& p1) noexcept
{
	p0.x = static_cast<decltype(v3::x)>(p0.x + p1.x);
	p0.y = static_cast<decltype(v3::y)>(p0.y + p1.y);
	p0.z = static_cast<decltype(v3::z)>(p0.z + p1.z);

	return p0;
}

template<Vector3 v3>
v3 operator+(const v3& p0, const v3& p1) noexcept
{
	v3 p = p0;
	p += p1;

	return p;
}

template<Vector3 v3>
v3& operator-=(v3& p0, const v3& p1) noexcept
{
	p0.x = static_cast<decltype(v3::x)>(p0.x - p1.x);
	p0.y = static_cast<decltype(v3::y)>(p0.y - p1.y);
	p0.z = static_cast<decltype(v3::z)>(p0.z - p1.z);

	return p0;
}

template<Vector3 v3>
v3 operator-(const v3& p0, const v3& p1) noexcept
{
	v3 p = p0;
	p -= p1;

	return p;
}

template<Vector3 v3>
v3& operator*=(v3& p0, const v3& p1) noexcept
{
	p0.x = static_cast<decltype(v3::x)>(p0.x * p1.x);
	p0.y = static_cast<decltype(v3::y)>(p0.y * p1.y);
	p0.z = static_cast<decltype(v3::z)>(p0.z * p1.z);

	return p0;
}

template<Vector3 v3>
v3 operator*(const v3& p0, const v3& p1) noexcept
{
	v3 p = p0;
	p *= p1;

	return p;
}

template<Vector3 v3, Scalar v1>
v3& operator*=(v3& p0, const v1& p1) noexcept
{
	p0.x = static_cast<decltype(v3::x)>(p0.x * p1);
	p0.y = static_cast<decltype(v3::y)>(p0.y * p1);
	p0.z = static_cast<decltype(v3::z)>(p0.z * p1);

	return p0;
}

template<Vector3 v3, Scalar v1>
v3 operator*(const v3& p0, const v1& p1) noexcept
{
	v3 p = p0;
	p *= p1;

	return p;
}

template<Vector3 v3, Scalar v1>
v3 operator*(const v1& p0, const v3& p1) noexcept
{
	v3 p = p1;
	p *= p0;

	return p;
}

template<Vector3 v3>
v3& operator/=(v3& p0, const v3& p1) noexcept
{
	p0.x = static_cast<decltype(v3::x)>(p0.x / p1.x);
	p0.y = static_cast<decltype(v3::y)>(p0.y / p1.y);
	p0.z = static_cast<decltype(v3::z)>(p0.z / p1.z);

	return p0;
}

template<Vector3 v3, Scalar v1>
v3& operator/=(v3& p0, const v1& p1) noexcept
{
	p0.x = static_cast<decltype(v3::x)>(p0.x / p1);
	p0.y = static_cast<decltype(v3::y)>(p0.y / p1);
	p0.z = static_cast<decltype(v3::z)>(p0.z / p1);

	return p0;
}

template<Vector3 v3>
v3 operator/(const v3& p0, const v3& p1) noexcept
{
	v3 p = p0;
	p /= p1;

	return p;
}

template<Vector3 v3, Scalar v1>
v3 operator/(const v3& p0, const v1& p1) noexcept
{
	v3 p = p0;
	p /= p1;

	return p;
}

template<Vector3 v3, Scalar v1>
v3 operator/(const v1& p0, const v3& p1) noexcept
{
	v3 p;
	p.x = static_cast<decltype(v3::x)>(p0 / p1.x);
	p.y = static_cast<decltype(v3::y)>(p0 / p1.y);
	p.z = static_cast<decltype(v3::z)>(p0 / p1.z);

	return p;
}

template<Vector3 v3>
bool operator==(const v3& left, const v3& right)
{
	if constexpr (std::is_floating_point_v<decltype(v3::x)>)
	{
		if (!CompareFloats(left.x, right.x) ||
			!CompareFloats(left.y, right.y) ||
			!CompareFloats(left.z, right.z))
			false;
	}
	else
	{
		if (left.x != right.x ||
			left.y != right.y ||
			left.z != right.z)
			false;
	}

	return true;
}

template<Vector3 v3>
bool operator!=(const v3& left, const v3& right)
{
	return !(left == right);
}

template<Vector4 v4>
bool operator==(const v4& left, const v4& right)
{
	if constexpr (std::is_floating_point_v<decltype(v4::x)>)
	{
		if (!CompareFloats(left.x, right.x) ||
			!CompareFloats(left.y, right.y) ||
			!CompareFloats(left.z, right.z) ||
			!CompareFloats(left.w, right.w))
			false;
	}
	else
	{
		if (left.x != right.x ||
			left.y != right.y ||
			left.z != right.z ||
			left.w != right.w)
			false;
	}

	return true;
}

template<Vector4 v4>
bool operator!=(const v4& left, const v4& right)
{
	return !(left == right);
}
