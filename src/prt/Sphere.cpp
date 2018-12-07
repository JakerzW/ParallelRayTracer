#include "Sphere.h"

Sphere::Sphere(float rad, glm::vec3 pos, glm::vec3 col)
{
	radius = rad;
	position = pos;
	colour = col;
}

glm::vec3 Sphere::Shade(std::shared_ptr<Ray> ray, glm::vec3 intersect)
{
	return colour;
}

float Sphere::GetRadius()
{
	return radius;
}

glm::vec3 Sphere::GetPosition()
{
	return position;
}
