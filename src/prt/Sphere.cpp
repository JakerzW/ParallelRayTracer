#include "Sphere.h"

//Initialise a sphere
Sphere::Sphere(float rad, glm::vec3 pos, std::shared_ptr<Material> m)
{
	radius = rad;
	position = pos;
	material = m;
}

//Return the radius
float Sphere::GetRadius()
{
	return radius;
}

//Return the position
glm::vec3 Sphere::GetPosition()
{
	return position;
}

//Calculate whether or not a ray has hit the sphere and manipulate the HitRecord variables
bool Sphere::DidHit(std::shared_ptr<Ray> ray, float tMin, float tMax, HitRecord &hitRec) const
{
	glm::vec3 oc = ray->GetOrigin() - position;
	float a = glm::dot(ray->GetDirection(), ray->GetDirection());
	float b = glm::dot(oc, ray->GetDirection());
	float c = glm::dot(oc, oc) - radius * radius;
	float discriminant = b * b - a * c;

	if (discriminant > 0)
	{
		float root = (-b - sqrt(discriminant)) / a;
		if (root < tMax && root > tMin)
		{
			hitRec.t = root;
			hitRec.p = ray->GetPointAtParameter(hitRec.t);
			hitRec.normal = (hitRec.p - position) / radius;
			hitRec.material = material;
			return true;
		}
		root = (-b + sqrt(discriminant)) / a;
		if (root < tMax && root > tMin)
		{
			hitRec.t = root;
			hitRec.p = ray->GetPointAtParameter(hitRec.t);
			hitRec.normal = (hitRec.p - position) / radius;
			hitRec.material = material;
			return true;
		}
	}
	return false;
}
