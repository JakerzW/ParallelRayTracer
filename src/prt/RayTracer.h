#ifndef _RAYTRACER_H
#define _RAYTRACER_H

#include "Ray.h"
#include "Sphere.h"
#include "Camera.h"
#include "ObjectList.h"

#include <SDL2/SDL.h>
#include <glm.hpp>

#include <vector>
#include <memory>
#include <mutex>

struct Pixel
{
	glm::ivec2 pixCoords;
	glm::vec3 colour;
};

class RayTracer
{
	private:
		std::vector<std::shared_ptr<Pixel>> allPixels;
		std::weak_ptr<RayTracer> self;
		std::shared_ptr<Camera> camera;
		std::shared_ptr<ObjectList> world;
		SDL_Renderer* renderer;
		int antialias;
		int winWidth;
		int winHeight;
		std::mutex mtx;

	public:
		glm::vec3 Trace(std::shared_ptr<Ray> ray, std::shared_ptr<Object> world, int depth);
		glm::vec3 RandomInUnitSphere();
		void Draw(std::shared_ptr<Camera> c, std::shared_ptr<ObjectList> w, int winWidth, int winHeight, SDL_Renderer* r, int a);
		void RunThreads(int xMin, int xMax, int yMin, int yMax);
		std::vector<std::shared_ptr<Pixel>> GetAllPixels();

};

#endif