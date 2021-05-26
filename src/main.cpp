#include "Chip8CPU.h"

int main(int argc, char *argv[]) {
	if (argc < 2) {
		std::cerr << "Insufficient number of arguments supplied." << '\n';
		return EXIT_FAILURE;
	}

	try {
		/* TODO: Move all the code from main to Chip8Menu class */
		/* TODO: Add new window with controls for all games */

		/* Names */
		constexpr const char *WINDOW_TITLE { "CHIP8 Menu" };
		constexpr const char *FONT { "../fonts/Arcade Classic.ttf" };

		constexpr const char *NAME_FIRST_PART { "Marko    Kujundzic    " };
		constexpr const char *NAME_SECOND_PART { "418    2016" };

		constexpr const char *TITLE_FIRST_PART { "CHIP  8    " };
		constexpr const char *TITLE_SECOND_PART { "EMULATOR" };

		constexpr const char *COLOR_CHANGE_FIRST_PART { "TO    CHANGE    THE    EMULATOR    COLOR    PRESS    " };
		constexpr const char *COLOR_CHANGE_SECOND_PART { "R    " };
		constexpr const char *COLOR_CHANGE_THIRD_PART { "G    " };
		constexpr const char *COLOR_CHANGE_FOURTH_PART { "Y    " };
		constexpr const char *COLOR_CHANGE_FIFTH_PART { "B    " };
		constexpr const char *COLOR_CHANGE_SIXTH_PART { "W    " };

		constexpr const char *ROM_CHANGE_FIRST_PART { "TO    CHANGE    THE    EMULATOR    ROM    PRESS    " };
		constexpr const char *ROM_CHANGE_SECOND_PART { "LEFT    ARROW    " };
		constexpr const char *ROM_CHANGE_THIRD_PART { "OR    " };
		constexpr const char *ROM_CHANGE_FOURTH_PART { "RIGHT ARROW" };

		constexpr const char *PROCEED_FIRST_PART { "PRESS    " };
		constexpr const char *PROCEED_SECOND_PART { "ENTER    " };
		constexpr const char *PROCEED_THIRD_PART { "TO    BEGIN" };

		constexpr const char *SELECTED_ROM { "SELECTED    ROM    FILE" };
		constexpr const char *SELECTED_COLOR { "SELECTED    COLOR" };

		constexpr const char *MUTE_FIRST_PART { "TO    TURN    MUSIC    " };
		constexpr const char *MUTE_SECOND_PART { "ON    " };
		constexpr const char *MUTE_THIRD_PART { "OR    " };
		constexpr const char *MUTE_FOURTH_PART { "OFF    " };
		constexpr const char *MUTE_FIFTH_PART { "PRESS    " };
		constexpr const char *MUTE_SIXTH_PART { "S" };

		constexpr const char *HOW_TO_PLAY_FIRST_PART { "TO    SEE    HOW    TO    PLAY    EACH    ROM    PRESS    " };
		constexpr const char *HOW_TO_PLAY_SECOND_PART {"I"};

		constexpr const char *HOW_TO_PLAY {"HOW    TO    PLAY"};

		constexpr int WIDTH = Chip8CPU::DISPLAY_WIDTH * Chip8CPU::DISPLAY_PIXEL_SCALE;
		constexpr int HEIGHT = Chip8CPU::DISPLAY_HEIGHT * Chip8CPU::DISPLAY_PIXEL_SCALE;

		constexpr uint8_t NUMBER_OF_ROMS { 11 };
		constexpr uint8_t NUMBER_OF_COLORS { 5 };

		static constexpr uint8_t WHITE { 0 };
		static constexpr uint8_t RED { 1 };
		static constexpr uint8_t GREEN { 2 };
		static constexpr uint8_t YELLOW { 3 };
		static constexpr uint8_t BLUE { 4 };

		/* Music */
		Mix_Music *gMusic = nullptr;

		SDL_Init(SDL_INIT_AUDIO);
		Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

		gMusic = Mix_LoadMUS("../audio/song.wav");

		/* ROMS */
		constexpr std::array<const char *, NUMBER_OF_ROMS> roms
				{
						"TETRIS",
						"TICTAC",
						"INVADERS",
						"BLINKY",
						"BRIX",
						"MISSILE",
						"PONG",
						"PUZZLE",
						"UFO",
						"VBRIX",
						"SPACERACER"
				};

		/* Colors */
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
		SDL_Color purple_color = { 255, 0, 255, 255 };

		/* Name */
		SDL_Surface *surface_1 = TTF_RenderText_Solid(font_type_large, NAME_FIRST_PART, purple_color);
		SDL_Texture *texture_1 = SDL_CreateTextureFromSurface(renderer, surface_1);

		SDL_Rect r_1;
		r_1.x = 160;
		r_1.y = 0;
		r_1.w = surface_1->w;
		r_1.h = surface_1->h;

		SDL_FreeSurface(surface_1);

		SDL_Surface *surface_27 = TTF_RenderText_Solid(font_type_large, NAME_SECOND_PART, green_color);
		SDL_Texture *texture_27 = SDL_CreateTextureFromSurface(renderer, surface_27);

		SDL_Rect r_27;
		r_27.x = 590;
		r_27.y = 0;
		r_27.w = surface_27->w;
		r_27.h = surface_27->h;

		SDL_FreeSurface(surface_27);

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
		r_9.y = 270;
		r_9.w = surface_9->w;
		r_9.h = surface_9->h;

		SDL_FreeSurface(surface_9);

		SDL_Surface *surface_10 = TTF_RenderText_Solid(font_type_small, PROCEED_SECOND_PART, red_color);
		SDL_Texture *texture_10 = SDL_CreateTextureFromSurface(renderer, surface_10);

		SDL_Rect r_10;
		r_10.x = 420;
		r_10.y = 270;
		r_10.w = surface_10->w;
		r_10.h = surface_10->h;

		SDL_FreeSurface(surface_10);

		SDL_Surface *surface_11 = TTF_RenderText_Solid(font_type_small, PROCEED_THIRD_PART, white_color);
		SDL_Texture *texture_11 = SDL_CreateTextureFromSurface(renderer, surface_11);

		SDL_Rect r_11;
		r_11.x = 500;
		r_11.y = 270;
		r_11.w = surface_11->w;
		r_11.h = surface_11->h;

		SDL_FreeSurface(surface_11);

		/* Selected ROM */
		SDL_Surface *surface_12 = TTF_RenderText_Solid(font_type_medium, SELECTED_ROM, white_color);
		SDL_Texture *texture_12 = SDL_CreateTextureFromSurface(renderer, surface_12);

		SDL_Rect r_12;
		r_12.x = 255;
		r_12.y = 150;
		r_12.w = surface_12->w;
		r_12.h = surface_12->h;

		SDL_FreeSurface(surface_12);

		SDL_Surface *surface_13 = TTF_RenderText_Solid(font_type_medium, roms[rom_index], green_color);
		SDL_Texture *texture_13 = SDL_CreateTextureFromSurface(renderer, surface_13);

		SDL_Rect r_13;
		r_13.x = 585;
		r_13.y = 150;
		r_13.w = surface_13->w;
		r_13.h = surface_13->h;

		SDL_FreeSurface(surface_13);

		/* Change ROM */
		SDL_Surface *surface_17 = TTF_RenderText_Solid(font_type_small, ROM_CHANGE_FIRST_PART, white_color);
		SDL_Texture *texture_17 = SDL_CreateTextureFromSurface(renderer, surface_17);

		SDL_Rect r_17;
		r_17.x = 100;
		r_17.y = 415;
		r_17.w = surface_17->w;
		r_17.h = surface_17->h;

		SDL_FreeSurface(surface_17);

		SDL_Surface *surface_18 = TTF_RenderText_Solid(font_type_small, ROM_CHANGE_SECOND_PART, yellow_color);
		SDL_Texture *texture_18 = SDL_CreateTextureFromSurface(renderer, surface_18);

		SDL_Rect r_18;
		r_18.x = 550;
		r_18.y = 415;
		r_18.w = surface_18->w;
		r_18.h = surface_18->h;

		SDL_FreeSurface(surface_18);

		SDL_Surface *surface_19 = TTF_RenderText_Solid(font_type_small, ROM_CHANGE_THIRD_PART, white_color);
		SDL_Texture *texture_19 = SDL_CreateTextureFromSurface(renderer, surface_19);

		SDL_Rect r_19;
		r_19.x = 700;
		r_19.y = 415;
		r_19.w = surface_19->w;
		r_19.h = surface_19->h;

		SDL_FreeSurface(surface_19);

		SDL_Surface *surface_20 = TTF_RenderText_Solid(font_type_small, ROM_CHANGE_FOURTH_PART, yellow_color);
		SDL_Texture *texture_20 = SDL_CreateTextureFromSurface(renderer, surface_20);

		SDL_Rect r_20;
		r_20.x = 740;
		r_20.y = 415;
		r_20.w = surface_20->w;
		r_20.h = surface_20->h;

		SDL_FreeSurface(surface_20);

		/* Selected Color */
		SDL_Surface *surface_14 = TTF_RenderText_Solid(font_type_medium, SELECTED_COLOR, white_color);
		SDL_Texture *texture_14 = SDL_CreateTextureFromSurface(renderer, surface_14);

		SDL_Rect r_14;
		r_14.x = 310;
		r_14.y = 185;
		r_14.w = surface_14->w;
		r_14.h = surface_14->h;

		SDL_FreeSurface(surface_14);

		SDL_Surface *surface_15 = TTF_RenderText_Solid(font_type_medium, colors[RED], red_color);
		SDL_Texture *texture_15 = SDL_CreateTextureFromSurface(renderer, surface_15);

		SDL_Rect r_15;
		r_15.x = 590;
		r_15.y = 185;
		r_15.w = surface_15->w;
		r_15.h = surface_15->h;

		SDL_FreeSurface(surface_15);

		/* Mute music */
		SDL_Surface *surface_21 = TTF_RenderText_Solid(font_type_small, MUTE_FIRST_PART, white_color);
		SDL_Texture *texture_21 = SDL_CreateTextureFromSurface(renderer, surface_21);

		SDL_Rect r_21;
		r_21.x = 280;
		r_21.y = 375;
		r_21.w = surface_21->w;
		r_21.h = surface_21->h;

		SDL_FreeSurface(surface_21);

		SDL_Surface *surface_22 = TTF_RenderText_Solid(font_type_small, MUTE_SECOND_PART, purple_color);
		SDL_Texture *texture_22 = SDL_CreateTextureFromSurface(renderer, surface_22);

		SDL_Rect r_22;
		r_22.x = 470;
		r_22.y = 375;
		r_22.w = surface_22->w;
		r_22.h = surface_22->h;

		SDL_FreeSurface(surface_22);

		SDL_Surface *surface_23 = TTF_RenderText_Solid(font_type_small, MUTE_THIRD_PART, white_color);
		SDL_Texture *texture_23 = SDL_CreateTextureFromSurface(renderer, surface_23);

		SDL_Rect r_23;
		r_23.x = 510;
		r_23.y = 375;
		r_23.w = surface_23->w;
		r_23.h = surface_23->h;

		SDL_FreeSurface(surface_23);

		SDL_Surface *surface_24 = TTF_RenderText_Solid(font_type_small, MUTE_FOURTH_PART, purple_color);
		SDL_Texture *texture_24 = SDL_CreateTextureFromSurface(renderer, surface_24);

		SDL_Rect r_24;
		r_24.x = 550;
		r_24.y = 375;
		r_24.w = surface_24->w;
		r_24.h = surface_24->h;

		SDL_FreeSurface(surface_24);

		SDL_Surface *surface_25 = TTF_RenderText_Solid(font_type_small, MUTE_FIFTH_PART, white_color);
		SDL_Texture *texture_25 = SDL_CreateTextureFromSurface(renderer, surface_25);

		SDL_Rect r_25;
		r_25.x = 600;
		r_25.y = 375;
		r_25.w = surface_25->w;
		r_25.h = surface_25->h;

		SDL_FreeSurface(surface_25);

		SDL_Surface *surface_26 = TTF_RenderText_Solid(font_type_small, MUTE_SIXTH_PART, blue_color);
		SDL_Texture *texture_26 = SDL_CreateTextureFromSurface(renderer, surface_26);

		SDL_Rect r_26;
		r_26.x = 680;
		r_26.y = 375;
		r_26.w = surface_26->w;
		r_26.h = surface_26->h;

		SDL_FreeSurface(surface_26);

		/* How to play */
		SDL_Surface *surface_28 = TTF_RenderText_Solid(font_type_small, HOW_TO_PLAY_FIRST_PART, white_color);
		SDL_Texture *texture_28 = SDL_CreateTextureFromSurface(renderer, surface_28);

		SDL_Rect r_28;
		r_28.x = 250;
		r_28.y = 340;
		r_28.w = surface_28->w;
		r_28.h = surface_28->h;

		SDL_FreeSurface(surface_28);

		SDL_Surface *surface_29 = TTF_RenderText_Solid(font_type_small, HOW_TO_PLAY_SECOND_PART, green_color);
		SDL_Texture *texture_29 = SDL_CreateTextureFromSurface(renderer, surface_29);

		SDL_Rect r_29;
		r_29.x = 710;
		r_29.y = 340;
		r_29.w = surface_29->w;
		r_29.h = surface_29->h;

		SDL_FreeSurface(surface_29);

		Mix_PlayMusic(gMusic, -1);

		/* Loop */
		bool running { true };

		SDL_Color color { 255, 0, 0, 255 };

		while (running) {
			while (SDL_PollEvent(&event)) {
				switch (event.type) {
					case SDL_QUIT:
						running = false;
						break;
					case SDL_KEYDOWN: {
						auto& scancode = event.key.keysym.scancode;

						if (scancode == SDL_SCANCODE_RIGHT) {
							SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
							SDL_RenderFillRect(renderer, &r_13);
							SDL_RenderPresent(renderer);

							rom_index = (rom_index + 1) % NUMBER_OF_ROMS;

							surface_13 = TTF_RenderText_Solid(font_type_medium, roms[rom_index], green_color);
							texture_13 = SDL_CreateTextureFromSurface(renderer, surface_13);
						}
						else if (scancode == SDL_SCANCODE_LEFT) {
							SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
							SDL_RenderFillRect(renderer, &r_13);
							SDL_RenderPresent(renderer);

							if (--rom_index < 0) {
								rom_index += NUMBER_OF_ROMS;
							}

							surface_13 = TTF_RenderText_Solid(font_type_medium, roms[rom_index], green_color);
							texture_13 = SDL_CreateTextureFromSurface(renderer, surface_13);
						}
						else if (scancode == SDL_SCANCODE_R) {
							SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
							SDL_RenderFillRect(renderer, &r_15);
							SDL_RenderPresent(renderer);

							color.r = 255;
							color.g = 0;
							color.b = 0;

							surface_15 = TTF_RenderText_Solid(font_type_medium, colors[RED], red_color);
							texture_15 = SDL_CreateTextureFromSurface(renderer, surface_15);
						}
						else if (scancode == SDL_SCANCODE_G) {
							SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
							SDL_RenderFillRect(renderer, &r_15);
							SDL_RenderPresent(renderer);

							color.r = 0;
							color.g = 255;
							color.b = 0;

							surface_15 = TTF_RenderText_Solid(font_type_medium, colors[GREEN], green_color);
							texture_15 = SDL_CreateTextureFromSurface(renderer, surface_15);
						}
						else if (scancode == SDL_SCANCODE_B) {
							SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
							SDL_RenderFillRect(renderer, &r_15);
							SDL_RenderPresent(renderer);

							color.r = 0;
							color.g = 0;
							color.b = 255;

							surface_15 = TTF_RenderText_Solid(font_type_medium, colors[BLUE], blue_color);
							texture_15 = SDL_CreateTextureFromSurface(renderer, surface_15);
						}
						else if (scancode == SDL_SCANCODE_Y) {
							SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
							SDL_RenderFillRect(renderer, &r_15);
							SDL_RenderPresent(renderer);

							color.r = 255;
							color.g = 255;
							color.b = 0;

							surface_15 = TTF_RenderText_Solid(font_type_medium, colors[YELLOW], yellow_color);
							texture_15 = SDL_CreateTextureFromSurface(renderer, surface_15);
						}
						else if (scancode == SDL_SCANCODE_W) {
							SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
							SDL_RenderFillRect(renderer, &r_15);
							SDL_RenderPresent(renderer);

							color.r = 255;
							color.g = 255;
							color.b = 255;

							surface_15 = TTF_RenderText_Solid(font_type_medium, colors[WHITE], white_color);
							texture_15 = SDL_CreateTextureFromSurface(renderer, surface_15);
						}
						else if (scancode == SDL_SCANCODE_ESCAPE) {
							SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
							SDL_RenderFillRect(renderer, &r_15);
							SDL_RenderPresent(renderer);

							running = false;
						}
						else if (scancode == SDL_SCANCODE_S) {
							if (Mix_PausedMusic() == 1) {
								Mix_ResumeMusic();
							}
							else {
								Mix_PauseMusic();
							}
						}
						else if (scancode == SDL_SCANCODE_I) {
							SDL_Init(SDL_INIT_EVERYTHING);

							SDL_Window *new_window = SDL_CreateWindow(
									"Chip 8 How to play",
									SDL_WINDOWPOS_UNDEFINED,
									SDL_WINDOWPOS_UNDEFINED,
									Chip8CPU::DISPLAY_WIDTH * Chip8CPU::DISPLAY_PIXEL_SCALE,
									Chip8CPU::DISPLAY_HEIGHT * Chip8CPU::DISPLAY_PIXEL_SCALE,
									SDL_WINDOW_INPUT_FOCUS);
							SDL_Renderer *new_renderer = SDL_CreateRenderer(new_window, -1, SDL_TEXTUREACCESS_TARGET);

							SDL_Event new_event;

							/* Title */
							SDL_Surface *surface_30 = TTF_RenderText_Solid(font_type_large, HOW_TO_PLAY, purple_color);
							SDL_Texture *texture_30 = SDL_CreateTextureFromSurface(new_renderer, surface_30);

							SDL_Rect r_30;
							r_30.x = 350;
							r_30.y = 0;
							r_30.w = surface_30->w;
							r_30.h = surface_30->h;

							SDL_FreeSurface(surface_30);

							bool new_running { true };

							while (new_running) {
								while (SDL_PollEvent(&new_event)) {
									switch (new_event.type) {
										case SDL_QUIT:
											new_running = false;
											break;
										case SDL_KEYDOWN: {
											auto& new_scancode = new_event.key.keysym.scancode;

											if (new_scancode == SDL_SCANCODE_Q) {
												new_running = false;
												break;
											}
										}
											break;
									}
								}
								SDL_RenderCopy(new_renderer, texture_30, nullptr, &r_30);
								SDL_RenderPresent(new_renderer);
							}

							SDL_DestroyTexture(texture_30);
							SDL_DestroyRenderer(new_renderer);
							SDL_DestroyWindow(new_window);
						}
						else if (scancode == SDL_SCANCODE_RETURN) {
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
							SDL_DestroyTexture(texture_17);
							SDL_DestroyTexture(texture_18);
							SDL_DestroyTexture(texture_19);
							SDL_DestroyTexture(texture_20);
							SDL_DestroyTexture(texture_21);
							SDL_DestroyTexture(texture_22);
							SDL_DestroyTexture(texture_23);
							SDL_DestroyTexture(texture_24);
							SDL_DestroyTexture(texture_25);
							SDL_DestroyTexture(texture_26);
							SDL_DestroyTexture(texture_27);
							SDL_DestroyTexture(texture_28);
							SDL_DestroyTexture(texture_29);
							SDL_DestroyRenderer(renderer);
							SDL_DestroyWindow(window);

							Mix_Quit();
							SDL_Quit();
							TTF_Quit();

							Chip8CPU emulator {};
							std::string path = std::string { "../roms/" } + roms[rom_index];

							uint8_t beep = 10;
							uint8_t sleep = 10;

							if (strcmp(roms[rom_index], "INVADERS") == 0 ||
							    strcmp(roms[rom_index], "BLINKY") == 0 ||
							    strcmp(roms[rom_index], "VBRIX") == 0 ||
							    strcmp(roms[rom_index], "SPACERACER") == 0) {
								sleep = 1;
							}

							emulator.emulate(path, color, beep, sleep);

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
			SDL_RenderCopy(renderer, texture_17, nullptr, &r_17);
			SDL_RenderCopy(renderer, texture_18, nullptr, &r_18);
			SDL_RenderCopy(renderer, texture_19, nullptr, &r_19);
			SDL_RenderCopy(renderer, texture_20, nullptr, &r_20);
			SDL_RenderCopy(renderer, texture_21, nullptr, &r_21);
			SDL_RenderCopy(renderer, texture_22, nullptr, &r_22);
			SDL_RenderCopy(renderer, texture_23, nullptr, &r_23);
			SDL_RenderCopy(renderer, texture_24, nullptr, &r_24);
			SDL_RenderCopy(renderer, texture_25, nullptr, &r_25);
			SDL_RenderCopy(renderer, texture_26, nullptr, &r_26);
			SDL_RenderCopy(renderer, texture_27, nullptr, &r_27);
			SDL_RenderCopy(renderer, texture_28, nullptr, &r_28);
			SDL_RenderCopy(renderer, texture_29, nullptr, &r_29);
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
		SDL_DestroyTexture(texture_9);
		SDL_DestroyTexture(texture_10);
		SDL_DestroyTexture(texture_11);
		SDL_DestroyTexture(texture_12);
		SDL_DestroyTexture(texture_13);
		SDL_DestroyTexture(texture_14);
		SDL_DestroyTexture(texture_15);
		SDL_DestroyTexture(texture_16);
		SDL_DestroyTexture(texture_17);
		SDL_DestroyTexture(texture_18);
		SDL_DestroyTexture(texture_19);
		SDL_DestroyTexture(texture_20);
		SDL_DestroyTexture(texture_21);
		SDL_DestroyTexture(texture_22);
		SDL_DestroyTexture(texture_23);
		SDL_DestroyTexture(texture_24);
		SDL_DestroyTexture(texture_25);
		SDL_DestroyTexture(texture_26);
		SDL_DestroyTexture(texture_27);
		SDL_DestroyTexture(texture_28);
		SDL_DestroyTexture(texture_29);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);

		Mix_FreeMusic(gMusic);

		Mix_Quit();
		SDL_Quit();
		TTF_Quit();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
