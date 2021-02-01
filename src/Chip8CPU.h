#ifndef _CHIP8CPU_H_
#define _CHIP8CPU_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <algorithm>
#include <iostream>
#include <cstdint>
#include <fstream>
#include <array>
#include <string>

class Chip8CPU
{
public:
	/* Constants */
	static constexpr uint16_t MEMORY_SIZE { 0x1000 };
	static constexpr uint16_t PROGRAM_START { 0x200 };

	static constexpr uint8_t WINDOW_WIDTH { 64 };
	static constexpr uint8_t WINDOW_HEIGHT { 32 };

	static constexpr uint8_t REGISTER_NUMBER { 16 };
	static constexpr uint8_t NUMBER_OF_KEYS { 16 };
	static constexpr uint8_t STACK_SIZE { 32 };
	static constexpr uint8_t PIXEL_SCALE { 10 };
	static constexpr uint8_t FONT_SIZE { 80 };

	/* CHIP 8 font map */
	static constexpr std::array<uint8_t, FONT_SIZE> font_map =
			{
					0xF0, 0x90, 0x90, 0x90, 0xF0, /* 0 */
					0x20, 0x60, 0x20, 0x20, 0x70, /* 1 */
					0xF0, 0x10, 0xF0, 0x80, 0xF0, /* 2 */
					0xF0, 0x10, 0xF0, 0x10, 0xF0, /* 3 */
					0x90, 0x90, 0xF0, 0x10, 0x10, /* 4 */
					0xF0, 0x80, 0xF0, 0x10, 0xF0, /* 5 */
					0xF0, 0x80, 0xF0, 0x90, 0xF0, /* 6 */
					0xF0, 0x10, 0x20, 0x40, 0x40, /* 7 */
					0xF0, 0x90, 0xF0, 0x90, 0xF0, /* 8 */
					0xF0, 0x90, 0xF0, 0x10, 0xF0, /* 9 */
					0xF0, 0x90, 0xF0, 0x90, 0x90, /* A */
					0xE0, 0x90, 0xE0, 0x90, 0xE0, /* B */
					0xF0, 0x80, 0x80, 0x80, 0xF0, /* C */
					0xE0, 0x90, 0x90, 0x90, 0xE0, /* D */
					0xF0, 0x80, 0xF0, 0x80, 0xF0, /* E */
					0xF0, 0x80, 0xF0, 0x80, 0x80  /* F */
			};

	/* SDL Keyboard map */
	static constexpr std::array<char, NUMBER_OF_KEYS> keyboard_map =
			{
					SDLK_0,
					SDLK_1,
					SDLK_2,
					SDLK_3,
					SDLK_4,
					SDLK_5,
					SDLK_6,
					SDLK_7,
					SDLK_8,
					SDLK_9,
					SDLK_a,
					SDLK_b,
					SDLK_c,
					SDLK_d,
					SDLK_e,
					SDLK_f
			};

	/* Keyboard */
	static int get_keyboard_mapping_value(const char& key_hit);

	void key_press(const int& key);

	void key_release(const int& key);

	bool is_key_pressed(const int& key);

	/* Memory */
	void load_rom(const std::string& path);

	void write_mem(const uint8_t& byte, const uint16_t& index);

	constexpr uint8_t read_mem(const uint16_t& index) const;

	/* Timers */
	constexpr void configure_delay(const uint16_t& delay) noexcept;

	constexpr void configure_sound(const uint16_t& sound) noexcept;

	/* Initialization */
	void initialize() noexcept;

	/* Emulator loop */
	void emulate(const std::string& path);

	/* Stack */
	void push(const uint16_t& data);

	uint16_t pop();

private:
	/* Utility */
	static constexpr bool memory_in_bounds(const uint16_t& index) noexcept;

	static constexpr bool push_in_bounds(const uint16_t& index) noexcept;

	static constexpr bool pop_in_bounds(const uint16_t& index) noexcept;

	static constexpr bool keyboard_in_bounds(const int& index) noexcept;

	/* RAM memory */
	std::array<uint8_t, MEMORY_SIZE + STACK_SIZE> memory;

	/* Register bank */
	std::array<uint8_t, REGISTER_NUMBER> v;

	/* Keyboard */
	std::array<bool, NUMBER_OF_KEYS> keyboard;

	/* PC */
	uint16_t pc;
	/* SP */
	uint16_t sp;
	/* Instruction register */
	uint16_t i;

	/* Timers */
	uint8_t delay_timer;
	uint8_t sound_timer;
};

#endif
