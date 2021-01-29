#include <iostream>
#include <SDL2/SDL.h>

#include "Chip8CPU.h"

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		std::cerr << "Insufficient number of arguments supplied." << '\n';
		return -1;
	}

	try
	{
		Chip8CPU emulator {};
		emulator.load_rom(argv[1]);

		SDL_Init(SDL_INIT_EVERYTHING);

		SDL_Window *window = SDL_CreateWindow(
				"CHIP8 Emulator",
				SDL_WINDOWPOS_UNDEFINED,
				SDL_WINDOWPOS_UNDEFINED,
				640,
				320,
				SDL_WINDOW_SHOWN
		);

		auto escape { false };

		SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_TEXTUREACCESS_TARGET);

		while (!escape)
		{
			SDL_Event event;

			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
				{
					escape = true;
					break;
				}
			}

			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
			SDL_RenderClear(renderer);
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
			SDL_Rect r;
			r.x = 0;
			r.y = 0;
			r.w = 40;
			r.h = 40;
			SDL_RenderFillRect(renderer, &r);
			SDL_RenderPresent(renderer);
		}

		SDL_DestroyWindow(window);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return -1;
	}

	return 0;
}
