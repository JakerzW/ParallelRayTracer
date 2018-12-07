#include "Ray.h"

void Ray::SetOrigin(glm::ivec2 origCoords)
{
	origin.x = origCoords.x;
	origin.y = origCoords.y;
	origin.z = -1;
}

glm::vec3 Ray::GetOrigin()
{
	return origin;
}

glm::vec3 Ray::GetDirection()
{
	return direction;
}
