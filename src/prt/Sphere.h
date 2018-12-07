#ifndef _SPHERE_H
#define _SPHERE_H

#include "Object.h"
#include "Ray.h"

#include <glm.hpp>

#include <memory>

class Sphere : public Object
{
	private:
		float radius;
		glm::vec3 position;
		glm::vec3 colour;

	public: 
		Sphere(float rad, glm::vec3 pos, glm::vec3 col);
		glm::vec3 Shade(std::shared_ptr<Ray> ray, glm::vec3 intersect);
		float GetRadius();
		glm::vec3 GetPosition();
};

#endif