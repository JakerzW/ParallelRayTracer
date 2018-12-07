#include "Camera.h"
#include "Object.h"
#include "Ray.h"
#include "RayTracer.h"
#include "Sphere.h"

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <ext.hpp>

#include <iostream>
#include <memory>

int main()
{
	std::cout << "Doing nothing..." << std::endl;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "Something went wrong, cannot initialise SDL." << std::endl;
		return -1;
	}
	
	int winPosX = 500;
	int winPosY = 100;
	int winWidth = 800;
	int winHeight = 800;

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

	std::shared_ptr<Camera> camera;
	std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>(5, glm::vec3(0, 0, -10), glm::vec3(255, 0, 0));
	std::shared_ptr<RayTracer> tracer;
	tracer->AddSphere(sphere);
	int pixX = 250;
	int pixY = 250;

	while (running)
	{
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
						case SDLK_UP:
						{
							pixY--;
							break;
						}
						case SDLK_DOWN:
						{
							pixY++;
							break;
						}
						case SDLK_LEFT:
						{
							pixX--;
							break;
						}
						case SDLK_RIGHT:
						{
							pixX++;
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

		//Do stuff

		for (size_t i = 0; i < winWidth; i++)
		{
			for (size_t j = 0; j < winHeight; j++)
			{
				//Create a new ray
				std::shared_ptr<Ray> newRay = camera->CreateRay(glm::ivec2(i, j));

				//Shoot ray and check for intersections
				tracer->Trace(newRay);

			}
		}

		SDL_RenderPresent(renderer);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
		SDL_RenderDrawPoint(renderer, pixX, pixY);

		//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		//(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//SDL_GL_SwapWindow(window);

		if (idealFps > deltaTime)
		{
			//std::cout << "Delaying..." << std::endl;
			unsigned int delay = (idealFps - deltaTime) * 1000.0f;
			SDL_Delay(delay);
		}
	}

	//system("PAUSE");

	return 0;
}