#ifndef _RAYTRACER_H
#define _RAYTRACER_H

#include "Ray.h"
#include "Sphere.h"

#include <glm.hpp>

#include <vector>
#include <memory>

struct RaySphereTest
{
	glm::vec3 IntersectPoint = glm::vec3(0, 0, 0);
	bool didIntersect;
};

class RayTracer
{
	private:
		std::vector<std::shared_ptr<Sphere>> allSpheres;

	public:
		void AddSphere(std::shared_ptr<Sphere> newSphere);
		glm::vec3 Trace(std::shared_ptr<Ray> ray);
		glm::vec3 ClosestPoint(std::shared_ptr<Ray> ray, glm::vec3 queryPoint);
		RaySphereTest RaySphereIntersection(std::shared_ptr<Ray> ray, glm::vec3 spherePos, float sphereRadius);
};

#endif