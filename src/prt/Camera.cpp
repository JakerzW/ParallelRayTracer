#include "Camera.h"

std::shared_ptr<Ray> Camera::CreateRay(glm::ivec2 pixCoords)
{
	std::shared_ptr<Ray> newRay = std::make_shared<Ray>();
	newRay->SetOrigin(pixCoords);
	return newRay;
}
