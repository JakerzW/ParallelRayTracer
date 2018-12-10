#ifndef _CAMERA_H
#define _CAMERA_H

#include "Ray.h"

#include <ext.hpp>

#include <vector>
#include <memory>

class Camera
{
	private:
		glm::vec3 origin;
		glm::vec3 lowerLeftCorner;
		glm::vec3 horizontal;
		glm::vec3 vertical;

	public: 
		Camera(glm::vec3 o, glm::vec3 l, glm::vec3 h, glm::vec3 v);
		std::shared_ptr<Ray> CreateRay(float u, float v);
};

#endif