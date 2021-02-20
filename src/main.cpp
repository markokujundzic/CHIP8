#include "Chip8CPU.h"

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		std::cerr << "Insufficient number of arguments supplied." << '\n';
		return EXIT_FAILURE;
	}

	try
	{
		constexpr const char *TITLE = "CHIP8 Menu";
		constexpr const char *FONT = "../fonts/Arcade Classic.ttf";
		constexpr const char *NAME = "Marko    Kujundzic    418    2016";
		constexpr const char *emu = "CHIP8    emulator";

		constexpr int WIDTH = Chip8CPU::DISPLAY_WIDTH * Chip8CPU::DISPLAY_PIXEL_SCALE;
		constexpr int HEIGHT = Chip8CPU::DISPLAY_HEIGHT * Chip8CPU::DISPLAY_PIXEL_SCALE;

		SDL_Window *window = SDL_CreateWindow(TITLE,
		                                      SDL_WINDOWPOS_UNDEFINED,
		                                      SDL_WINDOWPOS_UNDEFINED,
		                                      WIDTH,
		                                      HEIGHT,
		                                      SDL_WINDOW_SHOWN);
		SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
		SDL_Event event;

		TTF_Init();

		TTF_Font *verdanaFont = TTF_OpenFont(FONT, 50);
		SDL_Color textColor = { 255, 0, 0, 255 };
		SDL_Surface *textSurface = TTF_RenderText_Solid(verdanaFont, NAME, textColor);
		SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

		SDL_Rect textRect;
		textRect.x = 160;
		textRect.y = 0;
		textRect.w = textSurface->w;
		textRect.h = textSurface->h;

		SDL_FreeSurface(textSurface);

		SDL_Surface *textSurface1 = TTF_RenderText_Solid(verdanaFont, emu, textColor);
		SDL_Texture *textTexture1 = SDL_CreateTextureFromSurface(renderer, textSurface1);

		SDL_Rect textRect1;
		textRect1.x = 290;
		textRect1.y = 50;
		textRect1.w = textSurface1->w;
		textRect1.h = textSurface1->h;

		SDL_FreeSurface(textSurface1);

		TTF_Quit();

		bool running { true };

		while (running)
		{
			while (SDL_PollEvent(&event))
			{
				switch (event.type)
				{
					case SDL_QUIT:
						running = false;
						break;
					case SDL_KEYDOWN:
					{
						auto& scancode = event.key.keysym.scancode;

						if (scancode == SDL_SCANCODE_ESCAPE)
						{
							running = false;
						}
						else if (scancode == SDL_SCANCODE_RETURN)
						{
							SDL_DestroyTexture(textTexture);
							SDL_DestroyTexture(textTexture1);
							SDL_DestroyRenderer(renderer);
							SDL_DestroyWindow(window);
							SDL_Quit();

							Chip8CPU emulator {};
							emulator.emulate(argv[1]);

							running = false;
							break;
						}
					}
						break;
				}
			}

			SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
			SDL_RenderPresent(renderer);
			SDL_RenderCopy(renderer, textTexture1, nullptr, &textRect1);
			SDL_RenderPresent(renderer);
		}

		SDL_DestroyTexture(textTexture);
		SDL_DestroyTexture(textTexture1);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
