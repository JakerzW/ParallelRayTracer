#include "Camera.h"
#include "Ray.h"
#include "RayTracer.h"
#include "Sphere.h"
#include "Object.h"

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

	glm::vec3 lowerLeftCorner = glm::vec3(-2.0f, -1.0f, -1.0f);
	glm::vec3 horizontal = glm::vec3(4.0f, 0.0f, 0.0f);
	glm::vec3 vertical = glm::vec3(0.0f, 2.0f, 0.0f);
	glm::vec3 origin = glm::vec3(0.0f, 0.0f, 0.0f);

	std::shared_ptr<Camera> camera = std::make_shared<Camera>(origin, lowerLeftCorner, horizontal, vertical);

	//list of objects
	std::vector<std::shared_ptr<Sphere>> sphereList;

	std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>(0.5, glm::vec3(0, 0, -1), glm::vec3(255, 0, 0));

	sphereList.push_back(sphere);

	std::shared_ptr<RayTracer> tracer = std::make_shared<RayTracer>();

	while (running)
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

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
					}
				}
			}
			break;
		}

		currentTime = SDL_GetTicks();
		deltaTime = (float)(currentTime - lastTime) / 1000.0f;
		lastTime = currentTime;

		//Main code
		for (int j = winHeight - 1; j >= 0; j--)
		{
			for (int i = 0; i < winWidth; i++)
			{
				float u = float(i) / float(winWidth);
				float v = float(j) / float(winHeight);

				//Create a new ray
				std::shared_ptr<Ray> newRay = camera->CreateRay(u, v);				

				glm::vec3 colour = tracer->Trace(newRay, sphere);	

				int pixelR = int(255.99 * colour.x);
				int pixelG = int(255.99 * colour.y);
				int pixelB = int(255.99 * colour.z);

				SDL_SetRenderDrawColor(renderer, pixelR, pixelG, pixelB, 255);
				SDL_RenderDrawPoint(renderer, i, j);
			}
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