#include "Object.h"

glm::vec3 Object::ClosestPoint(std::shared_ptr<Ray> ray, glm::vec3 queryPoint)
{
	glm::vec3 closestPoint = glm::vec3(0, 0, 0);



	return closestPoint;

	//float distance = 0.0f;
	//bool firstCheck = true;
	//Closest point on line function	
	//c = half of tangent intersection
	//d = distance between sphere centre and normal to intersection
	//x = closest point
	//n = direction of ray
	//a = vector from 0,0,0 to ray
	//p = vector to centre of sphere (its position)
	//x = a + ((p - a) . n)n
	//glm::vec3 spherePosition = allSpheres.at(i)->GetPosition(); // p
	//float sphereRadius = allSpheres.at(i)->GetRadius(); // r
	//glm::vec3 newClosestPoint; // x
	//glm::vec3 rayOrigin = ray->GetOrigin(); // a
	//glm::vec3 rayDirection = ray->GetDirection(); // n		
	//newClosestPoint = rayOrigin + ((glm::dot((queryPoint - rayOrigin), rayDirection)) * rayDirection);
	//if (firstCheck)
	//{			
	//	distance = sqrt(pow(((float)newClosestPoint.x - (float)rayOrigin.x), 2.0f) +
	//					pow(((float)newClosestPoint.y - (float)rayOrigin.y), 2.0f) +
	//					pow(((float)newClosestPoint.z - (float)rayOrigin.z), 2.0f));
	//	closestPoint = newClosestPoint;
	//	firstCheck = false;
	//}
	//else
	//{
	//	float newDistance = sqrt(pow(((float)newClosestPoint.x - (float)rayOrigin.x), 2.0f) +
	//								pow(((float)newClosestPoint.y - (float)rayOrigin.y), 2.0f) +
	//								pow(((float)newClosestPoint.z - (float)rayOrigin.z), 2.0f));
	//	if (newDistance < distance)
	//	{
	//		distance = newDistance;
	//		closestPoint = newClosestPoint;
	//	}
	//}
	//return closestPoint;
}