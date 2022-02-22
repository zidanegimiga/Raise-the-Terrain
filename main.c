#include "terrain.h"

/* render window (global) */
SDL_Window *gWindow = NULL;

/* window renderer (global) */
SDL_Renderer *gRenderer = NULL;

/**
 * init - initializes SDL, window, and renderer
 * Return: True on success, False on failure
 */
bool init(void)
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n",
		       SDL_GetError());
		success = false;
	}
	else
	{
		gWindow = SDL_CreateWindow("Raise the Terrain",
					   SDL_WINDOWPOS_UNDEFINED,
					   SDL_WINDOWPOS_UNDEFINED,
					   SCREEN_WIDTH, SCREEN_HEIGHT,
					   SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n",
			       SDL_GetError());
			success = false;
		}
		else
		{
			gRenderer =
				SDL_CreateRenderer(gWindow, -1,
						   SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created!");
				printf("SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
				SDL_SetRenderDrawColor(gRenderer, 0x2D, 0x4C,
						       0x76, 0xFF);
		}
	}
	return (success);
}

/**
 * main - main function for program
 * @argc: number of arguments passed
 * @argv: pointer to array of arguments
 * Return: 0 on success
 */
int main(int argc, char *argv[])
{
	SDL_Point **rows;
	SDL_Point **cols;
	int i, j;

	rows = generate_rows();
	cols = generate_cols();

	if (!init())
		printf("Failed to initialize!\n");
	else
	{
		bool quit = false;
		SDL_Event e;

		while (!quit)
		{
			while (SDL_PollEvent(&event) != 0)
			{
				/* user requests quit */
				if (event.type == SDL_QUIT)
					quit = true;

				if (event.type == SDL_KEYDOWN &&
				    event.key.keysym.sym == SDLK_ESCAPE)
					quit = true;
			}
      
			SDL_SetRenderDrawColor(gRenderer, 0x31, 0x5D, 0x5F, 0xFF);
			SDL_RenderClear(gRenderer);

			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			for (i = 0; i < POINTS; i++)
			{
				SDL_RenderDrawLines(gRenderer, rows[i], POINTS);
				SDL_RenderDrawLines(gRenderer, cols[i], POINTS);
			}
			SDL_RenderPresent(gRenderer);
		}
	}
	closeSDL(gWindow, gRenderer, rows, cols);
	return (0);
}
