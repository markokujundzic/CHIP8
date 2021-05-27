#include "Chip8Menu.h"

int main(int argc, char *argv[]) {
	if (argc < 2) {
		std::cerr << "Insufficient number of arguments supplied." << '\n';
		return EXIT_FAILURE;
	}

	try {
		CHIP8Menu menu;
		menu.render_menu();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
