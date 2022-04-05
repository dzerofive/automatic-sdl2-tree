#include "game.h"

Game::Game()
	{
		int sdlResult = SDL_Init(SDL_INIT_VIDEO);
		if (sdlResult != 0) 
        {
			Logger::log(Fatal, "Failed to initialize SDL.");
			std::exit(1);
		}
		Logger::log("SDL initialized successfully.");

		mainWindow = SDL_CreateWindow(windowName, 100, 100, 1280, 720, SDL_WINDOW_OPENGL);
		if (!mainWindow) 
        {
			Logger::log(Fatal, "Failed to initialize SDL window: %s.", SDL_GetError());
			std::exit(1);
		}
		Logger::log("SDL window initialized successfully.");

		mainRenderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	}

Game::~Game()
{
	SDL_DestroyWindow(mainWindow);
    SDL_DestroyRenderer(mainRenderer);
	SDL_Quit();
}


void Game::processInput() 
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            shouldRun = false;
            Logger::log(Ok, "Program quit by user request: Close button on window been pressed.");
            break;
        
        default:
            break;
        }

        const Uint8* state = SDL_GetKeyboardState(NULL);
        if (state[escapeKey])
        {
            shouldRun = false;
            Logger::log(Ok, "Program quit by user request: Escape key been pressed.");
        }

        
        if (state[SDL_SCANCODE_W]) Logger::log("W has been pressed!");

    }
}

void Game::runLoop() 
{
	while(this->shouldRun)
	{
		processInput();
		updateGame();
		generateOutput();
	}
}

void Game::updateGame()
{

}

void Game::generateOutput()
{
    SDL_SetRenderDrawColor(mainRenderer, 20, 20, 25, 255);
    SDL_RenderClear(mainRenderer);

    // Draw frame
    SDL_SetRenderDrawColor(mainRenderer, 200, 200, 200, 255);
    SDL_Rect walls[4] = {
        {0, 0, 1280, 10}, 
        {0, 710, 1280, 10},
        {0, 0, 10, 720},
        {1270, 0, 10, 720},};
    for(int i = 0; i < 4; i++)
    {
        SDL_RenderFillRect(mainRenderer, &walls[i]);
    }
    
    // Draw paddle
    SDL_SetRenderDrawColor(mainRenderer, 200, 60, 60, 255);
    paddleLocation = {60, 400};
    SDL_Rect paddleDrawLocation{(int)paddleLocation.x-10, (int)(paddleLocation.y-(paddleHeight/2)), 20, (int)paddleHeight};
    SDL_RenderFillRect(mainRenderer, &paddleDrawLocation);
    // Draw paddle debug point
    SDL_SetRenderDrawColor(mainRenderer, 200, 200, 200, 255);
    SDL_Rect paddleDebugPoint{(int)paddleLocation.x-4, (int)paddleLocation.y-4, 8, 8};
    SDL_RenderFillRect(mainRenderer, &paddleDebugPoint);

    // Draw ball
    SDL_SetRenderDrawColor(mainRenderer, 200, 200, 200, 255);
    ballLocation = {400, 400};
    SDL_Rect ballDrawLocation{(int)(ballLocation.x-(ballRadius/2)), (int)(ballLocation.y-(ballRadius/2)), (int)ballRadius, (int)ballRadius};
    SDL_RenderFillRect(mainRenderer, &ballDrawLocation);

    SDL_RenderPresent(mainRenderer);
}