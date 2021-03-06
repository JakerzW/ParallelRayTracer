#ifndef _SPHERE_H
#define _SPHERE_H

#include "Object.h"
#include "Ray.h"
#include "Material.h"

#include <glm.hpp>

#include <memory>

struct RaySphereTest
{
	glm::vec3 IntersectPoint = glm::vec3(0, 0, 0);
	bool didIntersect;
};

class Sphere : public Object
{
	private:
		float radius;
		glm::vec3 position;
		std::shared_ptr<Material> material;

	public: 
		Sphere(float rad, glm::vec3 pos, std::shared_ptr<Material> m);
		float GetRadius();
		glm::vec3 GetPosition();
		bool DidHit(std::shared_ptr<Ray> ray, float tMin, float tMax, HitRecord &hitRec) const;
};

#endif