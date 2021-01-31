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
			[this, index { PROGRAM_START }](const uint8_t& c)
					mutable
			{
				write_mem(c, index++);
			});
}

inline constexpr bool Chip8CPU::in_bounds(const uint16_t& index) noexcept
{
	return index >= 0 && index < MEMORY_SIZE;
}

void Chip8CPU::write_mem(const uint8_t& data, const uint16_t& index)
{
	if (!in_bounds(index))
	{
		throw std::runtime_error("Index out of bounds while performing write operation.");
	}
	memory[index] = data;
}

constexpr uint8_t Chip8CPU::read_mem(const uint16_t& index) const
{
	if (!in_bounds(index))
	{
		throw std::runtime_error("Index out of bounds while performing read operation.");
	}
	return memory[index];
}

constexpr void Chip8CPU::configure_delay(const uint16_t& delay) noexcept
{
	delay_timer = delay;
}

constexpr void Chip8CPU::configure_sound(const uint16_t& sound) noexcept
{
	delay_timer = sound;
}
