#include "Chip8CPU.h"

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		std::cerr << "Insufficient number of arguments supplied." << '\n';
		return EXIT_FAILURE;
	}

	try
	{
		Chip8CPU emulator {};
		emulator.emulate(argv[1]);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;

	/*const char* TITLE = "Hello World SDL2 + TTF";
	const int WIDTH = 1280, HEIGHT = 720;

	SDL_Window *window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Event windowEvent;

	TTF_Init();

	TTF_Font *verdanaFont = TTF_OpenFont("../fonts/UbuntuMono-B.ttf", 50);
	SDL_Color textColor = { 255, 255, 255, 255 };
	SDL_Surface *textSurface = TTF_RenderText_Solid(verdanaFont, "Hello World", textColor);
	SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

	SDL_Rect textRect;
	textRect.x = 0;
	textRect.y = 0;
	textRect.w = textSurface->w;
	textRect.h = textSurface->h;

	SDL_FreeSurface(textSurface);

	SDL_Surface *textSurface1 = TTF_RenderText_Solid(verdanaFont, "Marak", textColor);
	SDL_Texture *textTexture1 = SDL_CreateTextureFromSurface(renderer, textSurface1);

	SDL_Rect textRect1;
	textRect1.x = 50;
	textRect1.y = 50;
	textRect1.w = textSurface1->w;
	textRect1.h = textSurface1->h;

	SDL_FreeSurface(textSurface1);

	TTF_Quit();

	bool isRunning = true;
	while (isRunning) {
		while(SDL_PollEvent(&windowEvent)) {
			switch (windowEvent.type) {
				case SDL_QUIT:
					isRunning = false;
					break;
			}
		}
		SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
		SDL_RenderPresent(renderer);
		SDL_RenderCopy(renderer, textTexture1, NULL, &textRect1);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyTexture(textTexture);
	SDL_DestroyTexture(textTexture1);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return EXIT_SUCCESS;*/
}
