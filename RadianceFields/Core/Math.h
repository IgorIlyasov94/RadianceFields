#pragma once

#include "../Includes.h"
#include "DataTypes.h"

namespace Core
{
	class Math
	{
	public:
		static constexpr float SH_Ylm_0__0 = 0.5000000000000000f * std::numbers::inv_sqrtpi_v<float>;

		static constexpr float SH_Ylm_1_m1 = 0.8660254037844386f * std::numbers::inv_sqrtpi_v<float>;
		static constexpr float SH_Ylm_1__0 = 0.8660254037844386f * std::numbers::inv_sqrtpi_v<float>;
		static constexpr float SH_Ylm_1__1 = 0.8660254037844386f * std::numbers::inv_sqrtpi_v<float>;

		static constexpr float SH_Ylm_2_m2 = 1.9364916731037084f * std::numbers::inv_sqrtpi_v<float>;
		static constexpr float SH_Ylm_2_m1 = 1.9364916731037084f * std::numbers::inv_sqrtpi_v<float>;
		static constexpr float SH_Ylm_2__0 = 0.5590169943749474f * std::numbers::inv_sqrtpi_v<float>;
		static constexpr float SH_Ylm_2__1 = 1.9364916731037084f * std::numbers::inv_sqrtpi_v<float>;
		static constexpr float SH_Ylm_2__2 = 0.9682458365518542f * std::numbers::inv_sqrtpi_v<float>;

		[[nodiscard]] static constexpr float Lerp(const float& scalar0, const float& scalar1, float t) noexcept
		{
			float result = scalar0 + (scalar1 - scalar0) * t;

			return result;
		}

		[[nodiscard]] static constexpr float3 Lerp(const float3& vector0, const float3& vector1, float t) noexcept
		{
			float3 result = vector0 + (vector1 - vector0) * t;

			return result;
		}

		template<Vector3 T>
		[[nodiscard]] static constexpr T Min(const T& vector0, const T& vector1) noexcept
		{
			T result = T(
				vector0.x < vector1.x ? vector0.x : vector1.x,
				vector0.y < vector1.y ? vector0.y : vector1.y,
				vector0.z < vector1.z ? vector0.z : vector1.z);

			return result;
		}

		template<Vector3 T>
		[[nodiscard]] static constexpr T Max(const T& vector0, const T& vector1) noexcept
		{
			T result = T(
				vector0.x > vector1.x ? vector0.x : vector1.x,
				vector0.y > vector1.y ? vector0.y : vector1.y,
				vector0.z > vector1.z ? vector0.z : vector1.z);

			return result;
		}

		[[nodiscard]] static constexpr float3 Abs(const float3& vector0) noexcept
		{
			float3 result = float3(
				vector0.x < 0.0f ? -vector0.x : vector0.x,
				vector0.y < 0.0f ? -vector0.y : vector0.y,
				vector0.z < 0.0f ? -vector0.z : vector0.z);

			return result;
		}

		[[nodiscard]] static constexpr float Dot(const float3& vector0, const float3& vector1) noexcept
		{
			float result = vector0.x * vector1.x + vector0.y * vector1.y + vector0.z * vector1.z;

			return result;
		}

		[[nodiscard]] static constexpr float Dot(const float4& vector0, const float4& vector1) noexcept
		{
			float result = vector0.x * vector1.x + vector0.y * vector1.y + vector0.z * vector1.z + vector0.w * vector1.w;

			return result;
		}

		[[nodiscard]] inline static float Length(const float3& vector0) noexcept
		{
			float result = std::sqrt(Dot(vector0, vector0));

			return result;
		}

		[[nodiscard]] inline static float3 Normalize(const float3& vector0)
		{
			float length = Length(vector0);
			float3 result = vector0 / length;

			return result;
		}

		[[nodiscard]] inline constexpr static float3 Cross(const float3& vector0, const float3& vector1) noexcept
		{
			float3 result{};
			result.x = vector0.y * vector1.z - vector0.z * vector1.y;
			result.y = vector0.z * vector1.x - vector0.x * vector1.z;
			result.z = vector0.x * vector1.y - vector0.y * vector1.x;

			return result;
		}

		[[nodiscard]] inline constexpr static float4 Mul(const float4x4& matrix, const float4& vector) noexcept
		{
			float4 result{};
			result.x = Dot(matrix.c0, vector);
			result.y = Dot(matrix.c1, vector);
			result.z = Dot(matrix.c2, vector);
			result.w = Dot(matrix.c3, vector);

			return result;
		}

		[[nodiscard]] inline constexpr static float4x4 Mul(const float4x4& matrix0, const float4x4& matrix1) noexcept
		{
			float4x4 result = float4x4(
				float4(
					Dot(float4(matrix0.c0.x, matrix0.c1.x, matrix0.c2.x, matrix0.c3.x), matrix1.c0),
					Dot(float4(matrix0.c0.y, matrix0.c1.y, matrix0.c2.y, matrix0.c3.y), matrix1.c0),
					Dot(float4(matrix0.c0.z, matrix0.c1.z, matrix0.c2.z, matrix0.c3.z), matrix1.c0),
					Dot(float4(matrix0.c0.w, matrix0.c1.w, matrix0.c2.w, matrix0.c3.w), matrix1.c0)),
				float4(
					Dot(float4(matrix0.c0.x, matrix0.c1.x, matrix0.c2.x, matrix0.c3.x), matrix1.c1),
					Dot(float4(matrix0.c0.y, matrix0.c1.y, matrix0.c2.y, matrix0.c3.y), matrix1.c1),
					Dot(float4(matrix0.c0.z, matrix0.c1.z, matrix0.c2.z, matrix0.c3.z), matrix1.c1),
					Dot(float4(matrix0.c0.w, matrix0.c1.w, matrix0.c2.w, matrix0.c3.w), matrix1.c1)),
				float4(
					Dot(float4(matrix0.c0.x, matrix0.c1.x, matrix0.c2.x, matrix0.c3.x), matrix1.c2),
					Dot(float4(matrix0.c0.y, matrix0.c1.y, matrix0.c2.y, matrix0.c3.y), matrix1.c2),
					Dot(float4(matrix0.c0.z, matrix0.c1.z, matrix0.c2.z, matrix0.c3.z), matrix1.c2),
					Dot(float4(matrix0.c0.w, matrix0.c1.w, matrix0.c2.w, matrix0.c3.w), matrix1.c2)),
				float4(
					Dot(float4(matrix0.c0.x, matrix0.c1.x, matrix0.c2.x, matrix0.c3.x), matrix1.c3),
					Dot(float4(matrix0.c0.y, matrix0.c1.y, matrix0.c2.y, matrix0.c3.y), matrix1.c3),
					Dot(float4(matrix0.c0.z, matrix0.c1.z, matrix0.c2.z, matrix0.c3.z), matrix1.c3),
					Dot(float4(matrix0.c0.w, matrix0.c1.w, matrix0.c2.w, matrix0.c3.w), matrix1.c3)));

			return result;
		}

		[[nodiscard]] inline constexpr static float Determinant(const float4x4& matrix) noexcept
		{
			float M0 = matrix.c2.z * matrix.c3.w - matrix.c2.w * matrix.c3.z;
			float M1 = matrix.c1.z * matrix.c3.w - matrix.c1.w * matrix.c3.z;
			float M2 = matrix.c1.z * matrix.c2.w - matrix.c1.w * matrix.c2.z;
			float M3 = matrix.c0.z * matrix.c3.w - matrix.c0.w * matrix.c3.z;
			float M4 = matrix.c0.z * matrix.c2.w - matrix.c0.w * matrix.c2.z;
			float M5 = matrix.c0.z * matrix.c1.w - matrix.c0.w * matrix.c1.z;

			float A0 = matrix.c1.y * M0 - matrix.c2.y * M1 + matrix.c3.y * M2;
			float A1 = matrix.c0.y * M0 - matrix.c2.y * M3 + matrix.c3.y * M4;
			float A2 = matrix.c0.y * M1 - matrix.c1.y * M3 + matrix.c3.y * M5;
			float A3 = matrix.c0.y * M2 - matrix.c1.y * M4 + matrix.c2.y * M5;

			float determinant = matrix.c0.x * A0 - matrix.c1.x * A1 + matrix.c2.x * A2 - matrix.c3.x * A3;

			return determinant;
		}

		inline static bool Inverse(const float4x4& matrix, float4x4& result) noexcept
		{
			float T0 = matrix.c0.x * matrix.c1.y - matrix.c0.y * matrix.c1.x;
			float T1 = matrix.c0.x * matrix.c2.y - matrix.c0.y * matrix.c2.x;
			float T2 = matrix.c0.x * matrix.c3.y - matrix.c0.y * matrix.c3.x;
			float T3 = matrix.c1.x * matrix.c2.y - matrix.c1.y * matrix.c2.x;
			float T4 = matrix.c1.x * matrix.c3.y - matrix.c1.y * matrix.c3.x;
			float T5 = matrix.c2.x * matrix.c3.y - matrix.c2.y * matrix.c3.x;

			float B0 = matrix.c0.z * matrix.c1.w - matrix.c0.w * matrix.c1.z;
			float B1 = matrix.c0.z * matrix.c2.w - matrix.c0.w * matrix.c2.z;
			float B2 = matrix.c0.z * matrix.c3.w - matrix.c0.w * matrix.c3.z;
			float B3 = matrix.c1.z * matrix.c2.w - matrix.c1.w * matrix.c2.z;
			float B4 = matrix.c1.z * matrix.c3.w - matrix.c1.w * matrix.c3.z;
			float B5 = matrix.c2.z * matrix.c3.w - matrix.c2.w * matrix.c3.z;

			float A00 = (matrix.c1.y * B5 - matrix.c2.y * B4 + matrix.c3.y * B3);
			float A01 = -(matrix.c0.y * B5 - matrix.c2.y * B2 + matrix.c3.y * B1);
			float A02 = (matrix.c0.y * B4 - matrix.c1.y * B2 + matrix.c3.y * B0);
			float A03 = -(matrix.c0.y * B3 - matrix.c1.y * B1 + matrix.c2.y * B0);

			float determinant = matrix.c0.x * A00 + matrix.c1.x * A01 + matrix.c2.x * A02 + matrix.c3.x * A03;
			bool matrixIsNonSingular = std::abs(determinant) > std::numeric_limits<float>::epsilon();
			float invDeterminant = matrixIsNonSingular ? 1.0f / determinant : 1.0f;

			A00 *= invDeterminant;
			A01 *= invDeterminant;
			A02 *= invDeterminant;
			A03 *= invDeterminant;

			float A10 = -(matrix.c1.x * B5 - matrix.c2.x * B4 + matrix.c3.x * B3) * invDeterminant;
			float A11 = (matrix.c0.x * B5 - matrix.c2.x * B2 + matrix.c3.x * B1) * invDeterminant;
			float A12 = -(matrix.c0.x * B4 - matrix.c1.x * B2 + matrix.c3.x * B0) * invDeterminant;
			float A13 = (matrix.c0.x * B3 - matrix.c1.x * B1 + matrix.c2.x * B0) * invDeterminant;

			float A20 = (matrix.c1.w * T5 - matrix.c2.w * T4 + matrix.c3.w * T3) * invDeterminant;
			float A21 = -(matrix.c0.w * T5 - matrix.c2.w * T2 + matrix.c3.w * T1) * invDeterminant;
			float A22 = (matrix.c0.w * T4 - matrix.c1.w * T2 + matrix.c3.w * T0) * invDeterminant;
			float A23 = -(matrix.c0.w * T3 - matrix.c1.w * T1 + matrix.c2.w * T0) * invDeterminant;

			float A30 = -(matrix.c1.z * T5 - matrix.c2.z * T4 + matrix.c3.z * T3) * invDeterminant;
			float A31 = (matrix.c0.z * T5 - matrix.c2.z * T2 + matrix.c3.z * T1) * invDeterminant;
			float A32 = -(matrix.c0.z * T4 - matrix.c1.z * T2 + matrix.c3.z * T0) * invDeterminant;
			float A33 = (matrix.c0.z * T3 - matrix.c1.z * T1 + matrix.c2.z * T0) * invDeterminant;

			result = float4x4(
				float4(A00, A01, A02, A03),
				float4(A10, A11, A12, A13),
				float4(A20, A21, A22, A23),
				float4(A30, A31, A32, A33));

			return matrixIsNonSingular;
		}

		[[nodiscard]] inline static float4x4 BuildViewMatrixRightHanded(const float3& position,
			const float3& direction, const float3& upVector)
		{
			float3 zAxis = direction;
			float3 xAxis = Normalize(Cross(upVector, zAxis));
			float3 yAxis = Cross(zAxis, xAxis);

			float dotXDirection = -Dot(xAxis, direction);
			float dotYDirection = -Dot(yAxis, direction);
			float dotZDirection = -Dot(zAxis, direction);

			float4x4 viewMatrix = float4x4(
				float4(xAxis.x, xAxis.y, xAxis.z, dotXDirection),
				float4(yAxis.x, yAxis.y, yAxis.z, dotYDirection),
				float4(zAxis.x, zAxis.y, zAxis.z, dotZDirection),
				float4(0.0f, 0.0f, 0.0f, 1.0f));

			return viewMatrix;
		}

		[[nodiscard]] inline static float4x4 BuildProjectionMatrixRightHanded(float zNear,
			float zFar, float fieldOfViewY, float aspectRatio)
		{
			float yScale = std::tan((std::numbers::pi_v<float> -fieldOfViewY) * 0.5f);
			float xScale = yScale / aspectRatio;
			float zScale = zFar / (zNear - zFar);

			float4x4 projectionMatrix = float4x4(
				float4(xScale, 0.0f, 0.0f, 0.0f),
				float4(0.0f, yScale, 0.0f, 0.0f),
				float4(0.0f, 0.0f, zScale, zNear * zScale),
				float4(0.0f, 0.0f, -1.0f, 0.0f));

			return projectionMatrix;
		}

		[[nodiscard]] static constexpr float EvaluateSH9(const float* coeffs, const float3& direction) noexcept
		{
			float result = coeffs[0] * SH_Ylm_0__0;

			result += coeffs[1] * SH_Ylm_1_m1 * direction.y;
			result += coeffs[2] * SH_Ylm_1__0 * direction.z;
			result += coeffs[3] * SH_Ylm_1__1 * direction.x;

			result += coeffs[4] * SH_Ylm_2_m2 * direction.x * direction.y;
			result += coeffs[5] * SH_Ylm_2_m1 * direction.y * direction.z;
			result += coeffs[6] * SH_Ylm_2__0 * (3.0f * direction.z * direction.z - 1.0f);
			result += coeffs[7] * SH_Ylm_2__1 * direction.x * direction.z;
			result += coeffs[8] * SH_Ylm_2__2 * (direction.x * direction.x - direction.y * direction.y);

			return result;
		}

		[[nodiscard]] static constexpr float3 EvaluateSH9(const float3* coeffs, const float3& direction) noexcept
		{
			float3 result = coeffs[0] * SH_Ylm_0__0;

			result += coeffs[1] * (SH_Ylm_1_m1 * direction.y);
			result += coeffs[2] * (SH_Ylm_1__0 * direction.z);
			result += coeffs[3] * (SH_Ylm_1__1 * direction.x);

			result += coeffs[4] * (SH_Ylm_2_m2 * direction.x * direction.y);
			result += coeffs[5] * (SH_Ylm_2_m1 * direction.y * direction.z);
			result += coeffs[6] * (SH_Ylm_2__0 * (3.0f * direction.z * direction.z - 1.0f));
			result += coeffs[7] * (SH_Ylm_2__1 * direction.x * direction.z);
			result += coeffs[8] * (SH_Ylm_2__2 * (direction.x * direction.x - direction.y * direction.y));

			return result;
		}
	};
}
