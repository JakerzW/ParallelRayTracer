#include "Sphere.h"

Sphere::Sphere(float rad, glm::vec3 pos, glm::vec3 col)
{
	radius = rad;
	position = pos;
	colour = col;
}

float Sphere::GetRadius()
{
	return radius;
}

glm::vec3 Sphere::GetPosition()
{
	return position;
}
