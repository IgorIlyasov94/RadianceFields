#include "Camera.h"
#include "Math.h"

Core::Camera::Camera()
{
	_fieldOfViewY = DEFAULT_FIELD_OF_VIEW_Y;
	_viewport = Viewport(uint2(1u, 1u), 0.0f, 1.0f);

	viewMatrix = Math::BuildViewMatrixRightHanded({}, float3(1.0f, 0.0, 0.0f), VECTOR_UP);
	projectionMatrix = Math::BuildProjectionMatrixRightHanded(_viewport.ZNear, _viewport.ZFar, _fieldOfViewY, 1.0f);
	viewProjectionMatrix = Math::Mul(viewMatrix, projectionMatrix);
	Math::Inverse(viewProjectionMatrix, invViewProjectionMatrix);
}

Core::Camera::Camera(const float3& position, const float3& direction, float fieldOfViewY, const Viewport& viewport)
{
	float aspectRatio = viewport.Size.x / static_cast<float>(viewport.Size.y);
	_fieldOfViewY = fieldOfViewY;
	_viewport = viewport;

	viewMatrix = Math::BuildViewMatrixRightHanded(position, direction, VECTOR_UP);
	projectionMatrix = Math::BuildProjectionMatrixRightHanded(viewport.ZNear, viewport.ZFar, fieldOfViewY, aspectRatio);
	viewProjectionMatrix = Math::Mul(viewMatrix, projectionMatrix);
	Math::Inverse(viewProjectionMatrix, invViewProjectionMatrix);
}

void Core::Camera::Update(const float3& position, const float3& direction)
{
	_position = position;

	viewMatrix = Math::BuildViewMatrixRightHanded(position, direction, VECTOR_UP);
	viewProjectionMatrix = Math::Mul(viewMatrix, projectionMatrix);
	Math::Inverse(viewProjectionMatrix, invViewProjectionMatrix);
}

float3 Core::Camera::Position() const noexcept
{
	return _position;
}

float4x4 Core::Camera::GetInvViewProjectionMatrix() const noexcept
{
	return invViewProjectionMatrix;
}
