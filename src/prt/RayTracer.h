#ifndef _RAYTRACER_H
#define _RAYTRACER_H

#include "Ray.h"
#include "Sphere.h"

#include <glm.hpp>

#include <vector>
#include <memory>

class RayTracer
{
	private:

	public:
		glm::vec3 Trace(std::shared_ptr<Ray> ray, std::shared_ptr<Object> world);
		glm::vec3 RandomInUnitSphere();
};

#endif