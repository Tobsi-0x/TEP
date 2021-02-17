#pragma once

#include <SDL2/SDL.h>
#include <GL/glew.h>

enum class GameState {
	PLAY,
	EXIT
};

class MainWindow
{

public:
	MainWindow();
	~MainWindow();

	void run();

private:

	// Functions
	void initSystem();
	void gameLoop();
	void procInput();
	void draw();

	// varialbes
	SDL_Window* _window;
	SDL_Renderer* _render;

	// int
	int _screenWidth;
	int _screenHeight;

	// enum
	GameState _gameState;

};

