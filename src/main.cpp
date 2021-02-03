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
		emulator.emulate(argv[1]);

		emulator.draw_sprite(0, 0, 10);

		SDL_Init(SDL_INIT_EVERYTHING);

		SDL_Window *window = SDL_CreateWindow(
				"CHIP8 Emulator",
				SDL_WINDOWPOS_UNDEFINED,
				SDL_WINDOWPOS_UNDEFINED,
				Chip8CPU::DISPLAY_WIDTH * Chip8CPU::DISPLAY_PIXEL_SCALE,
				Chip8CPU::DISPLAY_HEIGHT * Chip8CPU::DISPLAY_PIXEL_SCALE,
				SDL_WINDOW_SHOWN
		);

		auto escape { false };

		SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_TEXTUREACCESS_TARGET);

		while (!escape)
		{
			SDL_Event event;

			while (SDL_PollEvent(&event))
			{
				switch (event.type)
				{
					case SDL_QUIT:
						escape = true;
						break;
					case SDL_KEYUP:
						if (Chip8CPU::get_keyboard_mapping_value(event.key.keysym.sym) == -1)
						{
							std::cout << "Key not recognized is up." << '\n';
						} else
						{
							std::cout << "Key " << Chip8CPU::get_keyboard_mapping_value(event.key.keysym.sym)
							          << " is up!"
							          << '\n';
						}
						break;
					case SDL_KEYDOWN:
						if (Chip8CPU::get_keyboard_mapping_value(event.key.keysym.sym) == -1)
						{
							std::cout << "Key not recognized is down." << '\n';
						} else
						{
							std::cout << "Key " << Chip8CPU::get_keyboard_mapping_value(event.key.keysym.sym)
							          << " is down!"
							          << '\n';
						}
						break;
				}
			}

			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
			SDL_RenderClear(renderer);
			SDL_SetRenderDrawColor(renderer, 250, 250, 250, 0);

			for (auto x = 0; x < Chip8CPU::DISPLAY_WIDTH; x++)
			{
				for (auto y = 0; y < Chip8CPU::DISPLAY_HEIGHT; y++)
				{
					if (emulator.is_pixel_set(x, y))
					{
						SDL_Rect r;
						r.x = x * Chip8CPU::DISPLAY_PIXEL_SCALE;
						r.y = y * Chip8CPU::DISPLAY_PIXEL_SCALE;
						r.w = Chip8CPU::DISPLAY_PIXEL_SCALE;
						r.h = Chip8CPU::DISPLAY_PIXEL_SCALE;
						SDL_RenderFillRect(renderer, &r);
					}
				}
			}

			SDL_RenderPresent(renderer);
			// emulator.timer_tick();
		}

		SDL_DestroyWindow(window);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return -1;
	}

	return 0;

	/*const char* TITLE = "Hello World SDL2 + TTF";
	const int WIDTH = 1280, HEIGHT = 720;

	SDL_Window *window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Event windowEvent;

	TTF_Init();

	TTF_Font *verdanaFont = TTF_OpenFont("../fonts/UbuntuMono-B.ttf", 50);
	SDL_Color textColor = { 255, 255, 255, 255 };
	SDL_Surface *textSurface = TTF_RenderText_Solid(verdanaFont, "Hello World", textColor);
	SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

	SDL_Rect textRect;
	textRect.x = 0;
	textRect.y = 0;
	textRect.w = textSurface->w;
	textRect.h = textSurface->h;

	SDL_FreeSurface(textSurface);

	SDL_Surface *textSurface1 = TTF_RenderText_Solid(verdanaFont, "Marak", textColor);
	SDL_Texture *textTexture1 = SDL_CreateTextureFromSurface(renderer, textSurface1);

	SDL_Rect textRect1;
	textRect1.x = 50;
	textRect1.y = 50;
	textRect1.w = textSurface1->w;
	textRect1.h = textSurface1->h;

	SDL_FreeSurface(textSurface1);

	TTF_Quit();

	bool isRunning = true;
	while (isRunning) {
		while(SDL_PollEvent(&windowEvent)) {
			switch (windowEvent.type) {
				case SDL_QUIT:
					isRunning = false;
					break;
			}
		}
		SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
		SDL_RenderPresent(renderer);
		SDL_RenderCopy(renderer, textTexture1, NULL, &textRect1);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyTexture(textTexture);
	SDL_DestroyTexture(textTexture1);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return EXIT_SUCCESS;*/
}
