#include "Camera.h"
#include "../Utility/RadianceFieldsUtility.h"

using namespace Utility;

Core::Camera::Camera(const float3& position, const float3& direction, float fieldOfViewY, const Viewport& viewport)
{
	viewMatrix = RadianceFieldsUtility::BuildViewMatrix(position, direction, VECTOR_UP);
}
