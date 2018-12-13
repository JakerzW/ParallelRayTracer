#ifndef _RAY_H
#define _RAY_H

#include <glm.hpp>

class Ray
{
	private: 
		glm::vec3 origin;
		glm::vec3 direction;

	public: 
		Ray();
		Ray(glm::vec3 &o, glm::vec3 &d);
		void Init(glm::vec3 &o, glm::vec3 &d);
		glm::vec3 GetOrigin();
		glm::vec3 GetDirection();
		glm::vec3 GetPointAtParameter(float t);
};

#endif