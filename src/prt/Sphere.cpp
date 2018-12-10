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

bool Sphere::DidHit(std::shared_ptr<Ray> ray)
{
	glm::vec3 oc = ray->GetOrigin() - position;
	float a = glm::dot(ray->GetDirection(), ray->GetDirection());
	float b = 2.0 * glm::dot(oc, ray->GetDirection());
	float c = glm::dot(oc, oc) - pow(radius, 2);
	float discriminant = pow(b, 2) - 4 * a * c;
	   	 
	return (discriminant > 0);
}
