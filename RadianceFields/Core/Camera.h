#pragma once

#include "../Includes.h"
#include "DataTypes.h"
#include "Viewport.h"

namespace Core
{
	class Camera
	{
	public:
		static constexpr float3 VECTOR_UP = { 0.0f, 0.0f, 1.0f };
		static constexpr float DEFAULT_FIELD_OF_VIEW_Y = std::numbers::pi_v<float> / 3.0f; //60 deg

		Camera();
		Camera(const float3& position, const float3& direction, float fieldOfViewY, const Viewport& viewport);

		void Update(const float3& position, const float3& direction);

		float3 Position() const noexcept;

		float4x4 GetInvViewProjectionMatrix() const noexcept;

	private:
		float4x4 viewMatrix;
		float4x4 projectionMatrix;
		float4x4 viewProjectionMatrix;
		float4x4 invViewProjectionMatrix;

		Viewport _viewport;

		float3 _position;
		float _fieldOfViewY;

		float3 _direction;
	};
}
