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
		constexpr const char *COLOR_CHANGE_SIXTH_PART = "W    ";

		constexpr const char *PROCEED_FIRST_PART { "PRESS    " };
		constexpr const char *PROCEED_SECOND_PART = "ENTER    ";
		constexpr const char *PROCEED_THIRD_PART = "TO    BEGIN";

		constexpr const char *SELECTED_ROM { "SELECTED    ROM    FILE" };
		constexpr const char *SELECTED_COLOR { "SELECTED    COLOR" };

		constexpr int WIDTH = Chip8CPU::DISPLAY_WIDTH * Chip8CPU::DISPLAY_PIXEL_SCALE;
		constexpr int HEIGHT = Chip8CPU::DISPLAY_HEIGHT * Chip8CPU::DISPLAY_PIXEL_SCALE;

		constexpr uint8_t NUMBER_OF_ROMS { 4 };
		constexpr uint8_t NUMBER_OF_COLORS { 5 };

		static constexpr uint8_t WHITE { 0 };
		static constexpr uint8_t RED { 1 };
		static constexpr uint8_t GREEN { 2 };
		static constexpr uint8_t YELLOW { 3 };
		static constexpr uint8_t BLUE { 4 };

		/* ROMS */
		constexpr std::array<const char *, NUMBER_OF_ROMS> roms
				{
						"TETRIS",
						"TICTAC",
						"INVADERS",
						"GUESS"
				};

		constexpr std::array<const char *, NUMBER_OF_COLORS> colors
				{
						"WHITE",
						"RED",
						"GREEN",
						"YELLOW",
						"BLUE"
				};

		int8_t rom_index { 0 };

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
		TTF_Font *font_type_large = TTF_OpenFont(FONT, 50);
		TTF_Font *font_type_medium = TTF_OpenFont(FONT, 35);
		TTF_Font *font_type_small = TTF_OpenFont(FONT, 25);

		/* Colors */
		SDL_Color white_color = { 255, 255, 255, 255 };
		SDL_Color red_color = { 255, 0, 0, 255 };
		SDL_Color green_color = { 0, 255, 0, 255 };
		SDL_Color blue_color = { 0, 0, 255, 255 };
		SDL_Color yellow_color = { 255, 255, 0, 255 };

		/* Name */
		SDL_Surface *surface_1 = TTF_RenderText_Solid(font_type_large, NAME, white_color);
		SDL_Texture *texture_1 = SDL_CreateTextureFromSurface(renderer, surface_1);

		SDL_Rect r_1;
		r_1.x = 160;
		r_1.y = 0;
		r_1.w = surface_1->w;
		r_1.h = surface_1->h;

		SDL_FreeSurface(surface_1);

		/* Title */
		SDL_Surface *surface_2 = TTF_RenderText_Solid(font_type_large, TITLE_FIRST_PART, red_color);
		SDL_Texture *texture_2 = SDL_CreateTextureFromSurface(renderer, surface_2);

		SDL_Rect r_2;
		r_2.x = 290;
		r_2.y = 50;
		r_2.w = surface_2->w;
		r_2.h = surface_2->h;

		SDL_FreeSurface(surface_2);

		SDL_Surface *surface_3 = TTF_RenderText_Solid(font_type_large, TITLE_SECOND_PART, white_color);
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

		/* White */
		SDL_Surface *surface_16 = TTF_RenderText_Solid(font_type_small, COLOR_CHANGE_SIXTH_PART, white_color);
		SDL_Texture *texture_16 = SDL_CreateTextureFromSurface(renderer, surface_16);

		SDL_Rect r_16;
		r_16.x = 785;
		r_16.y = 455;
		r_16.w = surface_16->w;
		r_16.h = surface_16->h;

		SDL_FreeSurface(surface_16);

		/* Proceed */
		SDL_Surface *surface_9 = TTF_RenderText_Solid(font_type_small, PROCEED_FIRST_PART, white_color);
		SDL_Texture *texture_9 = SDL_CreateTextureFromSurface(renderer, surface_9);

		SDL_Rect r_9;
		r_9.x = 340;
		r_9.y = 425;
		r_9.w = surface_9->w;
		r_9.h = surface_9->h;

		SDL_FreeSurface(surface_9);

		SDL_Surface *surface_10 = TTF_RenderText_Solid(font_type_small, PROCEED_SECOND_PART, red_color);
		SDL_Texture *texture_10 = SDL_CreateTextureFromSurface(renderer, surface_10);

		SDL_Rect r_10;
		r_10.x = 420;
		r_10.y = 425;
		r_10.w = surface_10->w;
		r_10.h = surface_10->h;

		SDL_FreeSurface(surface_10);

		SDL_Surface *surface_11 = TTF_RenderText_Solid(font_type_small, PROCEED_THIRD_PART, white_color);
		SDL_Texture *texture_11 = SDL_CreateTextureFromSurface(renderer, surface_11);

		SDL_Rect r_11;
		r_11.x = 500;
		r_11.y = 425;
		r_11.w = surface_11->w;
		r_11.h = surface_11->h;

		SDL_FreeSurface(surface_11);

		/* Selected ROM */
		SDL_Surface *surface_12 = TTF_RenderText_Solid(font_type_medium, SELECTED_ROM, white_color);
		SDL_Texture *texture_12 = SDL_CreateTextureFromSurface(renderer, surface_12);

		SDL_Rect r_12;
		r_12.x = 260;
		r_12.y = 150;
		r_12.w = surface_12->w;
		r_12.h = surface_12->h;

		SDL_FreeSurface(surface_12);

		SDL_Surface *surface_13 = TTF_RenderText_Solid(font_type_medium, roms[rom_index], green_color);
		SDL_Texture *texture_13 = SDL_CreateTextureFromSurface(renderer, surface_13);

		SDL_Rect r_13;
		r_13.x = 590;
		r_13.y = 150;
		r_13.w = surface_13->w;
		r_13.h = surface_13->h;

		SDL_FreeSurface(surface_13);

		/* Selected Color */
		SDL_Surface *surface_14 = TTF_RenderText_Solid(font_type_medium, SELECTED_COLOR, white_color);
		SDL_Texture *texture_14 = SDL_CreateTextureFromSurface(renderer, surface_14);

		SDL_Rect r_14;
		r_14.x = 260;
		r_14.y = 185;
		r_14.w = surface_14->w;
		r_14.h = surface_14->h;

		SDL_FreeSurface(surface_14);

		SDL_Surface *surface_15 = TTF_RenderText_Solid(font_type_medium, colors[WHITE], white_color);
		SDL_Texture *texture_15 = SDL_CreateTextureFromSurface(renderer, surface_15);

		SDL_Rect r_15;
		r_15.x = 540;
		r_15.y = 185;
		r_15.w = surface_15->w;
		r_15.h = surface_15->h;

		SDL_FreeSurface(surface_15);

		/* Loop */

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

						if (scancode == SDL_SCANCODE_RIGHT)
						{
							SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
							SDL_RenderFillRect(renderer, &r_13);
							SDL_RenderPresent(renderer);

							rom_index = (rom_index + 1) % NUMBER_OF_ROMS;

							surface_13 = TTF_RenderText_Solid(font_type_medium, roms[rom_index], green_color);
							texture_13 = SDL_CreateTextureFromSurface(renderer, surface_13);
						}
						else if (scancode == SDL_SCANCODE_LEFT)
						{
							SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
							SDL_RenderFillRect(renderer, &r_13);
							SDL_RenderPresent(renderer);

							if (--rom_index < 0)
							{
								rom_index += NUMBER_OF_ROMS;
							}

							surface_13 = TTF_RenderText_Solid(font_type_medium, roms[rom_index], green_color);
							texture_13 = SDL_CreateTextureFromSurface(renderer, surface_13);
						}
						else if (scancode == SDL_SCANCODE_R)
						{
							SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
							SDL_RenderFillRect(renderer, &r_15);
							SDL_RenderPresent(renderer);

							color.r = 255;
							color.g = 0;
							color.b = 0;

							surface_15 = TTF_RenderText_Solid(font_type_medium, colors[RED], red_color);
							texture_15 = SDL_CreateTextureFromSurface(renderer, surface_15);
						}
						else if (scancode == SDL_SCANCODE_G)
						{
							SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
							SDL_RenderFillRect(renderer, &r_15);
							SDL_RenderPresent(renderer);

							color.r = 0;
							color.g = 255;
							color.b = 0;

							surface_15 = TTF_RenderText_Solid(font_type_medium, colors[GREEN], green_color);
							texture_15 = SDL_CreateTextureFromSurface(renderer, surface_15);
						}
						else if (scancode == SDL_SCANCODE_B)
						{
							SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
							SDL_RenderFillRect(renderer, &r_15);
							SDL_RenderPresent(renderer);

							color.r = 0;
							color.g = 0;
							color.b = 255;

							surface_15 = TTF_RenderText_Solid(font_type_medium, colors[BLUE], blue_color);
							texture_15 = SDL_CreateTextureFromSurface(renderer, surface_15);
						}
						else if (scancode == SDL_SCANCODE_Y)
						{
							SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
							SDL_RenderFillRect(renderer, &r_15);
							SDL_RenderPresent(renderer);

							color.r = 255;
							color.g = 255;
							color.b = 0;

							surface_15 = TTF_RenderText_Solid(font_type_medium, colors[YELLOW], yellow_color);
							texture_15 = SDL_CreateTextureFromSurface(renderer, surface_15);
						}
						else if (scancode == SDL_SCANCODE_W)
						{
							SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
							SDL_RenderFillRect(renderer, &r_15);
							SDL_RenderPresent(renderer);

							color.r = 255;
							color.g = 255;
							color.b = 255;

							surface_15 = TTF_RenderText_Solid(font_type_medium, colors[WHITE], white_color);
							texture_15 = SDL_CreateTextureFromSurface(renderer, surface_15);
						}
						else if (scancode == SDL_SCANCODE_ESCAPE)
						{
							SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
							SDL_RenderFillRect(renderer, &r_15);
							SDL_RenderPresent(renderer);

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
							SDL_DestroyTexture(texture_9);
							SDL_DestroyTexture(texture_10);
							SDL_DestroyTexture(texture_11);
							SDL_DestroyTexture(texture_12);
							SDL_DestroyTexture(texture_13);
							SDL_DestroyTexture(texture_14);
							SDL_DestroyTexture(texture_15);
							SDL_DestroyTexture(texture_16);
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
			SDL_RenderCopy(renderer, texture_2, nullptr, &r_2);
			SDL_RenderCopy(renderer, texture_3, nullptr, &r_3);
			SDL_RenderCopy(renderer, texture_4, nullptr, &r_4);
			SDL_RenderCopy(renderer, texture_5, nullptr, &r_5);
			SDL_RenderCopy(renderer, texture_6, nullptr, &r_6);
			SDL_RenderCopy(renderer, texture_7, nullptr, &r_7);
			SDL_RenderCopy(renderer, texture_8, nullptr, &r_8);
			SDL_RenderCopy(renderer, texture_9, nullptr, &r_9);
			SDL_RenderCopy(renderer, texture_10, nullptr, &r_10);
			SDL_RenderCopy(renderer, texture_11, nullptr, &r_11);
			SDL_RenderCopy(renderer, texture_12, nullptr, &r_12);
			SDL_RenderCopy(renderer, texture_13, nullptr, &r_13);
			SDL_RenderCopy(renderer, texture_14, nullptr, &r_14);
			SDL_RenderCopy(renderer, texture_15, nullptr, &r_15);
			SDL_RenderCopy(renderer, texture_16, nullptr, &r_16);
			SDL_RenderPresent(renderer);
		}

		TTF_Quit();

		SDL_DestroyTexture(texture_1);
		SDL_DestroyTexture(texture_2);
		SDL_DestroyTexture(texture_3);
		SDL_DestroyTexture(texture_4);
		SDL_DestroyTexture(texture_5);
		SDL_DestroyTexture(texture_6);
		SDL_DestroyTexture(texture_7);
		SDL_DestroyTexture(texture_8);
		SDL_DestroyTexture(texture_9);
		SDL_DestroyTexture(texture_10);
		SDL_DestroyTexture(texture_11);
		SDL_DestroyTexture(texture_12);
		SDL_DestroyTexture(texture_13);
		SDL_DestroyTexture(texture_14);
		SDL_DestroyTexture(texture_15);
		SDL_DestroyTexture(texture_16);
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
