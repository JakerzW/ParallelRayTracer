#ifndef _SPHERE_H
#define _SPHERE_H

#include "Object.h"
#include "Ray.h"

#include <glm.hpp>

#include <memory>

struct RaySphereTest
{
	glm::vec3 IntersectPoint = glm::vec3(0, 0, 0);
	bool didIntersect;
};

class Sphere 
{
	private:
		float radius;
		glm::vec3 position;
		glm::vec3 colour;

	public: 
		Sphere(float rad, glm::vec3 pos, glm::vec3 col);
		float GetRadius();
		glm::vec3 GetPosition();
		bool DidHit(std::shared_ptr<Ray> ray);
};

#endif