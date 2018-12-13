#include "Camera.h"
#include "Ray.h"
#include "RayTracer.h"
#include "Sphere.h"
#include "Object.h"
#include "ObjectList.h"
#include "Material.h"

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <ext.hpp>

#include <iostream>
#include <memory>

int main()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "Something went wrong, cannot initialise SDL." << std::endl;
		return -1;
	}
	
	int winPosX = 100;
	int winPosY = 100;
	int winWidth = 1000;
	int winHeight = 500;

	SDL_Window* window = SDL_CreateWindow("My Window", winPosX, winPosY, winWidth, winHeight,
										  SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	SDL_GLContext glcontext = SDL_GL_CreateContext(window);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Something went wrong, cannot initialise glew." << std::endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);
	
	bool running = true;

	unsigned int lastTime = SDL_GetTicks();
	unsigned int currentTime;
	float deltaTime;
	int fps = 60;
	float idealFps = (float)(1.0f / fps);	

	glm::vec3 lowerLeftCorner = glm::vec3(-2.0, -1.0, -1.0);
	glm::vec3 horizontal = glm::vec3(4.0, 0.0, 0.0);
	glm::vec3 vertical = glm::vec3(0.0, 2.0, 0.0);
	glm::vec3 origin = glm::vec3(0.0, 0.0, 0.0);

	std::shared_ptr<Camera> camera = std::make_shared<Camera>(origin, lowerLeftCorner, horizontal, vertical);
	
	std::shared_ptr<RayTracer> tracer = std::make_shared<RayTracer>();

	//List of objects
	std::vector<std::shared_ptr<Object>> objectList;

	std::shared_ptr<Lambertian> sphereMat1 = std::make_shared<Lambertian>(glm::vec3(0.8, 0.3, 0.3));
	std::shared_ptr<Lambertian> sphereMat2 = std::make_shared<Lambertian>(glm::vec3(0.8, 0.8, 0.0));
	std::shared_ptr<Metal> sphereMat3 = std::make_shared<Metal>(glm::vec3(0.8, 0.6, 0.2), 0.3);
	std::shared_ptr<Metal> sphereMat4 = std::make_shared<Metal>(glm::vec3(0.8, 0.8, 0.8), 1.0);

	std::shared_ptr<Sphere> sphere1 = std::make_shared<Sphere>(0.5, glm::vec3(0, 0, -1), sphereMat1);
	std::shared_ptr<Sphere> sphere2 = std::make_shared<Sphere>(100, glm::vec3(0, -100.5, -1), sphereMat2);
	std::shared_ptr<Sphere> sphere3 = std::make_shared<Sphere>(0.5, glm::vec3(1, 0, -1), sphereMat3);
	std::shared_ptr<Sphere> sphere4 = std::make_shared<Sphere>(0.5, glm::vec3(-1, 0, -1), sphereMat4);

	/*std::shared_ptr<Sphere> sphere1 = std::make_shared<Sphere>(0.5, glm::vec3(0, 0, -1), new Lambertian(glm::vec3(0.8, 0.3, 0.3)));
	std::shared_ptr<Sphere> sphere2 = std::make_shared<Sphere>(100, glm::vec3(0, -100.5, -1), new Lambertian(glm::vec3(0.8, 0.8, 0.0)));
	std::shared_ptr<Sphere> sphere3 = std::make_shared<Sphere>(0.5, glm::vec3(1, 0, -1), new Lambertian(glm::vec3(0.8, 0.6, 0.2)));
	std::shared_ptr<Sphere> sphere4 = std::make_shared<Sphere>(0.5, glm::vec3(-1, 0, -1), new Lambertian(glm::vec3(0.8, 0.8, 0.8)));
*/
	objectList.push_back(sphere1);
	objectList.push_back(sphere2);
	objectList.push_back(sphere3);
	objectList.push_back(sphere4);

	std::shared_ptr<ObjectList> world = std::make_shared<ObjectList>(objectList);

	while (running)
	{
		bool startTrace = false;
		SDL_Event event;
		
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
				{
					running = false;
					break;
				}
				case SDL_KEYDOWN:
				{
					switch (event.key.keysym.sym)
					{
						case SDLK_ESCAPE:
						{
							running = false;
							break;
						}
						case SDLK_RETURN:
						{
							startTrace = true;
							break;
						}
						case SDLK_BACKSPACE:
						{
							SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
							SDL_RenderClear(renderer);
						}
					}
				}
			}
			break;
		}

		currentTime = SDL_GetTicks();
		deltaTime = (float)(currentTime - lastTime) / 1000.0f;
		lastTime = currentTime;
		
		int ns = 100;

		//Main code
		if (startTrace)
		{
			for (int j = winHeight - 1; j >= 0; j--)
			{
				for (int i = 0; i < winWidth; i++)
				{
					glm::vec3 colour = glm::vec3(0, 0, 0);

					for (size_t h = 0; h < ns; h++)
					{
						float u = float(i + (float)rand() / (RAND_MAX + 1.0)) / float(winWidth);
						float v = float(j + (float)rand() / (RAND_MAX + 1.0)) / float(winHeight);

						std::shared_ptr<Ray> newRay = camera->CreateRay(u, v);
						glm::vec3 p = newRay->GetPointAtParameter(2.0);
						colour += tracer->Trace(newRay, world, 0);
					}

					colour /= float(ns);	
					colour = glm::vec3(sqrt(colour.x), sqrt(colour.y), sqrt(colour.z));

					int pixelR = int(255.99 * colour.x);
					int pixelG = int(255.99 * colour.y);
					int pixelB = int(255.99 * colour.z);

					SDL_SetRenderDrawColor(renderer, pixelR, pixelG, pixelB, 255);
					SDL_RenderDrawPoint(renderer, i, winHeight - j);
				}
			}
			startTrace = false;
		}		

		//std::cout << "Drawing Complete." << std::endl;

		SDL_RenderPresent(renderer);

		if (idealFps > deltaTime)
		{
			//std::cout << "Delaying..." << std::endl;
			unsigned int delay = (idealFps - deltaTime) * 1000.0f;
			SDL_Delay(delay);
		}
	}

	return 0;
}
