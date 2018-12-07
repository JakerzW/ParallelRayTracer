#ifndef _CAMERA_H
#define _CAMERA_H

#include "Ray.h"

#include <ext.hpp>

#include <vector>
#include <memory>

class Camera
{
	private:
		glm::vec3 viewMatrix;
		glm::vec3 projMatrix;

	public: 
		std::shared_ptr<Ray> CreateRay(glm::ivec2 pixCoords);
};

#endif