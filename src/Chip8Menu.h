#ifndef _CHIP8MENU_H_
#define _CHIP8MENU_H_

#include "Chip8CPU.h"

class CHIP8Menu {
public:
	void render_menu();

private:
	static constexpr uint8_t NUMBER_OF_ROMS { 11 };

	/* Names */
	static constexpr const char *WINDOW_TITLE { "CHIP8 Menu" };
	static constexpr const char *FONT { "../fonts/Arcade Classic.ttf" };

	static constexpr const char *NAME_FIRST_PART { "Marko    Kujundzic    " };
	static constexpr const char *NAME_SECOND_PART { "418    2016" };

	static constexpr const char *TITLE_FIRST_PART { "CHIP  8    " };
	static constexpr const char *TITLE_SECOND_PART { "EMULATOR" };

	static constexpr const char *COLOR_CHANGE_FIRST_PART { "TO    CHANGE    THE    EMULATOR    COLOR    PRESS    " };
	static constexpr const char *COLOR_CHANGE_SECOND_PART { "R    " };
	static constexpr const char *COLOR_CHANGE_THIRD_PART { "G    " };
	static constexpr const char *COLOR_CHANGE_FOURTH_PART { "Y    " };
	static constexpr const char *COLOR_CHANGE_FIFTH_PART { "B    " };
	static constexpr const char *COLOR_CHANGE_SIXTH_PART { "W    " };

	static constexpr const char *ROM_CHANGE_FIRST_PART { "TO    CHANGE    THE    EMULATOR    ROM    PRESS    " };
	static constexpr const char *ROM_CHANGE_SECOND_PART { "LEFT    ARROW    " };
	static constexpr const char *ROM_CHANGE_THIRD_PART { "OR    " };
	static constexpr const char *ROM_CHANGE_FOURTH_PART { "RIGHT ARROW" };

	static constexpr const char *PROCEED_FIRST_PART { "PRESS    " };
	static constexpr const char *PROCEED_SECOND_PART { "ENTER    " };
	static constexpr const char *PROCEED_THIRD_PART { "TO    BEGIN" };

	static constexpr const char *SELECTED_ROM { "SELECTED    ROM    FILE" };
	static constexpr const char *SELECTED_COLOR { "SELECTED    COLOR" };

	static constexpr const char *MUTE_FIRST_PART { "TO    TURN    MUSIC    " };
	static constexpr const char *MUTE_SECOND_PART { "ON    " };
	static constexpr const char *MUTE_THIRD_PART { "OR    " };
	static constexpr const char *MUTE_FOURTH_PART { "OFF    " };
	static constexpr const char *MUTE_FIFTH_PART { "PRESS    " };
	static constexpr const char *MUTE_SIXTH_PART { "S" };

	static constexpr const char *HOW_TO_PLAY_FIRST_PART {
			"TO    SEE    HOW    TO    PLAY    EACH    ROM    PRESS    " };
	static constexpr const char *HOW_TO_PLAY_SECOND_PART { "I" };

	static constexpr const char *HOW_TO_PLAY { "HOW    TO    PLAY" };

	static constexpr int WIDTH = Chip8CPU::DISPLAY_WIDTH * Chip8CPU::DISPLAY_PIXEL_SCALE;
	static constexpr int HEIGHT = Chip8CPU::DISPLAY_HEIGHT * Chip8CPU::DISPLAY_PIXEL_SCALE;

	static constexpr uint8_t NUMBER_OF_COLORS { 5 };

	static constexpr uint8_t WHITE { 0 };
	static constexpr uint8_t RED { 1 };
	static constexpr uint8_t GREEN { 2 };
	static constexpr uint8_t YELLOW { 3 };
	static constexpr uint8_t BLUE { 4 };

	static constexpr const char *CHIP8_HOW_TO_PLAY { "Chip 8 How to play" };

	static constexpr const char *TETRIS = "PRESS    5    AND    6    TO    MOVE    PRESS    4    TO    ROTATE";
	static constexpr const char *TICTAC = "PRESS    1    TO    9    TO    FILL    THE    BOXES";
	static constexpr const char *INVADERS = "PRESS    4    AND    6    TO    MOVE    PRESS    5    TO    SHOOT";
	static constexpr const char *BLINKY_FIRST = "PRESS    3    AND    6    TO    MOVE    UP    AND    DOWN";
	static constexpr const char *BLINKY_SECOND = "PRESS    7    AND    8    TO    MOVE    LEFT    AND    RIGHT";
	static constexpr const char *BRIX = "PRESS    4    AND    6    TO    MOVE";
	static constexpr const char *MISSILE = "PRESS    8    TO    SHOOT";
	static constexpr const char *PONG_FIRST = "PRESS    1    AND    4    TO    MOVE    LEFT    PLAYER    LEFT    AND    RIGHT";
	static constexpr const char *PONG_SECOND = "PRESS    C    AND    D    TO    MOVE    RIGHT    PLAYER    LEFT    AND    RIGHT";
	static constexpr const char *PUZZLE_FIRST = "PRESS    2    AND    8    TO    MOVE    UP    AND    DOWN";
	static constexpr const char *PUZZLE_SECOND = "PRESS    6    AND    4    TO    MOVE    LEFT    AND    RIGHT";
	static constexpr const char *UFO = "PRESS    4    5    6    TO    SHOOT    LEFT    CENTER    AND    RIGHT";
	static constexpr const char *VBRIX = "PRESS    1    AND    4    TO    MOVE    UP    AND    DOWN    PRESS    7    TO    START";
	static constexpr const char *SPACERACER = "PRESS    4    AND    D    TO    FLY    WITH    LEFT    AND    RIGHT    PLAYERS";

	/* ROMS */
	static constexpr std::array<const char *, NUMBER_OF_ROMS> roms
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
	static constexpr std::array<const char *, NUMBER_OF_COLORS> colors
			{
					"WHITE",
					"RED",
					"GREEN",
					"YELLOW",
					"BLUE"
			};

	/* SDL */
	static void sdl_initialize(SDL_Window **window, SDL_Renderer **renderer, const char *title_name);

	static void sdl_restore(SDL_Window **window, SDL_Renderer **renderer);

	static void sdl_rect_init(SDL_Rect& rect, int x, int y, const SDL_Surface *surface);

	/* Initialization */
	void initialize_music();

	/* Music */
	Mix_Music *music { nullptr };
};

#endif
