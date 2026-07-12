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

		Camera(const float3& position, const float3& direction, float fieldOfViewY, const Viewport& viewport);

	private:
		Camera() = delete;

		float4x4 viewMatrix;
		float4x4 projectionMatrix;

		Viewport _viewport;

		float3 _position;
		float _fieldOfViewY;

		float3 _direction;
	};
}
