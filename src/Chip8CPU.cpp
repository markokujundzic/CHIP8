#include "Chip8CPU.h"

constexpr std::array<char, Chip8CPU::NUMBER_OF_KEYS> Chip8CPU::keyboard_map;

constexpr std::array<uint8_t, Chip8CPU::FONT_SIZE> Chip8CPU::font_map;

inline constexpr bool Chip8CPU::memory_in_bounds(const uint16_t& index) noexcept
{
	return index >= 0 && index <= MEMORY_SIZE - 1;
}

inline constexpr bool Chip8CPU::push_in_bounds(const uint16_t& index) noexcept
{
	return index <= STACK_SIZE - 1;
}

inline constexpr bool Chip8CPU::pop_in_bounds(const uint16_t& index) noexcept
{
	return index <= STACK_SIZE - 1;
}

constexpr bool Chip8CPU::keyboard_in_bounds(const int& index) noexcept
{
	return index >= 0 && index <= NUMBER_OF_KEYS - 1;
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

constexpr inline void Chip8CPU::configure_delay(const uint16_t& delay) noexcept
{
	DT = delay;
}

constexpr inline void Chip8CPU::configure_sound(const uint16_t& sound) noexcept
{
	ST = sound;
}

void Chip8CPU::push(const uint16_t& data)
{
	if (!push_in_bounds(++SP))
	{
		throw std::runtime_error("Stack overflow while performing push operation.");
	}
	stack[SP] = data;
}

uint16_t Chip8CPU::pop()
{
	if (!pop_in_bounds(SP))
	{
		throw std::runtime_error("Stack underflow while performing pop operation.");
	}
	return stack[SP--];
}

inline void Chip8CPU::load_font() noexcept
{
	for (uint32_t i = FONT_START; i < font_map.size(); i++)
	{
		memory[i] = font_map[i];
	}
}

inline void Chip8CPU::clear_display_screen() noexcept
{
	for (auto x = 0; x < DISPLAY_WIDTH; x++)
	{
		for (auto y = 0; y < DISPLAY_HEIGHT; y++)
		{
			display[y][x] = false;
		}
	}
}

void Chip8CPU::initialize_hardware() noexcept
{
	running = true;
	PC = PROGRAM_START;
	SP = 0;
	DT = 0;
	ST = 0;
	I = 0;

	for (auto& reg : V)
	{
		reg = 0;
	}

	for (auto& mem : memory)
	{
		mem = 0;
	}

	clear_display_screen();
}

void Chip8CPU::initialize() noexcept
{
	initialize_hardware();
	load_font();
}

void Chip8CPU::emulate(const std::string& path, const SDL_Color& color)
{
	initialize();
	load_rom(path);
	run(color);
}

int Chip8CPU::get_keyboard_mapping_value(const char& key_hit) noexcept
{
	int return_value = KEY_NOT_FOUND;

	for (int i = 0; i < NUMBER_OF_KEYS; i++)
	{
		if (keyboard_map[i] == key_hit)
		{
			return_value = i;
			break;
		}
	}

	return return_value;
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

bool Chip8CPU::is_key_pressed(const int& key) const
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

bool Chip8CPU::is_pixel_set(const uint8_t& x, const uint8_t& y) const
{
	if (!pixel_in_bounds(x, y))
	{
		throw std::runtime_error("Pixel out of bounds while reading display screen pixels.");
	}
	return display[y][x];
}

void Chip8CPU::timer_tick() noexcept
{
	if (DT > 0)
	{
		Sleep(SLEEP_DURATION);
		DT--;
	}
	if (ST > 0)
	{
		Beep(BEEP_FREQUENCY, BEEP_DURATION * ST);
		ST = 0;
	}
}

inline void Chip8CPU::invert_pixel(const uint8_t& x, const uint8_t& y) noexcept
{
	display[y % DISPLAY_HEIGHT][x % DISPLAY_WIDTH] ^= true;
}

bool Chip8CPU::draw_sprite(const uint8_t& x, const uint8_t& y, const uint8_t& count, const uint8_t& index) noexcept
{
	auto collision { false };

	const auto *sprite = static_cast<const uint8_t *>(&index);

	for (auto y_offset = 0; y_offset < count; y_offset++)
	{
		for (auto x_offset = 0; x_offset < BITS_IN_BYTE; x_offset++)
		{
			if (sprite[y_offset] & (MSB_SET >> x_offset))
			{
				if (display[(y + y_offset) % DISPLAY_HEIGHT][(x + x_offset) % DISPLAY_WIDTH])
				{
					collision = true;
				}
				invert_pixel(x + x_offset, y + y_offset);
			}
		}
	}

	return collision;
}

inline constexpr uint16_t Chip8CPU::decode() const noexcept
{
	return read_mem(PC + 0) << BITS_IN_BYTE | read_mem(PC + 1);
}

void Chip8CPU::sdl_initialize(SDL_Window **window, SDL_Renderer **renderer)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	*window = SDL_CreateWindow(
			WINDOW_NAME,
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			DISPLAY_WIDTH * DISPLAY_PIXEL_SCALE,
			DISPLAY_HEIGHT * DISPLAY_PIXEL_SCALE,
			SDL_WINDOW_SHOWN);
	*renderer = SDL_CreateRenderer(*window, -1, SDL_TEXTUREACCESS_TARGET);
}

inline void Chip8CPU::sdl_restore(SDL_Window **window)
{
	SDL_DestroyWindow(*window);
}

void Chip8CPU::sdl_render(SDL_Renderer *renderer, const SDL_Color& color)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 0);

	for (auto x = 0; x < Chip8CPU::DISPLAY_WIDTH; x++)
	{
		for (auto y = 0; y < Chip8CPU::DISPLAY_HEIGHT; y++)
		{
			if (is_pixel_set(x, y))
			{
				SDL_Rect sdl_rect;
				sdl_rect.x = x * DISPLAY_PIXEL_SCALE;
				sdl_rect.y = y * DISPLAY_PIXEL_SCALE;
				sdl_rect.w = DISPLAY_PIXEL_SCALE;
				sdl_rect.h = DISPLAY_PIXEL_SCALE;
				SDL_RenderFillRect(renderer, &sdl_rect);
			}
		}
	}
	SDL_RenderPresent(renderer);
}

void Chip8CPU::sdl_poll_events(bool& pause)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				running = false;
				break;
			case SDL_KEYUP:
			{
				auto key = get_keyboard_mapping_value(event.key.keysym.sym);

				if (key != KEY_NOT_FOUND)
				{
					key_release(key);
				}
			}
				break;
			case SDL_KEYDOWN:
			{
				auto key = get_keyboard_mapping_value(event.key.keysym.sym);

				if (key != KEY_NOT_FOUND)
				{
					key_press(key);
				}

				auto& scancode = event.key.keysym.scancode;

				if (scancode == SDL_SCANCODE_SPACE)
				{
					pause = !pause;
				}
				else if (scancode == SDL_SCANCODE_ESCAPE)
				{
					running = false;
				}
			}
				break;
		}
	}
}

int Chip8CPU::sdl_wait_for_key_press() noexcept
{
	SDL_Event event;

	while (SDL_WaitEvent(&event))
	{
		if (event.type == SDL_KEYDOWN)
		{
			auto key = get_keyboard_mapping_value(event.key.keysym.sym);

			if (key != KEY_NOT_FOUND)
			{
				return key;
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			{
				running = false;
				break;
			}
		}
		else if (event.type == SDL_QUIT)
		{
			running = false;
			break;
		}
	}

	return KEY_NOT_FOUND;
}

inline constexpr void Chip8CPU::fetch() noexcept
{
	PC += 2;
}

inline constexpr uint16_t Chip8CPU::get_destination_address(const uint16_t& opcode) noexcept
{
	return opcode & 0xFFF;
}

inline constexpr bool Chip8CPU::equal(const uint8_t& x, const uint8_t& y) noexcept
{
	return x == y;
}

inline constexpr uint8_t Chip8CPU::get_first_byte(const uint16_t& opcode) noexcept
{
	return opcode & 0xFF;
}

inline constexpr uint8_t Chip8CPU::get_second_byte(const uint16_t& opcode) noexcept
{
	return (opcode >> BITS_IN_BYTE) & 0xFF;
}

inline constexpr uint8_t Chip8CPU::get_first_nibble(const uint16_t& opcode) noexcept
{
	return opcode & 0xF;
}

inline constexpr uint8_t Chip8CPU::get_second_nibble(const uint16_t& opcode) noexcept
{
	return (opcode >> NIBBLE) & 0xF;
}

inline constexpr uint8_t Chip8CPU::get_third_nibble(const uint16_t& opcode) noexcept
{
	return (opcode >> BITS_IN_BYTE) & 0xF;
}

inline constexpr uint8_t Chip8CPU::get_fourth_nibble(const uint16_t& opcode) noexcept
{
	return (opcode >> (BITS_IN_BYTE + NIBBLE)) & 0xF;
}

void Chip8CPU::execute(const uint16_t& opcode)
{
	switch (opcode & 0xF000)
	{
		case 0x0000:
			switch (opcode & 0x00FF)
			{
				/* 0x00E0 - CLS -> Clear the display */
				case 0x00E0:
					clear_display_screen();
					break;
				/* 0x00EE - RET -> Return from a subroutine */
				case 0x00EE:
					PC = pop();
					break;
				/* Unrecognized opcode */
				default:
					throw std::runtime_error("Illegal instruction encountered, opcode: 0x" + std::to_string(opcode));
			}
			break;
		/* 0x1nnn - JP addr -> Jump to location nnn */
		case 0x1000:
			PC = get_destination_address(opcode);
			break;
		/* 0x2nnn - CALL addr -> Call subroutine at nnn */
		case 0x2000:
			push(PC);
			PC = get_destination_address(opcode);
			break;
		/* 0x3xkk - SE Vx, byte -> Skip next instruction if Vx == kk */
		case 0x3000:
		{
			auto x = get_third_nibble(opcode);
			auto kk = get_first_byte(opcode);

			if (equal(V[x], kk))
			{
				fetch();
			}
		}
			break;
		/* 0x4xkk - SNE Vx, byte -> Skip next instruction if Vx != kk */
		case 0x4000:
		{
			auto x = get_third_nibble(opcode);
			auto kk = get_first_byte(opcode);

			if (!equal(V[x], kk))
			{
				fetch();
			}
		}
			break;
		/* 0x5xy0 - SE Vx, Vy -> Skip next instruction if Vx == Vy */
		case 0x5000:
		{
			auto x = get_third_nibble(opcode);
			auto y = get_second_nibble(opcode);

			if (equal(V[x], V[y]))
			{
				fetch();
			}
		}
			break;
		/* 0x6xkk - LD Vx, byte -> Puts the value kk into register Vx */
		case 0x6000:
		{
			auto x = get_third_nibble(opcode);
			auto kk = get_first_byte(opcode);

			V[x] = kk;
		}
			break;
		/* 0x7xkk - ADD Vx, byte -> Adds the value kk to the value of register Vx, then stores the result in Vx */
		case 0x7000:
		{
			auto x = get_third_nibble(opcode);
			auto kk = get_first_byte(opcode);

			V[x] += kk;
		}
			break;
		case 0x8000:
			switch (opcode & 0xF)
			{
				/* 0x8xy0 - LD Vx, Vy -> Stores the value of register Vy in register Vx */
				case 0x0000:
				{
					auto x = get_third_nibble(opcode);
					auto y = get_second_nibble(opcode);

					V[x] = V[y];
				}
					break;
				/* 0x8xy1 - OR Vx, Vy -> Performs a bitwise OR on the values of Vx and Vy, then stores the result in Vx */
				case 0x0001:
				{
					auto x = get_third_nibble(opcode);
					auto y = get_second_nibble(opcode);

					V[x] |= V[y];
				}
					break;
				/* 0x8xy2 - AND Vx, Vy -> Performs a bitwise AND on the values of Vx and Vy, then stores the result in Vx */
				case 0x0002:
				{
					auto x = get_third_nibble(opcode);
					auto y = get_second_nibble(opcode);

					V[x] &= V[y];
				}
					break;
				/* 0x8xy3 - XOR Vx, Vy -> Performs a bitwise XOR on the values of Vx and Vy, then stores the result in Vx */
				case 0x0003:
				{
					auto x = get_third_nibble(opcode);
					auto y = get_second_nibble(opcode);

					V[x] ^= V[y];
				}
					break;
				/* 0x8xy4 - ADD Vx, Vy -> The values of Vx and Vy are added together. If the result is greater than 8 bits VF is set to 1 */
				case 0x0004:
				{
					auto x = get_third_nibble(opcode);
					auto y = get_second_nibble(opcode);
					auto f = 0xF;

					V[f] = (V[y] > (0xFF - V[x])) ? 1 : 0;
					V[x] += V[y];
				}
					break;
				/* 0x8xy5 - SUB Vx, Vy -> If Vx > Vy, then VF is set. Then Vy is subtracted from Vx, and the results stored in Vx */
				case 0x0005:
				{
					auto x = get_third_nibble(opcode);
					auto y = get_second_nibble(opcode);
					auto f = 0xF;

					V[f] = (V[x] > V[y]) ? 1 : 0;
					V[x] -= V[y];
				}
					break;
				/* 0x8xy6 - SHR Vx {, Vy} -> If the least-significant bit of Vx is 1, then VF is set. Then Vx is divided by 2 */
				case 0x0006:
				{
					auto x = get_third_nibble(opcode);
					auto f = 0xF;

					V[f] = (V[x] & LSB_SET) ? 1 : 0;
					V[x] >>= LSB_SET;
				}
					break;
				/* 0x8xy7 - SUBN Vx, Vy -> If Vy > Vx, then VF is set. Then Vx is subtracted from Vy, and the results stored in Vx */
				case 0x0007:
				{
					auto x = get_third_nibble(opcode);
					auto y = get_second_nibble(opcode);
					auto f = 0xF;

					V[f] = (V[y] > V[x]) ? 1 : 0;
					V[x] = V[y] - V[x];
				}
					break;
				/* 0x8xyE - SHL Vx {, Vy} -> If the most-significant bit of Vx is 1, then VF is set. Then Vx is multiplied by 2 */
				case 0x000E:
				{
					auto x = get_third_nibble(opcode);
					auto f = 0xF;

					V[f] = (V[x] & MSB_SET) ? 1 : 0;
					V[x] <<= LSB_SET;
				}
					break;
				/* Unrecognized opcode */
				default:
					throw std::runtime_error("Illegal instruction encountered, opcode: 0x" + std::to_string(opcode));
			}
			break;
		/* 0x9xy0 - SNE Vx, Vy -> The values of Vx and Vy are compared, and if they are not equal, the program counter is increased by 2 */
		case 0x9000:
		{
			auto x = get_third_nibble(opcode);
			auto y = get_second_nibble(opcode);

			if (!equal(V[x], V[y]))
			{
				fetch();
			}
		}
			break;
		/* 0xAnnn - LD I, addr -> The value of register I is set to nnn */
		case 0xA000:
			I = get_destination_address(opcode);
			break;
		/* 0xBnnn - JP V0, addr -> The program counter is set to nnn plus the value of V0 */
		case 0xB000:
		{
			auto nnn = get_destination_address(opcode);
			PC = nnn + V[0];
		}
			break;
		/* 0xCxkk - RND Vx, byte -> The interpreter generates a random number from 0 to 255, which is then ANDed with the value kk. The results are stored in Vx */
		case 0xC000:
		{
			auto x = get_third_nibble(opcode);
			auto kk = get_first_byte(opcode);

			std::random_device device;
			std::mt19937 generator(device());
			std::uniform_int_distribution<> distribution(0, 255);

			V[x] = distribution(generator) & kk;
		}
			break;
		/* 0xDxyn - DRW Vx, Vy, nibble -> Display n-byte sprite starting at memory location I at (Vx, Vy), set VF = collision */
		case 0xD000:
		{
			auto x = get_third_nibble(opcode);
			auto y = get_second_nibble(opcode);
			auto n = get_first_nibble(opcode);
			auto f = 0xF;

			V[f] = draw_sprite(V[x], V[y], n, memory[I]) ? 1 : 0;
		}
			break;
		case 0xE000:
		{
			switch (opcode & 0xFF)
			{
				/* 0xEx9E - SKP Vx -> Skip next instruction if key with the value of Vx is pressed */
				case 0x9E:
				{
					auto x = get_third_nibble(opcode);

					if (is_key_pressed(V[x]))
					{
						fetch();
					}
				}
					break;
				/* 0xExA1 - SKNP Vx -> Skip next instruction if key with the value of Vx is not pressed */
				case 0xA1:
				{
					auto x = get_third_nibble(opcode);

					if (!is_key_pressed(V[x]))
					{
						fetch();
					}
				}
					break;
				/* Unrecognized opcode */
				default:
					throw std::runtime_error("Illegal instruction encountered, opcode: 0x" + std::to_string(opcode));
			}
		}
			break;
		case 0xF000:
		{
			switch (opcode & 0xFF)
			{
				/* 0xFx07 - LD Vx, DT -> The value of DT is placed into Vx */
				case 0x07:
				{
					auto x = get_third_nibble(opcode);

					V[x] = DT;
				}
					break;
				/* 0xFx0A - LD Vx, K -> Wait for a key press, store the value of the key in Vx */
				case 0x0A:
				{
					auto x = get_third_nibble(opcode);

					V[x] = sdl_wait_for_key_press();
				}
					break;
				/* 0xFx15 - LD DT, Vx -> DT is set equal to the value of Vx */
				case 0x15:
				{
					auto x = get_third_nibble(opcode);

					DT = V[x];
				}
					break;
				/* 0xFx18 - LD ST, Vx -> ST is set equal to the value of Vx */
				case 0x18:
				{
					auto x = get_third_nibble(opcode);

					ST = V[x];
				}
					break;
				/* 0xFx1E - ADD I, Vx -> The values of I and Vx are added, and the results are stored in I */
				case 0x1E:
				{
					auto x = get_third_nibble(opcode);

					I += V[x];
				}
					break;
				/* 0xFx29 - Fx29 - LD F, Vx -> The value of I is set to the location for the hexadecimal sprite corresponding to the value of Vx */
				case 0x29:
				{
					auto x = get_third_nibble(opcode);

					I = V[x] * DEFAULT_SPRITE_SIZE;
				}
					break;
				/* 0xFx33 - Fx29 - LD B, Vx -> Store BCD representation of Vx in memory locations I, I + 1, and I + 2 */
				case 0x33:
				{
					auto x = get_third_nibble(opcode);

					write_mem(V[x] / HUNDREDS, I);
					write_mem((V[x] / TENS) % TENS, I + 1);
					write_mem(V[x] % TENS, I + 2);
				}
					break;
				/* 0xFx55 - Fx29 - LD [I], Vx -> Store registers V0 through Vx in memory starting at location I */
				case 0x55:
				{
					auto x = get_third_nibble(opcode);

					for (auto i = 0; i <= x; i++)
					{
						write_mem(V[i], I + i);
					}
				}
					break;
				/* 0xFx55 - Fx29 - LD Vx, [I] -> Read registers V0 through Vx from memory starting at location I */
				case 0x65:
				{
					auto x = get_third_nibble(opcode);

					for (auto i = 0; i <= x; i++)
					{
						V[i] = read_mem(I + i);
					}
				}
					break;
				/* Unrecognized opcode */
				default:
					throw std::runtime_error("Illegal instruction encountered, opcode: 0x" + std::to_string(opcode));
			}
		}
			break;
		/* Unrecognized opcode */
		default:
			throw std::runtime_error("Illegal instruction encountered, opcode: 0x" + std::to_string(opcode));
	}
}

void Chip8CPU::run(const SDL_Color& color)
{
	bool pause { false };

	SDL_Window *window;
	SDL_Renderer *renderer;

	sdl_initialize(&window, &renderer);

	while (running)
	{
		sdl_poll_events(pause);

		if (!pause)
		{
			sdl_render(renderer, color);
			timer_tick();
			auto opcode = decode();
			fetch();
			execute(opcode);
		}
	}

	sdl_restore(&window);
}
