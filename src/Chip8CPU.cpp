#include "Chip8CPU.h"

void Chip8CPU::load_rom(const std::string& path)
{
	initialize();

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

inline constexpr bool Chip8CPU::memory_in_bounds(const uint16_t& index) noexcept
{
	return index >= 0 && index <= MEMORY_SIZE - 1;
}

inline constexpr bool Chip8CPU::push_in_bounds(const uint16_t& index) noexcept
{
	return index >= MEMORY_SIZE && index <= MEMORY_SIZE + STACK_SIZE - 1 &&
	       index + 1 >= MEMORY_SIZE && index + 1 <= MEMORY_SIZE + STACK_SIZE - 1;
}

inline constexpr bool Chip8CPU::pop_in_bounds(const uint16_t& index) noexcept
{
	return index >= MEMORY_SIZE && index <= MEMORY_SIZE + STACK_SIZE - 1 &&
	       index - 1 >= MEMORY_SIZE && index - 1 <= MEMORY_SIZE + STACK_SIZE - 1;
}

void Chip8CPU::write_mem(const uint8_t& data, const uint16_t& index)
{
	if (!memory_in_bounds(index))
	{
		throw std::runtime_error("Index out of bounds while performing write operation.");
	}
	memory[index] = data;
}

constexpr uint8_t Chip8CPU::read_mem(const uint16_t& index) const
{
	if (!memory_in_bounds(index))
	{
		throw std::runtime_error("Index out of bounds while performing read operation.");
	}
	return memory[index];
}

inline constexpr void Chip8CPU::configure_delay(const uint16_t& delay) noexcept
{
	delay_timer = delay;
}

inline constexpr void Chip8CPU::configure_sound(const uint16_t& sound) noexcept
{
	delay_timer = sound;
}

void Chip8CPU::push(const uint16_t& data)
{
	if (!push_in_bounds(sp))
	{
		throw std::runtime_error("Stack overflow while performing push operation.");
	}
	memory[sp++] = static_cast<uint8_t>(data & 0x00FF);
	memory[sp++] = static_cast<uint8_t>(data >> 8 & 0x00FF);
}

uint16_t Chip8CPU::pop()
{
	if (!pop_in_bounds(sp))
	{
		throw std::runtime_error("Stack underflow while performing pop operation.");
	}
	uint8_t h = memory[--sp];
	uint8_t l = memory[--sp];
	return h << 8 | l;
}

void Chip8CPU::initialize()
{
	sp = MEMORY_SIZE;
	pc = PROGRAM_START;
	i = 0;
	delay_timer = 60;
	sound_timer = 60;
	for (auto& reg : v)
	{
		reg = 0;
	}
	for (auto& mem : memory)
	{
		mem = 0;
	}
}
