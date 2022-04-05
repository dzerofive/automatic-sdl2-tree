#pragma once

#include "../include/SDL2/SDL.h"
#include "logger.h"
#include <cstdlib>

class Game
{
private:

	SDL_Window* mainWindow;
	SDL_Renderer* mainRenderer;
	bool shouldRun = true; // Shutdown when FLASE
	
	const char* windowName = "Loliconic";
	const SDL_Scancode escapeKey = SDL_SCANCODE_ESCAPE; // Key to close application
	
	// PONG TEST, TO BE REMOVED
	struct Vector2 {float x, y;};
	Vector2 ballLocation, paddleLocation;
	float paddleHeight = 160, ballRadius = 12;

public:

	Game();	// Initizlize game
	~Game(); // Shutdown game

	void processInput(); // Keyboard, mouse, gamepad
	void updateGame(); // Logic
	void generateOutput(); // Render stuff
	void runLoop(); // Run game loop, exit game when exit loop
};
