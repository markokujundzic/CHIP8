#include "Chip8CPU.h"

constexpr std::array<char, Chip8CPU::NUMBER_OF_KEYS> Chip8CPU::keyboard_map;
constexpr std::array<uint8_t, Chip8CPU::FONT_SIZE> Chip8CPU::font_map;

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

constexpr inline void Chip8CPU::configure_delay(const uint16_t& delay) noexcept
{
	delay_timer = delay;
}

constexpr inline void Chip8CPU::configure_sound(const uint16_t& sound) noexcept
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

inline void Chip8CPU::load_font() noexcept
{
	for (uint32_t i = FONT_START; i < font_map.size(); i++)
	{
		memory[i] = font_map[i];
	}
}

void Chip8CPU::initialize_hardware() noexcept
{
	sp = MEMORY_SIZE;
	pc = PROGRAM_START;
	delay_timer = 60;
	sound_timer = 60;
	i = 0;

	for (auto& reg : v)
	{
		reg = 0;
	}

	for (auto& mem : memory)
	{
		mem = 0;
	}

	for (auto x = 0; x < DISPLAY_WIDTH; x++)
	{
		for (auto y = 0; y < DISPLAY_HEIGHT; y++)
		{
			display[y][x] = false;
		}
	}
}

void Chip8CPU::initialize() noexcept
{
	initialize_hardware();
	load_font();
}

void Chip8CPU::emulate(const std::string& path)
{
	initialize();
	load_rom(path);
}

int Chip8CPU::get_keyboard_mapping_value(const char& key_hit)
{
	int return_value = KEY_NOT_FOUND;

	for (int i = 0; i < NUMBER_OF_KEYS; i++)
	{
		if (Chip8CPU::keyboard_map[i] == key_hit)
		{
			return_value = i;
			break;
		}
	}

	return return_value;
}

constexpr bool Chip8CPU::keyboard_in_bounds(const int& index) noexcept
{
	return index >= 0 && index <= NUMBER_OF_KEYS - 1;
}

void Chip8CPU::key_press(const int& key)
{
	if (!keyboard_in_bounds(key))
	{
		throw std::runtime_error("Index out of bounds while reading keyboard array element.");
	}
	keyboard[key] = true;
}

void Chip8CPU::key_release(const int& key)
{
	if (!keyboard_in_bounds(key))
	{
		throw std::runtime_error("Index out of bounds while reading keyboard array element.");
	}
	keyboard[key] = false;
}

bool Chip8CPU::is_key_pressed(const int& key)
{
	if (!keyboard_in_bounds(key))
	{
		throw std::runtime_error("Index out of bounds while reading keyboard array element.");
	}
	return keyboard[key];
}

constexpr bool Chip8CPU::pixel_in_bounds(const uint8_t& x, const uint8_t& y) noexcept
{
	return x >= 0 && x <= DISPLAY_WIDTH - 1 && y >= 0 && y <= DISPLAY_HEIGHT - 1;
}

void Chip8CPU::set_pixel(const uint8_t& x, const uint8_t& y)
{
	if (!pixel_in_bounds(x, y))
	{
		throw std::runtime_error("Pixel out of bounds while reading display screen pixels.");
	}
	display[y][x] = true;
}

bool Chip8CPU::is_pixel_set(const uint8_t& x, const uint8_t& y)
{
	if (!pixel_in_bounds(x, y))
	{
		throw std::runtime_error("Pixel out of bounds while reading display screen pixels.");
	}
	return display[y][x];
}
