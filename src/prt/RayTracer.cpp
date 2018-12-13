#include "RayTracer.h"
#include "Sphere.h"
#include "ObjectList.h"
#include "Ray.h"
#include "Material.h"

#include <stdlib.h>

#include <cmath>

glm::vec3 RayTracer::Trace(std::shared_ptr<Ray> ray, std::shared_ptr<Object> world, int depth)
{
	glm::vec3 colour = glm::vec3();

	HitRecord hitRec;

	if (world->DidHit(ray, 0.001, FLT_MAX, hitRec))
	{
		std::shared_ptr<Ray> scatteredRay = std::make_shared<Ray>();
		glm::vec3 attenuation;

		if (depth < 50 && hitRec.material->Scatter(ray, hitRec, attenuation, scatteredRay))
		{
			return attenuation * Trace(scatteredRay, world, depth + 1);
		}
		else
		{
			return glm::vec3(0, 0, 0);
		}
	}	
	//{
	//	glm::vec3 target = hitRec.p + hitRec.normal + RandomInUnitSphere();
	//	std::shared_ptr<Ray> newRay = std::make_shared<Ray>(hitRec.p, target - hitRec.p);
	//	colour = 0.5f * Trace(newRay, world);
	//	//colour = (0.5f * glm::vec3(hitRec.normal.x + 1, hitRec.normal.x + 1, hitRec.normal.x + 1));
	//}
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
		double x = double(rand()) / (RAND_MAX + 1.0);
		double y = double(rand()) / (RAND_MAX + 1.0);
		double z = double(rand()) / (RAND_MAX + 1.0);

		p = 2.0f * glm::vec3(x, y, z) - glm::vec3(1, 1, 1);
	} while (pow(glm::length(p),2) >= 1.0);
	//while (glm::length(p) >= 1.0);

	return p;
}




