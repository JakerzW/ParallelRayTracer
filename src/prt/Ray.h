#ifndef _RAY_H
#define _RAY_H

#include <glm.hpp>

class Ray
{
	private: 
		glm::vec3 origin;
		glm::vec3 direction;

	public: 
		void SetOrigin(glm::ivec2 origCoords);
		glm::vec3 GetOrigin();
		glm::vec3 GetDirection();
};

#endif