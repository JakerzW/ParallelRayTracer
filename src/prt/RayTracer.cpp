#include "RayTracer.h"
#include "Sphere.h"
#include "ObjectList.h"

#include <cmath>

glm::vec3 RayTracer::Trace(std::shared_ptr<Ray> ray, std::shared_ptr<Object> world)
{
	glm::vec3 colour;

	HitRecord hitRec;

	if (world->DidHit(ray, 0.0f, FLT_MAX, hitRec))
	{
		glm::vec3 target = hitRec.p + hitRec.normal + RandomInUnitSphere();
		//colour = 0.5 * Trace(ray);
		//colour = (0.5f * glm::vec3(hitRec.normal.x + 1, hitRec.normal.x + 1, hitRec.normal.x + 1));
	}
	else
	{
		glm::vec3 unitDirection = glm::normalize(ray->GetDirection());
		float t = 0.5 * (unitDirection.y + 1.0);
		colour = (1.0f - t) * glm::vec3(1.0f, 1.0f, 1.0f) + t * glm::vec3(0.5f, 0.7f, 1.0f);
	}

	return colour;
}

glm::vec3 RayTracer::RandomInUnitSphere()
{
	glm::vec3 p;

	do
	{
		p = 2.0f * glm::vec3(rand(), rand(), rand()) - glm::vec3(1, 1, 1);
	} while (pow(glm::length(p),2) >= 1.0);

	return p;
}




