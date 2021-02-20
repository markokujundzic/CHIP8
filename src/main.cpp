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
		constexpr const char *WINDOW_TITLE = "CHIP8 Menu";
		constexpr const char *FONT = "../fonts/Arcade Classic.ttf";
		constexpr const char *NAME = "Marko    Kujundzic    418    2016";
		constexpr const char *TITLE_FIRST_PART = "CHIP  8    ";
		constexpr const char *TITLE_SECOND_PART = "EMULATOR";

		constexpr int WIDTH = Chip8CPU::DISPLAY_WIDTH * Chip8CPU::DISPLAY_PIXEL_SCALE;
		constexpr int HEIGHT = Chip8CPU::DISPLAY_HEIGHT * Chip8CPU::DISPLAY_PIXEL_SCALE;

		SDL_Window *window = SDL_CreateWindow(WINDOW_TITLE,
		                                      SDL_WINDOWPOS_UNDEFINED,
		                                      SDL_WINDOWPOS_UNDEFINED,
		                                      WIDTH,
		                                      HEIGHT,
		                                      SDL_WINDOW_SHOWN);
		SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
		SDL_Event event;

		TTF_Init();

		TTF_Font *font_type = TTF_OpenFont(FONT, 50);

		SDL_Color white_color = { 255, 255, 255, 255 };
		SDL_Color red_color = { 255, 0, 0, 255 };

		SDL_Surface *surface_1 = TTF_RenderText_Solid(font_type, NAME, white_color);
		SDL_Texture *texture_1 = SDL_CreateTextureFromSurface(renderer, surface_1);

		SDL_Rect r_1;
		r_1.x = 160;
		r_1.y = 0;
		r_1.w = surface_1->w;
		r_1.h = surface_1->h;

		SDL_FreeSurface(surface_1);

		SDL_Surface *surface_2 = TTF_RenderText_Solid(font_type, TITLE_FIRST_PART, red_color);
		SDL_Texture *texture_2 = SDL_CreateTextureFromSurface(renderer, surface_2);

		SDL_Rect r_2;
		r_2.x = 290;
		r_2.y = 50;
		r_2.w = surface_2->w;
		r_2.h = surface_2->h;

		SDL_FreeSurface(surface_2);

		SDL_Surface *surface_3 = TTF_RenderText_Solid(font_type, TITLE_SECOND_PART, white_color);
		SDL_Texture *texture_3 = SDL_CreateTextureFromSurface(renderer, surface_3);

		SDL_Rect r_3;
		r_3.x = 460;
		r_3.y = 50;
		r_3.w = surface_3->w;
		r_3.h = surface_3->h;

		SDL_FreeSurface(surface_3);

		TTF_Quit();

		bool running { true };

		SDL_Color color { 255, 255, 255, 255 };

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

						if (scancode == SDL_SCANCODE_R)
						{
							color.r = 255;
							color.g = 0;
							color.b = 0;
						}
						else if (scancode == SDL_SCANCODE_G)
						{
							color.r = 0;
							color.g = 255;
							color.b = 0;
						}
						else if (scancode == SDL_SCANCODE_B)
						{
							color.r = 0;
							color.g = 0;
							color.b = 255;
						}
						else if (scancode == SDL_SCANCODE_Y)
						{
							color.r = 255;
							color.g = 255;
							color.b = 0;
						}
						else if (scancode == SDL_SCANCODE_ESCAPE)
						{
							running = false;
						}
						else if (scancode == SDL_SCANCODE_RETURN)
						{
							SDL_DestroyTexture(texture_1);
							SDL_DestroyTexture(texture_2);
							SDL_DestroyTexture(texture_3);
							SDL_DestroyRenderer(renderer);
							SDL_DestroyWindow(window);
							SDL_Quit();

							Chip8CPU emulator {};
							emulator.emulate(argv[1], color);

							running = false;
						}
					}
						break;
				}
			}

			SDL_RenderCopy(renderer, texture_1, nullptr, &r_1);
			SDL_RenderPresent(renderer);
			SDL_RenderCopy(renderer, texture_2, nullptr, &r_2);
			SDL_RenderPresent(renderer);
			SDL_RenderCopy(renderer, texture_3, nullptr, &r_3);
			SDL_RenderPresent(renderer);
		}

		SDL_DestroyTexture(texture_1);
		SDL_DestroyTexture(texture_2);
		SDL_DestroyTexture(texture_3);
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
