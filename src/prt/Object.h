#ifndef _OBJECT_H
#define _OBJECT_H

#include "Ray.h"

#include <glm.hpp>

#include <memory>

//Any object within the world must inherit from this
//All objects will require certain functions that are assigned in this class

class Material;

struct HitRecord
{
	float t = 0;
	glm::vec3 p = glm::vec3();
	glm::vec3 normal = glm::vec3();
	std::shared_ptr<Material> material;

};

class Object
{
	public:
	virtual bool DidHit(std::shared_ptr<Ray> ray, float tMin, float tMax, HitRecord &hitRec) const;
};


#endif // !_OBJECT_H
