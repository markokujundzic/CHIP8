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

void Chip8CPU::write_mem(const uint8_t& byte, const uint8_t& index)
{
	if (index < 0 || index > MEMORY_SIZE - 1)
	{
		throw std::runtime_error("Index out of bounds while performing write operation.");
	}
	memory[index] = byte;
}

uint8_t Chip8CPU::read_mem(const uint8_t& index)
{
	if (index < 0 || index > MEMORY_SIZE - 1)
	{
		throw std::runtime_error("Index out of bounds while performing read operation.");
	}
	return memory[index];
}
