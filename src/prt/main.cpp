#include <SDL2/SDL.h>

#include <iostream>

int main()
{
	std::cout << "Doing nothing..." << std::endl;

	SDL_Init(SDL_INIT_VIDEO);
	
	bool running = true;

	while (running)
	{
		SDL_Event event = { 0 };
		
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
	}

	//system("PAUSE");

	return 0;
}