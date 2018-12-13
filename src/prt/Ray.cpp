#include "Ray.h"

Ray::Ray()
{
}

//Initialise a ray using variables given
Ray::Ray(glm::vec3 &o, glm::vec3 &d)
{
	origin = o;
	direction = d;
}

//Initialise a ray that's already created
void Ray::Init(glm::vec3 &o, glm::vec3 &d)
{
	origin = o;
	direction = d;
}

//Return the origin of a ray
glm::vec3 Ray::GetOrigin()
{
	return origin;
}

//Return the direction of a ray
glm::vec3 Ray::GetDirection()
{
	return direction;
}

//Find the point of a ray using the distance variable t
glm::vec3 Ray::GetPointAtParameter(float t)
{
	return (origin + t * direction);
}
