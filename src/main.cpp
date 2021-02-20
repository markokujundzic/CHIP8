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
		/* Names */
		constexpr const char *WINDOW_TITLE = "CHIP8 Menu";
		constexpr const char *FONT = "../fonts/Arcade Classic.ttf";
		constexpr const char *NAME = "Marko    Kujundzic    418    2016";
		constexpr const char *TITLE_FIRST_PART = "CHIP  8    ";
		constexpr const char *TITLE_SECOND_PART = "EMULATOR";
		constexpr const char *COLOR_CHANGE_FIRST_PART = "TO    CHANGE    THE    EMULATOR    COLOR    PRESS    ";
		constexpr const char *COLOR_CHANGE_SECOND_PART = "R    ";
		constexpr const char *COLOR_CHANGE_THIRD_PART = "G    ";
		constexpr const char *COLOR_CHANGE_FOURTH_PART = "Y    ";
		constexpr const char *COLOR_CHANGE_FIFTH_PART = "B    ";

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

		/* Fonts */
		TTF_Font *font_type_big = TTF_OpenFont(FONT, 50);
		TTF_Font *font_type_small = TTF_OpenFont(FONT, 25);

		/* Colors */
		SDL_Color white_color = { 255, 255, 255, 255 };
		SDL_Color red_color = { 255, 0, 0, 255 };
		SDL_Color green_color = { 0, 255, 0, 255 };
		SDL_Color blue_color = { 0, 0, 255, 255 };
		SDL_Color yellow_color = { 255, 255, 0, 255 };

		/* Name */
		SDL_Surface *surface_1 = TTF_RenderText_Solid(font_type_big, NAME, white_color);
		SDL_Texture *texture_1 = SDL_CreateTextureFromSurface(renderer, surface_1);

		SDL_Rect r_1;
		r_1.x = 160;
		r_1.y = 0;
		r_1.w = surface_1->w;
		r_1.h = surface_1->h;

		SDL_FreeSurface(surface_1);

		/* Title */
		SDL_Surface *surface_2 = TTF_RenderText_Solid(font_type_big, TITLE_FIRST_PART, red_color);
		SDL_Texture *texture_2 = SDL_CreateTextureFromSurface(renderer, surface_2);

		SDL_Rect r_2;
		r_2.x = 290;
		r_2.y = 50;
		r_2.w = surface_2->w;
		r_2.h = surface_2->h;

		SDL_FreeSurface(surface_2);

		SDL_Surface *surface_3 = TTF_RenderText_Solid(font_type_big, TITLE_SECOND_PART, white_color);
		SDL_Texture *texture_3 = SDL_CreateTextureFromSurface(renderer, surface_3);

		SDL_Rect r_3;
		r_3.x = 460;
		r_3.y = 50;
		r_3.w = surface_3->w;
		r_3.h = surface_3->h;

		SDL_FreeSurface(surface_3);

		/* Color change */

		SDL_Surface *surface_4 = TTF_RenderText_Solid(font_type_small, COLOR_CHANGE_FIRST_PART, white_color);
		SDL_Texture *texture_4 = SDL_CreateTextureFromSurface(renderer, surface_4);

		SDL_Rect r_4;
		r_4.x = 190;
		r_4.y = 455;
		r_4.w = surface_4->w;
		r_4.h = surface_4->h;

		SDL_FreeSurface(surface_4);

		/* Red */

		SDL_Surface *surface_5 = TTF_RenderText_Solid(font_type_small, COLOR_CHANGE_SECOND_PART, red_color);
		SDL_Texture *texture_5 = SDL_CreateTextureFromSurface(renderer, surface_5);

		SDL_Rect r_5;
		r_5.x = 670;
		r_5.y = 455;
		r_5.w = surface_5->w;
		r_5.h = surface_5->h;

		SDL_FreeSurface(surface_5);

		/* Green */

		SDL_Surface *surface_6 = TTF_RenderText_Solid(font_type_small, COLOR_CHANGE_THIRD_PART, green_color);
		SDL_Texture *texture_6 = SDL_CreateTextureFromSurface(renderer, surface_6);

		SDL_Rect r_6;
		r_6.x = 695;
		r_6.y = 455;
		r_6.w = surface_6->w;
		r_6.h = surface_6->h;

		SDL_FreeSurface(surface_6);

		/* Yellow */

		SDL_Surface *surface_7 = TTF_RenderText_Solid(font_type_small, COLOR_CHANGE_FOURTH_PART, yellow_color);
		SDL_Texture *texture_7 = SDL_CreateTextureFromSurface(renderer, surface_7);

		SDL_Rect r_7;
		r_7.x = 725;
		r_7.y = 455;
		r_7.w = surface_7->w;
		r_7.h = surface_7->h;

		SDL_FreeSurface(surface_7);

		/* Blue */

		SDL_Surface *surface_8 = TTF_RenderText_Solid(font_type_small, COLOR_CHANGE_FIFTH_PART, blue_color);
		SDL_Texture *texture_8 = SDL_CreateTextureFromSurface(renderer, surface_8);

		SDL_Rect r_8;
		r_8.x = 755;
		r_8.y = 455;
		r_8.w = surface_8->w;
		r_8.h = surface_8->h;

		SDL_FreeSurface(surface_8);

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
							SDL_DestroyTexture(texture_4);
							SDL_DestroyTexture(texture_5);
							SDL_DestroyTexture(texture_6);
							SDL_DestroyTexture(texture_7);
							SDL_DestroyTexture(texture_8);
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
			SDL_RenderCopy(renderer, texture_4, nullptr, &r_4);
			SDL_RenderPresent(renderer);
			SDL_RenderCopy(renderer, texture_5, nullptr, &r_5);
			SDL_RenderPresent(renderer);
			SDL_RenderCopy(renderer, texture_6, nullptr, &r_6);
			SDL_RenderPresent(renderer);
			SDL_RenderCopy(renderer, texture_7, nullptr, &r_7);
			SDL_RenderPresent(renderer);
			SDL_RenderCopy(renderer, texture_8, nullptr, &r_8);
			SDL_RenderPresent(renderer);
		}

		SDL_DestroyTexture(texture_1);
		SDL_DestroyTexture(texture_2);
		SDL_DestroyTexture(texture_3);
		SDL_DestroyTexture(texture_4);
		SDL_DestroyTexture(texture_5);
		SDL_DestroyTexture(texture_6);
		SDL_DestroyTexture(texture_7);
		SDL_DestroyTexture(texture_8);
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
