#include "Ray.h"

Ray::Ray()
{
}

Ray::Ray(glm::vec3 &o, glm::vec3 &d)
{
	origin = o;
	direction = d;
}

void Ray::Init(glm::vec3 &o, glm::vec3 &d)
{
	origin = o;
	direction = d;
}

glm::vec3 Ray::GetOrigin()
{
	return origin;
}

glm::vec3 Ray::GetDirection()
{
	return direction;
}

glm::vec3 Ray::GetPointAtParameter(float t)
{
	return (origin + t * direction);
}
