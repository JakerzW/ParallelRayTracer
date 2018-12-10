#include "Sphere.h"

Sphere::Sphere(float rad, glm::vec3 pos)
{
	radius = rad;
	position = pos;
}

float Sphere::GetRadius()
{
	return radius;
}

glm::vec3 Sphere::GetPosition()
{
	return position;
}

bool Sphere::DidHit(std::shared_ptr<Ray> ray)
{
	glm::vec3 oc = ray->GetOrigin() - position;
	float a = glm::dot(ray->GetDirection(), ray->GetDirection());
	float b = 2.0 * glm::dot(oc, ray->GetDirection());
	float c = glm::dot(oc, oc) - radius * radius;
	float discriminant = b * b - 4 * a * c;
	   	 
	return (discriminant > 0);

	if (discriminant < 0)
	{
		return -1.0;
	}
	else
	{
		return (-b - sqrt(discriminant)) / (2.0 * a);
	}
}
