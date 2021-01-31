#ifndef _CHIP8CPU_H_
#define _CHIP8CPU_H_

#include <algorithm>
#include <iostream>
#include <cstdint>
#include <fstream>
#include <array>
#include <string>

class Chip8CPU
{
public:
	static constexpr uint16_t MEMORY_SIZE { 0x1000 };
	static constexpr uint16_t PROGRAM_START { 0x200 };

	static constexpr uint8_t WINDOW_WIDTH { 64 };
	static constexpr uint8_t WINDOW_HEIGHT { 32 };

	static constexpr uint8_t REGISTER_NUMBER { 16 };
	static constexpr uint8_t STACK_SIZE { 32 };
	static constexpr uint8_t PIXEL_SCALE { 10 };

	void load_rom(const std::string& path);

	void write_mem(const uint8_t& byte, const uint16_t& index);

	constexpr void configure_delay(const uint16_t& delay) noexcept;

	constexpr void configure_sound(const uint16_t& sound) noexcept;

	constexpr uint8_t read_mem(const uint16_t& index) const;

	void initialize();

	void push(const uint16_t& data);

	uint16_t pop();

private:
	static constexpr bool memory_in_bounds(const uint16_t& index) noexcept;

	static constexpr bool push_in_bounds(const uint16_t& index) noexcept;

	static constexpr bool pop_in_bounds(const uint16_t& index) noexcept;

	std::array<uint8_t, MEMORY_SIZE + STACK_SIZE> memory;
	std::array<uint8_t, REGISTER_NUMBER> v;

	uint16_t i;
	uint16_t pc;
	uint16_t sp;

	uint8_t delay_timer;
	uint8_t sound_timer;
};

#endif
