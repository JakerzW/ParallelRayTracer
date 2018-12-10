#ifndef _OBJECT_H
#define _OBJECT_H

#include "Ray.h"

#include <glm.hpp>

#include <memory>

//Any object within the world must inherit from this
//All objects will require certain functions that are assigned in this class

class Object
{
	private:
		

	public:
		glm::vec3 ClosestPoint(std::shared_ptr<Ray> ray, glm::vec3 queryPoint);
};


#endif // !_OBJECT_H
