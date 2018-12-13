#include "RayTracer.h"
#include "Sphere.h"
#include "ObjectList.h"
#include "Ray.h"
#include "Material.h"

#include <stdlib.h>

#include <cmath>
#include <thread>
#include <iostream>

glm::vec3 RayTracer::Trace(std::shared_ptr<Ray> ray, std::shared_ptr<Object> world, int depth)
{
	glm::vec3 colour = glm::vec3();

	HitRecord hitRec;

	if (world->DidHit(ray, 0.001, FLT_MAX, hitRec))
	{
		std::shared_ptr<Ray> scatteredRay = std::make_shared<Ray>();
		glm::vec3 attenuation;

		if (depth < 50 && hitRec.material->Scatter(ray, hitRec, attenuation, scatteredRay))
		{
			return attenuation * Trace(scatteredRay, world, depth + 1);
		}
		else
		{
			return glm::vec3(0, 0, 0);
		}
	}	
	//{
	//	glm::vec3 target = hitRec.p + hitRec.normal + RandomInUnitSphere();
	//	std::shared_ptr<Ray> newRay = std::make_shared<Ray>(hitRec.p, target - hitRec.p);
	//	colour = 0.5f * Trace(newRay, world);
	//	//colour = (0.5f * glm::vec3(hitRec.normal.x + 1, hitRec.normal.x + 1, hitRec.normal.x + 1));
	//}
	else
	{
		glm::vec3 unitDirection = glm::normalize(ray->GetDirection());
		float t = 0.5 * (unitDirection.y + 1.0);
		colour = (1.0f - t) * glm::vec3(1.0f, 1.0f, 1.0f) + t * glm::vec3(0.5f, 0.7f, 1.0f);
	}

	return colour;
}

glm::vec3 RayTracer::RandomInUnitSphere()
{
	glm::vec3 p;

	do
	{
		double x = double(rand()) / (RAND_MAX + 1.0);
		double y = double(rand()) / (RAND_MAX + 1.0);
		double z = double(rand()) / (RAND_MAX + 1.0);

		p = 2.0f * glm::vec3(x, y, z) - glm::vec3(1, 1, 1);
	} while (pow(glm::length(p),2) >= 1.0);
	//while (glm::length(p) >= 1.0);

	return p;
}

void RayTracer::Draw(std::shared_ptr<Camera> c, std::shared_ptr<ObjectList> w, int winW, int winH, SDL_Renderer* r, int a)
{
	camera = c;
	world = w;
	renderer = r;
	antialias = a;
	winWidth = winW;
	winHeight = winH;	

	std::thread threadOne(&RayTracer::RunThreads, this, 0, int(winWidth * 0.25), 0, int(winHeight * 0.5));
	std::thread threadTwo(&RayTracer::RunThreads, this, int(winWidth * 0.25), int(winWidth * 0.5), 0, int(winHeight * 0.5));
	std::thread threadThree(&RayTracer::RunThreads, this, int(winWidth * 0.5), int(winWidth * 0.75), 0, int(winHeight * 0.5));
	std::thread threadFour(&RayTracer::RunThreads, this, int(winWidth * 0.75), winWidth, 0, int(winHeight * 0.5));
	std::thread threadFive(&RayTracer::RunThreads, this, 0, int(winWidth * 0.25), int(winHeight * 0.5), winHeight);
	std::thread threadSix(&RayTracer::RunThreads, this, int(winWidth * 0.25), int(winWidth * 0.5), int(winHeight * 0.5), winHeight);
	std::thread threadSeven(&RayTracer::RunThreads, this, int(winWidth * 0.5), int(winWidth * 0.75), int(winHeight * 0.5), winHeight);
	std::thread threadEight(&RayTracer::RunThreads, this, int(winWidth * 0.75), winWidth, int(winHeight * 0.5), winHeight);

	threadOne.join();
	threadTwo.join();
	threadThree.join();
	threadFour.join();
	threadFive.join();
	threadSix.join();
	threadSeven.join();
	threadEight.join();

	std::cout << "Threads completed." << std::endl;
}

void RayTracer::RunThreads(int xMin, int xMax, int yMin, int yMax)
{
	for (int i = xMin; i < xMax; i++)
	{
		for (int j = yMin; j < yMax; j++)
		{
			std::shared_ptr<Pixel> currentPix = std::make_shared<Pixel>();
			glm::vec3 colour = glm::vec3(0, 0, 0);

			for (size_t h = 0; h < antialias; h++)
			{
				float u = float(i + (double)rand() / (RAND_MAX + 1.0)) / float(winWidth);
				float v = float(j + (double)rand() / (RAND_MAX + 1.0)) / float(winHeight);

				std::shared_ptr<Ray> newRay = camera->CreateRay(u, v);
				glm::vec3 p = newRay->GetPointAtParameter(2.0);
				//mtx.lock();
				colour += Trace(newRay, world, 0);
				//mtx.unlock();
			}

			colour /= float(antialias);
			colour = glm::vec3(sqrt(colour.x), sqrt(colour.y), sqrt(colour.z));

			colour.x = int(255.99 * colour.x);
			colour.y = int(255.99 * colour.y);
			colour.z = int(255.99 * colour.z);

			/*int pixelR = int(255.99 * colour.x);
			int pixelG = int(255.99 * colour.y);
			int pixelB = int(255.99 * colour.z);*/

			currentPix->colour = colour;
			currentPix->pixCoords = glm::ivec2(i, j);
			
			mtx.lock();
			allPixels.push_back(currentPix);
			mtx.unlock();

			//SDL_SetRenderDrawColor(renderer, pixelR, pixelG, pixelB, 255);
			//SDL_RenderDrawPoint(renderer, i, winHeight - j);
		}
	}
}

std::vector<std::shared_ptr<Pixel>> RayTracer::GetAllPixels()
{
	return allPixels;
}




