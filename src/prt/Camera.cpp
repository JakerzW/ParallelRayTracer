#include "Camera.h"

Camera::Camera(glm::vec3 o, glm::vec3 l, glm::vec3 h, glm::vec3 v)
{
	origin = o;
	lowerLeftCorner = l;
	horizontal = h;
	vertical = v;
}

std::shared_ptr<Ray> Camera::CreateRay(float u, float v)
{
	std::shared_ptr<Ray> newRay = std::make_shared<Ray>();
	
	newRay->Init(origin, lowerLeftCorner + u*horizontal + v*vertical);
	
	return newRay;
}
