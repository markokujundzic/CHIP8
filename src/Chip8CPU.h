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
	static constexpr auto MEMORY_SIZE { 0x1000 };
	static constexpr auto PROGRAM_START { 0x200 };

	static constexpr auto WINDOW_WIDTH { 64 };
	static constexpr auto WINDOW_HEIGHT { 32 };

	static constexpr auto PIXEL_SCALE { 10 };

	void load_rom(const std::string& path);

	void write_mem(const uint8_t& byte, const uint8_t& index);

	uint8_t read_mem(const uint8_t& index);

private:
	std::array<uint8_t, MEMORY_SIZE> memory;
};

#endif
