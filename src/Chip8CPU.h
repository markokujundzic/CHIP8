#ifndef _CHIP8CPU_H_
#define _CHIP8CPU_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <Windows.h>

#include <algorithm>
#include <array>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <random>
#include <string>

class Chip8CPU
{
public:
	/* Memory */
	static constexpr uint16_t PROGRAM_START { 0x200 };
	static constexpr uint16_t MEMORY_SIZE { 0x1000 };
	static constexpr uint8_t REGISTER_NUMBER { 16 };
	static constexpr uint8_t STACK_SIZE { 32 };

	/* Display screen */
	static constexpr uint8_t DISPLAY_PIXEL_SCALE { 10 };
	static constexpr uint8_t DEFAULT_SPRITE_SIZE { 5 };
	static constexpr uint8_t DISPLAY_WIDTH { 64 };

	static constexpr uint8_t DISPLAY_HEIGHT { 32 };
	static constexpr uint8_t BITS_IN_BYTE { 8 };
	static constexpr uint8_t NIBBLE { 4 };

	static constexpr uint8_t MSB_SET { 0x80 };
	static constexpr uint8_t LSB_SET { 0x1 };

	static constexpr uint8_t HUNDREDS { 100 };
	static constexpr uint8_t TENS { 10 };

	/* Keyboard */
	static constexpr uint8_t NUMBER_OF_KEYS { 16 };
	static constexpr int KEY_NOT_FOUND { -1 };

	/* Font */
	static constexpr uint8_t FONT_SIZE { 80 };
	static constexpr uint8_t FONT_START { 0 };

	/* Window name */
	static constexpr const char *WINDOW_NAME { "CHIP8" };

	/* CHIP 8 font map */
	static constexpr std::array<uint8_t, FONT_SIZE> font_map =
			{
					/* 0 */
					0xF0, 0x90, 0x90, 0x90, 0xF0,
					/* 1 */
					0x20, 0x60, 0x20, 0x20, 0x70,
					/* 2 */
					0xF0, 0x10, 0xF0, 0x80, 0xF0,
					/* 3 */
					0xF0, 0x10, 0xF0, 0x10, 0xF0,
					/* 4 */
					0x90, 0x90, 0xF0, 0x10, 0x10,
					/* 5 */
					0xF0, 0x80, 0xF0, 0x10, 0xF0,
					/* 6 */
					0xF0, 0x80, 0xF0, 0x90, 0xF0,
					/* 7 */
					0xF0, 0x10, 0x20, 0x40, 0x40,
					/* 8 */
					0xF0, 0x90, 0xF0, 0x90, 0xF0,
					/* 9 */
					0xF0, 0x90, 0xF0, 0x10, 0xF0,
					/* A */
					0xF0, 0x90, 0xF0, 0x90, 0x90,
					/* B */
					0xE0, 0x90, 0xE0, 0x90, 0xE0,
					/* C */
					0xF0, 0x80, 0x80, 0x80, 0xF0,
					/* D */
					0xE0, 0x90, 0x90, 0x90, 0xE0,
					/* E */
					0xF0, 0x80, 0xF0, 0x80, 0xF0,
					/* F */
					0xF0, 0x80, 0xF0, 0x80, 0x80
			};

	/* SDL Keyboard map */
	static constexpr std::array<char, NUMBER_OF_KEYS> keyboard_map =
			{
					/* Key 0 pressed */
					SDLK_0,
					/* Key 1 pressed */
					SDLK_1,
					/* Key 2 pressed */
					SDLK_2,
					/* Key 3 pressed */
					SDLK_3,
					/* Key 4 pressed */
					SDLK_4,
					/* Key 5 pressed */
					SDLK_5,
					/* Key 6 pressed */
					SDLK_6,
					/* Key 7 pressed */
					SDLK_7,
					/* Key 8 pressed */
					SDLK_8,
					/* Key 9 pressed */
					SDLK_9,
					/* Key A pressed */
					SDLK_a,
					/* Key B pressed */
					SDLK_b,
					/* Key C pressed */
					SDLK_c,
					/* Key D pressed */
					SDLK_d,
					/* Key E pressed */
					SDLK_e,
					/* Key F pressed */
					SDLK_f
			};

	/* Timers */
	constexpr void configure_delay(const uint16_t& delay) noexcept;

	constexpr void configure_sound(const uint16_t& sound) noexcept;

	/* Emulator loop */
	void emulate(const std::string& path);

private:
	/* Timers */
	void timer_tick() noexcept;

	/* Keyboard */
	static int get_keyboard_mapping_value(const char& key_hit) noexcept;

	void key_press(const int& key);

	void key_release(const int& key);

	bool is_key_pressed(const int& key) const;

	/* Emulator loop */
	constexpr uint16_t decode() const noexcept;

	void execute(const uint16_t& opcode);

	constexpr void fetch() noexcept;

	static constexpr uint16_t get_destination_address(const uint16_t& opcode) noexcept;

	static constexpr uint8_t get_first_byte(const uint16_t& opcode) noexcept;

	static constexpr uint8_t get_second_byte(const uint16_t& opcode) noexcept;

	static constexpr uint8_t get_first_nibble(const uint16_t& opcode) noexcept;

	static constexpr uint8_t get_second_nibble(const uint16_t& opcode) noexcept;

	static constexpr uint8_t get_third_nibble(const uint16_t& opcode) noexcept;

	static constexpr uint8_t get_fourth_nibble(const uint16_t& opcode) noexcept;

	void run();

	/* Memory */
	void load_rom(const std::string& path);

	void write_mem(const uint8_t& byte, const uint16_t& index);

	constexpr uint8_t read_mem(const uint16_t& index) const;

	/* Initialization */
	void initialize() noexcept;

	void initialize_hardware() noexcept;

	/* Stack */
	void push(const uint16_t& data);

	uint16_t pop();

	/* Font */
	void load_font() noexcept;

	/* Display screen */
	using pixel_matrix = std::array<std::array<bool, DISPLAY_WIDTH>, DISPLAY_HEIGHT>;

	void set_pixel(const uint8_t& x, const uint8_t& y);

	bool is_pixel_set(const uint8_t& x, const uint8_t& y) const;

	bool draw_sprite(const uint8_t& x, const uint8_t& y, const uint8_t& count, const uint8_t& index) noexcept;

	void clear_display_screen() noexcept;

	void invert_pixel(const uint8_t& x, const uint8_t& y) noexcept;

	/* SDL */
	static void sdl_initialize(SDL_Window **window, SDL_Renderer **renderer);

	static void sdl_restore(SDL_Window **window);

	static int sdl_wait_for_key_press() noexcept;

	void sdl_render(SDL_Renderer *renderer);

	void sdl_poll_events();

	/* Bounds checking */
	static constexpr bool memory_in_bounds(const uint16_t& index) noexcept;

	static constexpr bool push_in_bounds(const uint16_t& index) noexcept;

	static constexpr bool pop_in_bounds(const uint16_t& index) noexcept;

	static constexpr bool keyboard_in_bounds(const int& index) noexcept;

	static constexpr bool pixel_in_bounds(const uint8_t& x, const uint8_t& y) noexcept;

	/* Comparison */
	static constexpr bool equal(const uint8_t& x, const uint8_t& y) noexcept;

	/* RAM memory */
	std::array<uint8_t, MEMORY_SIZE + STACK_SIZE> memory;

	/* Register bank */
	std::array<uint8_t, REGISTER_NUMBER> V;

	/* Keyboard */
	std::array<bool, NUMBER_OF_KEYS> keyboard;

	/* Display screen*/
	pixel_matrix display;

	/* PC */
	uint16_t PC;

	/* SP */
	uint16_t SP;

	/* Instruction register */
	uint16_t I;

	/* Timers */
	uint8_t DT;

	uint8_t ST;

	/* Emulator state */
	bool running;
};

#endif