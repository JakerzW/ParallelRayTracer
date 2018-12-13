#ifndef _MATERIAL_H
#define _MATERIAL_H

#include "Ray.h"
#include "Object.h"

#include <memory>

struct HitRecord;

class Material
{
	public:
		virtual bool Scatter(std::shared_ptr<Ray> rayIn, HitRecord &hitRec, glm::vec3 &attenuation, std::shared_ptr<Ray> rayScattered) const = 0;
		
};

class Lambertian : public Material
{
	public:
		Lambertian(const glm::vec3 &a);
		virtual bool Scatter(std::shared_ptr<Ray> rayIn, HitRecord &hitRec, glm::vec3 &attenuation, std::shared_ptr<Ray> rayScattered) const;
		glm::vec3 albedo;
};

class Metal : public Material
{
	public:
		Metal(const glm::vec3 &a, float f);
		virtual bool Scatter(std::shared_ptr<Ray> rayIn, HitRecord &hitRec, glm::vec3 &attenuation, std::shared_ptr<Ray> rayScattered) const;
		glm::vec3 albedo;
		float fuzz;

};

glm::vec3 RandomInUnitSphere();

glm::vec3 Reflect(glm::vec3 &v, glm::vec3 &n);

#endif // !_MATERIAL_H