#include "RayTracer.h"

#include <cmath>

void RayTracer::AddSphere(std::shared_ptr<Sphere> newSphere)
{
	allSpheres.push_back(newSphere);
}

glm::vec3 RayTracer::Trace(std::shared_ptr<Ray> ray)
{
	//return colour of pixel to draw
	return glm::vec3();
}

glm::vec3 RayTracer::ClosestPoint(std::shared_ptr<Ray> ray, glm::vec3 queryPoint)
{
	glm::vec3 closestPoint = glm::vec3(0, 0, 0);
	float distance = 0.0f;
	bool firstCheck = true;

	//Closest point on line function
	for (size_t i = 0; i < allSpheres.size(); i++)
	{
		//c = half of tangent intersection
		//d = distance between sphere centre and normal to intersection
		//x = closest point
		//n = direction of ray
		//a = vector from 0,0,0 to ray
		//p = vector to centre of sphere (its position)
		//x = a + ((p - a) . n)n
		//glm::vec3 spherePosition = allSpheres.at(i)->GetPosition(); // p
		//float sphereRadius = allSpheres.at(i)->GetRadius(); // r

		glm::vec3 newClosestPoint; // x
		glm::vec3 rayOrigin = ray->GetOrigin(); // a
		glm::vec3 rayDirection = ray->GetDirection(); // n		

		newClosestPoint = rayOrigin + ((glm::dot((queryPoint - rayOrigin), rayDirection)) * rayDirection);

		if (firstCheck)
		{			
			distance = sqrt(pow(((float)newClosestPoint.x - (float)rayOrigin.x), 2.0f) +
							pow(((float)newClosestPoint.y - (float)rayOrigin.y), 2.0f) +
							pow(((float)newClosestPoint.z - (float)rayOrigin.z), 2.0f));
			closestPoint = newClosestPoint;
			firstCheck = false;
		}

		else
		{
			float newDistance = sqrt(pow(((float)newClosestPoint.x - (float)rayOrigin.x), 2.0f) +
									 pow(((float)newClosestPoint.y - (float)rayOrigin.y), 2.0f) +
									 pow(((float)newClosestPoint.z - (float)rayOrigin.z), 2.0f));
			if (newDistance < distance)
			{
				distance = newDistance;
				closestPoint = newClosestPoint;
			}
		}
	}

	return closestPoint;
}

RaySphereTest RayTracer::RaySphereIntersection(std::shared_ptr<Ray> ray, glm::vec3 spherePos, float sphereRadius)
{
	glm::vec3 rayOrigin = ray->GetOrigin();
	glm::vec3 rayDirection = ray->GetDirection();
	RaySphereTest rtn;

	if (((rayOrigin.x <= (spherePos.x + sphereRadius)) &&
		(rayOrigin.y <= (spherePos.y + sphereRadius)) &&
		(rayOrigin.z <= (spherePos.z + sphereRadius))) || 
		((rayOrigin.x >= (spherePos.x - sphereRadius)) &&
		(rayOrigin.y >= (spherePos.y - sphereRadius)) &&
		(rayOrigin.z >= (spherePos.z - sphereRadius))))
	{
		//Is within current sphere
		rtn.didIntersect = false;
	}
	else
	{
		glm::vec3 closestPoint = ClosestPoint(ray, spherePos);
		if ((closestPoint.x <= rayOrigin.x) && 
			(closestPoint.y <= rayOrigin.y) && 
			(closestPoint.z <= rayOrigin.z))
		{
			//Is behind ray origin
			rtn.didIntersect = false;
		}
		else
		{
			float d = abs(sqrt(pow(((float)spherePos.x - (float)rayOrigin.x - (float)closestPoint.x), 2.0f) + 
						       pow(((float)spherePos.y - (float)rayOrigin.y - (float)closestPoint.y), 2.0f) +
							   pow(((float)spherePos.z - (float)rayOrigin.z - (float)closestPoint.z), 2.0f)));

			float x = sqrt(pow(d, 2.0f) - pow(sphereRadius, 2.0f));

			rtn.IntersectPoint = ( rayOrigin + ((glm::dot((spherePos - rayOrigin), rayDirection)) - x) * rayDirection);
			rtn.didIntersect = true;
		}
	}

	return rtn;
}
