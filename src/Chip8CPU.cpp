#include "Chip8CPU.h"

void Chip8CPU::load_rom(const std::string& path)
{
	std::ifstream file(path, std::ios::binary | std::ios::in);
	if (!file.is_open())
	{
		throw std::runtime_error("Cannot open ROM file for reading.");
	}

	std::for_each(
			std::istreambuf_iterator<char>(file),
			std::istreambuf_iterator<char>(),
			[this, index { PROGRAM_START }](const char& c)
					mutable
			{
				if (index > MEMORY_SIZE)
				{
					throw std::runtime_error("ROM size exceeds available memory.");
				}
				memory[index++] = static_cast<uint8_t>(c);
			});
}
