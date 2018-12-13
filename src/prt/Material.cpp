#include "Material.h"

Lambertian::Lambertian(const glm::vec3 &a) : albedo(a)
{

}

//Calculate the scatter for a matte object
bool Lambertian::Scatter(std::shared_ptr<Ray> rayIn, HitRecord & hitRec, glm::vec3 & attenuation, std::shared_ptr<Ray> rayScattered) const
{
	glm::vec3 target = hitRec.p + hitRec.normal + RandomInUnitSphere();
	std::shared_ptr<Ray>newRay = std::make_shared<Ray>(hitRec.p, target - hitRec.p);
	rayScattered = newRay;
	attenuation = albedo;
	return true;
}

//Initialise and calculate roughness for a metal object
Metal::Metal(const glm::vec3 &a, float f) : albedo(a)
{
	if (f < 1)
	{
		fuzz = f;
	}
	else
	{
		fuzz = 1;
	}
}

//Calculate scatter for a metal object
bool Metal::Scatter(std::shared_ptr<Ray> rayIn, HitRecord & hitRec, glm::vec3 & attenuation, std::shared_ptr<Ray> rayScattered) const
{
	glm::vec3 reflected = Reflect(glm::normalize(rayIn->GetDirection()), hitRec.normal);
	std::shared_ptr<Ray> newRay = std::make_shared<Ray>(hitRec.p, reflected + fuzz * RandomInUnitSphere());
	rayScattered = newRay;
	attenuation = albedo;
	return (glm::dot(rayScattered->GetDirection(), hitRec.normal) > 0);
}

//Calculate random ray direction
glm::vec3 RandomInUnitSphere()
{
	glm::vec3 p;

	do
	{
		double x = double(rand()) / (RAND_MAX + 1.0);
		double y = double(rand()) / (RAND_MAX + 1.0);
		double z = double(rand()) / (RAND_MAX + 1.0);

		p = 2.0f * glm::vec3(x, y, z) - glm::vec3(1, 1, 1);
	} while (pow(glm::length(p), 2) >= 1.0);
	//while (glm::length(p) >= 1.0);

	return p;
}

//Calculate the normal for a reflection
glm::vec3 Reflect(glm::vec3 & v, glm::vec3 & n)
{
	return v - 2 * glm::dot(v, n) * n;
}

