#include "Chip8Menu.h"

constexpr std::array<const char *, CHIP8Menu::NUMBER_OF_ROMS> CHIP8Menu::roms;

constexpr std::array<const char *, CHIP8Menu::NUMBER_OF_COLORS> CHIP8Menu::colors;

void CHIP8Menu::initialize_music() {
	SDL_Init(SDL_INIT_EVERYTHING);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	music = Mix_LoadMUS("../audio/song.wav");
}

void CHIP8Menu::sdl_initialize(SDL_Window **window, SDL_Renderer **renderer, const char *title_name) {
	*window = SDL_CreateWindow(
			title_name,
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			WIDTH,
			HEIGHT,
			SDL_WINDOW_SHOWN);
	*renderer = SDL_CreateRenderer(*window, -1, 0);
}

void CHIP8Menu::sdl_restore(SDL_Window **window, SDL_Renderer **renderer) {
	SDL_DestroyWindow(*window);
	SDL_DestroyRenderer(*renderer);
}

void CHIP8Menu::sdl_rect_init(SDL_Rect& rect, int x, int y, const SDL_Surface *surface) {
	rect.x = x;
	rect.y = y;
	rect.w = surface->w;
	rect.h = surface->h;
}

void CHIP8Menu::render_menu() {
	initialize_music();

	int8_t rom_index { 0 };

	SDL_Window *window;
	SDL_Renderer *renderer;

	sdl_initialize(&window, &renderer, WINDOW_TITLE);

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
	sdl_rect_init(r_1, 160, 0, surface_1);
	SDL_FreeSurface(surface_1);

	SDL_Surface *surface_27 = TTF_RenderText_Solid(font_type_large, NAME_SECOND_PART, green_color);
	SDL_Texture *texture_27 = SDL_CreateTextureFromSurface(renderer, surface_27);

	SDL_Rect r_27;
	sdl_rect_init(r_27, 590, 0, surface_27);
	SDL_FreeSurface(surface_27);

	/* Title */
	SDL_Surface *surface_2 = TTF_RenderText_Solid(font_type_large, TITLE_FIRST_PART, red_color);
	SDL_Texture *texture_2 = SDL_CreateTextureFromSurface(renderer, surface_2);

	SDL_Rect r_2;
	sdl_rect_init(r_2, 290, 50, surface_2);
	SDL_FreeSurface(surface_2);

	SDL_Surface *surface_3 = TTF_RenderText_Solid(font_type_large, TITLE_SECOND_PART, white_color);
	SDL_Texture *texture_3 = SDL_CreateTextureFromSurface(renderer, surface_3);

	SDL_Rect r_3;
	sdl_rect_init(r_3, 460, 50, surface_3);
	SDL_FreeSurface(surface_3);

	/* Color change */
	SDL_Surface *surface_4 = TTF_RenderText_Solid(font_type_small, COLOR_CHANGE_FIRST_PART, white_color);
	SDL_Texture *texture_4 = SDL_CreateTextureFromSurface(renderer, surface_4);

	SDL_Rect r_4;
	sdl_rect_init(r_4, 190, 455, surface_4);
	SDL_FreeSurface(surface_4);

	/* Red */
	SDL_Surface *surface_5 = TTF_RenderText_Solid(font_type_small, COLOR_CHANGE_SECOND_PART, red_color);
	SDL_Texture *texture_5 = SDL_CreateTextureFromSurface(renderer, surface_5);

	SDL_Rect r_5;
	sdl_rect_init(r_5, 670, 455, surface_5);
	SDL_FreeSurface(surface_5);

	/* Green */
	SDL_Surface *surface_6 = TTF_RenderText_Solid(font_type_small, COLOR_CHANGE_THIRD_PART, green_color);
	SDL_Texture *texture_6 = SDL_CreateTextureFromSurface(renderer, surface_6);

	SDL_Rect r_6;
	sdl_rect_init(r_6, 695, 455, surface_6);
	SDL_FreeSurface(surface_6);

	/* Yellow */
	SDL_Surface *surface_7 = TTF_RenderText_Solid(font_type_small, COLOR_CHANGE_FOURTH_PART, yellow_color);
	SDL_Texture *texture_7 = SDL_CreateTextureFromSurface(renderer, surface_7);

	SDL_Rect r_7;
	sdl_rect_init(r_7, 735, 455, surface_7);
	SDL_FreeSurface(surface_7);

	/* Blue */
	SDL_Surface *surface_8 = TTF_RenderText_Solid(font_type_small, COLOR_CHANGE_FIFTH_PART, blue_color);
	SDL_Texture *texture_8 = SDL_CreateTextureFromSurface(renderer, surface_8);

	SDL_Rect r_8;
	sdl_rect_init(r_8, 755, 455, surface_8);
	SDL_FreeSurface(surface_8);

	/* White */
	SDL_Surface *surface_16 = TTF_RenderText_Solid(font_type_small, COLOR_CHANGE_SIXTH_PART, white_color);
	SDL_Texture *texture_16 = SDL_CreateTextureFromSurface(renderer, surface_16);

	SDL_Rect r_16;
	sdl_rect_init(r_16, 785, 455, surface_16);
	SDL_FreeSurface(surface_16);

	/* Proceed */
	SDL_Surface *surface_9 = TTF_RenderText_Solid(font_type_small, PROCEED_FIRST_PART, white_color);
	SDL_Texture *texture_9 = SDL_CreateTextureFromSurface(renderer, surface_9);

	SDL_Rect r_9;
	sdl_rect_init(r_9, 340, 270, surface_9);
	SDL_FreeSurface(surface_9);

	SDL_Surface *surface_10 = TTF_RenderText_Solid(font_type_small, PROCEED_SECOND_PART, red_color);
	SDL_Texture *texture_10 = SDL_CreateTextureFromSurface(renderer, surface_10);

	SDL_Rect r_10;
	sdl_rect_init(r_10, 420, 270, surface_10);
	SDL_FreeSurface(surface_10);

	SDL_Surface *surface_11 = TTF_RenderText_Solid(font_type_small, PROCEED_THIRD_PART, white_color);
	SDL_Texture *texture_11 = SDL_CreateTextureFromSurface(renderer, surface_11);

	SDL_Rect r_11;
	sdl_rect_init(r_11, 500, 270, surface_11);
	SDL_FreeSurface(surface_11);

	/* Selected ROM */
	SDL_Surface *surface_12 = TTF_RenderText_Solid(font_type_medium, SELECTED_ROM, white_color);
	SDL_Texture *texture_12 = SDL_CreateTextureFromSurface(renderer, surface_12);

	SDL_Rect r_12;
	sdl_rect_init(r_12, 255, 150, surface_12);
	SDL_FreeSurface(surface_12);

	SDL_Surface *surface_13 = TTF_RenderText_Solid(font_type_medium, roms[rom_index], green_color);
	SDL_Texture *texture_13 = SDL_CreateTextureFromSurface(renderer, surface_13);

	SDL_Rect r_13;
	sdl_rect_init(r_13, 585, 150, surface_13);
	SDL_FreeSurface(surface_13);

	/* Change ROM */
	SDL_Surface *surface_17 = TTF_RenderText_Solid(font_type_small, ROM_CHANGE_FIRST_PART, white_color);
	SDL_Texture *texture_17 = SDL_CreateTextureFromSurface(renderer, surface_17);

	SDL_Rect r_17;
	sdl_rect_init(r_17, 100, 415, surface_17);
	SDL_FreeSurface(surface_17);

	SDL_Surface *surface_18 = TTF_RenderText_Solid(font_type_small, ROM_CHANGE_SECOND_PART, yellow_color);
	SDL_Texture *texture_18 = SDL_CreateTextureFromSurface(renderer, surface_18);

	SDL_Rect r_18;
	sdl_rect_init(r_18, 550, 415, surface_18);
	SDL_FreeSurface(surface_18);

	SDL_Surface *surface_19 = TTF_RenderText_Solid(font_type_small, ROM_CHANGE_THIRD_PART, white_color);
	SDL_Texture *texture_19 = SDL_CreateTextureFromSurface(renderer, surface_19);

	SDL_Rect r_19;
	sdl_rect_init(r_19, 700, 415, surface_19);
	SDL_FreeSurface(surface_19);

	SDL_Surface *surface_20 = TTF_RenderText_Solid(font_type_small, ROM_CHANGE_FOURTH_PART, yellow_color);
	SDL_Texture *texture_20 = SDL_CreateTextureFromSurface(renderer, surface_20);

	SDL_Rect r_20;
	sdl_rect_init(r_20, 740, 415, surface_20);
	SDL_FreeSurface(surface_20);

	/* Selected Color */
	SDL_Surface *surface_14 = TTF_RenderText_Solid(font_type_medium, SELECTED_COLOR, white_color);
	SDL_Texture *texture_14 = SDL_CreateTextureFromSurface(renderer, surface_14);

	SDL_Rect r_14;
	sdl_rect_init(r_14, 310, 185, surface_14);
	SDL_FreeSurface(surface_14);

	SDL_Surface *surface_15 = TTF_RenderText_Solid(font_type_medium, colors[RED], red_color);
	SDL_Texture *texture_15 = SDL_CreateTextureFromSurface(renderer, surface_15);

	SDL_Rect r_15;
	sdl_rect_init(r_15, 590, 185, surface_15);
	SDL_FreeSurface(surface_15);

	/* Mute music */
	SDL_Surface *surface_21 = TTF_RenderText_Solid(font_type_small, MUTE_FIRST_PART, white_color);
	SDL_Texture *texture_21 = SDL_CreateTextureFromSurface(renderer, surface_21);

	SDL_Rect r_21;
	sdl_rect_init(r_21, 280, 375, surface_21);
	SDL_FreeSurface(surface_21);

	SDL_Surface *surface_22 = TTF_RenderText_Solid(font_type_small, MUTE_SECOND_PART, purple_color);
	SDL_Texture *texture_22 = SDL_CreateTextureFromSurface(renderer, surface_22);

	SDL_Rect r_22;
	sdl_rect_init(r_22, 470, 375, surface_22);
	SDL_FreeSurface(surface_22);

	SDL_Surface *surface_23 = TTF_RenderText_Solid(font_type_small, MUTE_THIRD_PART, white_color);
	SDL_Texture *texture_23 = SDL_CreateTextureFromSurface(renderer, surface_23);

	SDL_Rect r_23;
	sdl_rect_init(r_23, 510, 375, surface_23);
	SDL_FreeSurface(surface_23);

	SDL_Surface *surface_24 = TTF_RenderText_Solid(font_type_small, MUTE_FOURTH_PART, purple_color);
	SDL_Texture *texture_24 = SDL_CreateTextureFromSurface(renderer, surface_24);

	SDL_Rect r_24;
	sdl_rect_init(r_24, 550, 375, surface_24);
	SDL_FreeSurface(surface_24);

	SDL_Surface *surface_25 = TTF_RenderText_Solid(font_type_small, MUTE_FIFTH_PART, white_color);
	SDL_Texture *texture_25 = SDL_CreateTextureFromSurface(renderer, surface_25);

	SDL_Rect r_25;
	sdl_rect_init(r_25, 600, 375, surface_25);
	SDL_FreeSurface(surface_25);

	SDL_Surface *surface_26 = TTF_RenderText_Solid(font_type_small, MUTE_SIXTH_PART, blue_color);
	SDL_Texture *texture_26 = SDL_CreateTextureFromSurface(renderer, surface_26);

	SDL_Rect r_26;
	sdl_rect_init(r_26, 680, 375, surface_26);
	SDL_FreeSurface(surface_26);

	/* How to play */
	SDL_Surface *surface_28 = TTF_RenderText_Solid(font_type_small, HOW_TO_PLAY_FIRST_PART, white_color);
	SDL_Texture *texture_28 = SDL_CreateTextureFromSurface(renderer, surface_28);

	SDL_Rect r_28;
	sdl_rect_init(r_28, 250, 340, surface_28);
	SDL_FreeSurface(surface_28);

	SDL_Surface *surface_29 = TTF_RenderText_Solid(font_type_small, HOW_TO_PLAY_SECOND_PART, green_color);
	SDL_Texture *texture_29 = SDL_CreateTextureFromSurface(renderer, surface_29);

	SDL_Rect r_29;
	sdl_rect_init(r_29, 710, 340, surface_29);
	SDL_FreeSurface(surface_29);

	Mix_PlayMusic(music, -1);

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

						SDL_Window *new_window;
						SDL_Renderer *new_renderer;

						sdl_initialize(&new_window, &new_renderer, CHIP8_HOW_TO_PLAY);

						SDL_Event new_event;

						/* Title */
						SDL_Surface *surface_30 = TTF_RenderText_Solid(font_type_large, HOW_TO_PLAY, purple_color);
						SDL_Texture *texture_30 = SDL_CreateTextureFromSurface(new_renderer, surface_30);

						SDL_Rect r_30;
						sdl_rect_init(r_30, 350, 0, surface_30);
						SDL_FreeSurface(surface_30);

						/* Tetris */
						SDL_Surface *surface_31 = TTF_RenderText_Solid(font_type_small, roms[0], red_color);
						SDL_Texture *texture_31 = SDL_CreateTextureFromSurface(new_renderer, surface_31);

						SDL_Rect r_31;
						sdl_rect_init(r_31, 100, 60, surface_31);
						SDL_FreeSurface(surface_31);

						SDL_Surface *surface_32 = TTF_RenderText_Solid(font_type_small, TETRIS, white_color);
						SDL_Texture *texture_32 = SDL_CreateTextureFromSurface(new_renderer, surface_32);

						SDL_Rect r_32;
						sdl_rect_init(r_32, 250, 60, surface_32);
						SDL_FreeSurface(surface_32);

						/* TicTac */
						SDL_Surface *surface_33 = TTF_RenderText_Solid(font_type_small, roms[1], blue_color);
						SDL_Texture *texture_33 = SDL_CreateTextureFromSurface(new_renderer, surface_33);

						SDL_Rect r_33;
						sdl_rect_init(r_33, 100, 85, surface_33);
						SDL_FreeSurface(surface_33);

						SDL_Surface *surface_34 = TTF_RenderText_Solid(font_type_small, TICTAC, white_color);
						SDL_Texture *texture_34 = SDL_CreateTextureFromSurface(new_renderer, surface_34);

						SDL_Rect r_34;
						sdl_rect_init(r_34, 250, 85, surface_34);
						SDL_FreeSurface(surface_34);

						/* Invaders */
						SDL_Surface *surface_35 = TTF_RenderText_Solid(font_type_small, roms[2], yellow_color);
						SDL_Texture *texture_35 = SDL_CreateTextureFromSurface(new_renderer, surface_35);

						SDL_Rect r_35;
						sdl_rect_init(r_35, 100, 110, surface_35);
						SDL_FreeSurface(surface_35);

						SDL_Surface *surface_36 = TTF_RenderText_Solid(font_type_small, INVADERS, white_color);
						SDL_Texture *texture_36 = SDL_CreateTextureFromSurface(new_renderer, surface_36);

						SDL_Rect r_36;
						sdl_rect_init(r_36, 250, 110, surface_36);
						SDL_FreeSurface(surface_36);

						/* Blinky */
						SDL_Surface *surface_37 = TTF_RenderText_Solid(font_type_small, roms[3], green_color);
						SDL_Texture *texture_37 = SDL_CreateTextureFromSurface(new_renderer, surface_37);

						SDL_Rect r_37;
						sdl_rect_init(r_37, 100, 135, surface_37);
						SDL_FreeSurface(surface_37);

						SDL_Surface *surface_38 = TTF_RenderText_Solid(font_type_small, BLINKY_FIRST, white_color);
						SDL_Texture *texture_38 = SDL_CreateTextureFromSurface(new_renderer, surface_38);

						SDL_Rect r_38;
						sdl_rect_init(r_38, 250, 135, surface_38);
						SDL_FreeSurface(surface_38);

						SDL_Surface *surface_39 = TTF_RenderText_Solid(font_type_small, BLINKY_SECOND, white_color);
						SDL_Texture *texture_39 = SDL_CreateTextureFromSurface(new_renderer, surface_39);

						SDL_Rect r_39;
						sdl_rect_init(r_39, 250, 160, surface_39);
						SDL_FreeSurface(surface_39);

						/* Brix */
						SDL_Surface *surface_40 = TTF_RenderText_Solid(font_type_small, roms[4], purple_color);
						SDL_Texture *texture_40 = SDL_CreateTextureFromSurface(new_renderer, surface_40);

						SDL_Rect r_40;
						sdl_rect_init(r_40, 100, 185, surface_40);
						SDL_FreeSurface(surface_40);

						SDL_Surface *surface_41 = TTF_RenderText_Solid(font_type_small, BRIX, white_color);
						SDL_Texture *texture_41 = SDL_CreateTextureFromSurface(new_renderer, surface_41);

						SDL_Rect r_41;
						sdl_rect_init(r_41, 250, 185, surface_41);
						SDL_FreeSurface(surface_41);

						/* Missile */
						SDL_Surface *surface_42 = TTF_RenderText_Solid(font_type_small, roms[5], red_color);
						SDL_Texture *texture_42 = SDL_CreateTextureFromSurface(new_renderer, surface_42);

						SDL_Rect r_42;
						sdl_rect_init(r_42, 100, 210, surface_42);
						SDL_FreeSurface(surface_42);

						SDL_Surface *surface_43 = TTF_RenderText_Solid(font_type_small, MISSILE, white_color);
						SDL_Texture *texture_43 = SDL_CreateTextureFromSurface(new_renderer, surface_43);

						SDL_Rect r_43;
						sdl_rect_init(r_43, 250, 210, surface_43);
						SDL_FreeSurface(surface_43);

						/* Pong */
						SDL_Surface *surface_44 = TTF_RenderText_Solid(font_type_small, roms[6], blue_color);
						SDL_Texture *texture_44 = SDL_CreateTextureFromSurface(new_renderer, surface_44);

						SDL_Rect r_44;
						sdl_rect_init(r_44, 100, 235, surface_44);
						SDL_FreeSurface(surface_44);

						SDL_Surface *surface_45 = TTF_RenderText_Solid(font_type_small, PONG_FIRST, white_color);
						SDL_Texture *texture_45 = SDL_CreateTextureFromSurface(new_renderer, surface_45);

						SDL_Rect r_45;
						sdl_rect_init(r_45, 250, 235, surface_45);
						SDL_FreeSurface(surface_45);

						SDL_Surface *surface_46 = TTF_RenderText_Solid(font_type_small, PONG_SECOND, white_color);
						SDL_Texture *texture_46 = SDL_CreateTextureFromSurface(new_renderer, surface_46);

						SDL_Rect r_46;
						sdl_rect_init(r_46, 250, 260, surface_46);
						SDL_FreeSurface(surface_46);

						/* Puzzle */
						SDL_Surface *surface_47 = TTF_RenderText_Solid(font_type_small, roms[7], yellow_color);
						SDL_Texture *texture_47 = SDL_CreateTextureFromSurface(new_renderer, surface_47);

						SDL_Rect r_47;
						sdl_rect_init(r_47, 100, 285, surface_47);
						SDL_FreeSurface(surface_47);

						SDL_Surface *surface_48 = TTF_RenderText_Solid(font_type_small, PUZZLE_FIRST, white_color);
						SDL_Texture *texture_48 = SDL_CreateTextureFromSurface(new_renderer, surface_48);

						SDL_Rect r_48;
						sdl_rect_init(r_48, 250, 285, surface_48);
						SDL_FreeSurface(surface_48);

						SDL_Surface *surface_49 = TTF_RenderText_Solid(font_type_small, PUZZLE_SECOND, white_color);
						SDL_Texture *texture_49 = SDL_CreateTextureFromSurface(new_renderer, surface_49);

						SDL_Rect r_49;
						sdl_rect_init(r_49, 250, 310, surface_49);
						SDL_FreeSurface(surface_49);

						/* UFO */
						SDL_Surface *surface_50 = TTF_RenderText_Solid(font_type_small, roms[8], green_color);
						SDL_Texture *texture_50 = SDL_CreateTextureFromSurface(new_renderer, surface_50);

						SDL_Rect r_50;
						sdl_rect_init(r_50, 100, 335, surface_50);
						SDL_FreeSurface(surface_50);

						SDL_Surface *surface_51 = TTF_RenderText_Solid(font_type_small, UFO, white_color);
						SDL_Texture *texture_51 = SDL_CreateTextureFromSurface(new_renderer, surface_51);

						SDL_Rect r_51;
						sdl_rect_init(r_51, 250, 335, surface_51);
						SDL_FreeSurface(surface_51);

						/* VBRIX */
						SDL_Surface *surface_52 = TTF_RenderText_Solid(font_type_small, roms[9], purple_color);
						SDL_Texture *texture_52 = SDL_CreateTextureFromSurface(new_renderer, surface_52);

						SDL_Rect r_52;
						sdl_rect_init(r_52, 100, 360, surface_52);
						SDL_FreeSurface(surface_52);

						SDL_Surface *surface_53 = TTF_RenderText_Solid(font_type_small, VBRIX, white_color);
						SDL_Texture *texture_53 = SDL_CreateTextureFromSurface(new_renderer, surface_53);

						SDL_Rect r_53;
						sdl_rect_init(r_53, 250, 360, surface_53);
						SDL_FreeSurface(surface_53);

						/* SPACERACER */
						SDL_Surface *surface_54 = TTF_RenderText_Solid(font_type_small, roms[10], red_color);
						SDL_Texture *texture_54 = SDL_CreateTextureFromSurface(new_renderer, surface_54);

						SDL_Rect r_54;
						sdl_rect_init(r_54, 100, 385, surface_54);
						SDL_FreeSurface(surface_54);

						SDL_Surface *surface_55 = TTF_RenderText_Solid(font_type_small, SPACERACER, white_color);
						SDL_Texture *texture_55 = SDL_CreateTextureFromSurface(new_renderer, surface_55);

						SDL_Rect r_55;
						sdl_rect_init(r_55, 250, 385, surface_55);
						SDL_FreeSurface(surface_55);

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
							SDL_RenderCopy(new_renderer, texture_31, nullptr, &r_31);
							SDL_RenderCopy(new_renderer, texture_32, nullptr, &r_32);
							SDL_RenderCopy(new_renderer, texture_33, nullptr, &r_33);
							SDL_RenderCopy(new_renderer, texture_34, nullptr, &r_34);
							SDL_RenderCopy(new_renderer, texture_35, nullptr, &r_35);
							SDL_RenderCopy(new_renderer, texture_36, nullptr, &r_36);
							SDL_RenderCopy(new_renderer, texture_37, nullptr, &r_37);
							SDL_RenderCopy(new_renderer, texture_38, nullptr, &r_38);
							SDL_RenderCopy(new_renderer, texture_39, nullptr, &r_39);
							SDL_RenderCopy(new_renderer, texture_40, nullptr, &r_40);
							SDL_RenderCopy(new_renderer, texture_41, nullptr, &r_41);
							SDL_RenderCopy(new_renderer, texture_42, nullptr, &r_42);
							SDL_RenderCopy(new_renderer, texture_43, nullptr, &r_43);
							SDL_RenderCopy(new_renderer, texture_44, nullptr, &r_44);
							SDL_RenderCopy(new_renderer, texture_45, nullptr, &r_45);
							SDL_RenderCopy(new_renderer, texture_46, nullptr, &r_46);
							SDL_RenderCopy(new_renderer, texture_47, nullptr, &r_47);
							SDL_RenderCopy(new_renderer, texture_48, nullptr, &r_48);
							SDL_RenderCopy(new_renderer, texture_49, nullptr, &r_49);
							SDL_RenderCopy(new_renderer, texture_50, nullptr, &r_50);
							SDL_RenderCopy(new_renderer, texture_51, nullptr, &r_51);
							SDL_RenderCopy(new_renderer, texture_52, nullptr, &r_52);
							SDL_RenderCopy(new_renderer, texture_53, nullptr, &r_53);
							SDL_RenderCopy(new_renderer, texture_54, nullptr, &r_54);
							SDL_RenderCopy(new_renderer, texture_55, nullptr, &r_55);
							SDL_RenderPresent(new_renderer);
						}

						SDL_DestroyTexture(texture_30);
						SDL_DestroyTexture(texture_31);
						SDL_DestroyTexture(texture_32);
						SDL_DestroyTexture(texture_33);
						SDL_DestroyTexture(texture_34);
						SDL_DestroyTexture(texture_35);
						SDL_DestroyTexture(texture_36);
						SDL_DestroyTexture(texture_37);
						SDL_DestroyTexture(texture_38);
						SDL_DestroyTexture(texture_39);
						SDL_DestroyTexture(texture_40);
						SDL_DestroyTexture(texture_41);
						SDL_DestroyTexture(texture_42);
						SDL_DestroyTexture(texture_43);
						SDL_DestroyTexture(texture_44);
						SDL_DestroyTexture(texture_45);
						SDL_DestroyTexture(texture_46);
						SDL_DestroyTexture(texture_47);
						SDL_DestroyTexture(texture_48);
						SDL_DestroyTexture(texture_49);
						SDL_DestroyTexture(texture_50);
						SDL_DestroyTexture(texture_51);
						SDL_DestroyTexture(texture_52);
						SDL_DestroyTexture(texture_53);
						SDL_DestroyTexture(texture_54);
						SDL_DestroyTexture(texture_55);

						sdl_restore(&new_window, &new_renderer);
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

						sdl_restore(&window, &renderer);

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

	Mix_FreeMusic(music);

	Mix_Quit();
	SDL_Quit();
	TTF_Quit();

	sdl_restore(&window, &renderer);
}
