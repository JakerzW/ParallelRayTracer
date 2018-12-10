#include "RayTracer.h"

#include <cmath>

glm::vec3 RayTracer::Trace(std::shared_ptr<Ray> ray, std::shared_ptr<Sphere> sphere)
{
	glm::vec3 colour;

	if (sphere->DidHit(ray))
	{
		colour = glm::vec3(1, 0, 0);
	}
	else
	{
		glm::vec3 unitDirection = glm::normalize(ray->GetDirection());
		float t = 0.5 * (-unitDirection.y + 1.0);
		colour = (1.0f - t) * glm::vec3(1.0f, 1.0f, 1.0f) + t * glm::vec3(0.5f, 0.7f, 1.0f);
	}

	return colour;
}




