#include "MainWindow.h"

#include <iostream>
#include <string>

void errorHandler(std::string errorString) {
	std::cout << errorString << std::endl;
	SDL_Quit();
}

MainWindow::MainWindow() {
	_window = nullptr;
	_render = nullptr;

	// Screen Width & Height. 600x400 is a nice square. Reminds me of old games.
	_screenWidth = 600;
	_screenHeight = 400;

	_gameState = GameState::PLAY;
}

MainWindow::~MainWindow() {

	std::cout << "Init: [CLEANUP]" << std::endl;
	// SDL Cleanup
	SDL_DestroyRenderer(_render);
	SDL_DestroyWindow(_window);
	SDL_Quit();
}


void MainWindow::run() {
	initSystem();

	gameLoop();
}

void MainWindow::initSystem() {

	// Init SDL https://wiki.libsdl.org/SDL_Init
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		// SDL_Log("SDL Init: [FAILED] Error code: ", SDL_GetError());
		std::cout << "SDL Init: [FAILED] Error code: " << SDL_GetError() << std::endl;

		_gameState = GameState::EXIT;
	}
	else
	{
		// SDL_Log("SDL Init: [SUCCESSFUL]");
		std::cout << "SDL Init: [SUCCESSFUL]" << std::endl;
	}

	// Makes a Window
	_window = SDL_CreateWindow("Project ProgC", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, SDL_WINDOW_OPENGL);

	if (_window == nullptr)
	{
		errorHandler("SDL Window: [FAILED]");
	}
	else
	{
		std::cout << "SDL Window: [SUCCESSFUL]" << std::endl;
	}

	SDL_GLContext glContext = SDL_GL_CreateContext(_window);
	if (glContext == nullptr)
	{
		errorHandler("SDL_GL: [FAILED]");
	}
	else
	{
		std::cout << "SDL_GL: [SUCCESSFUL]" << std::endl;
	}


	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		errorHandler("glew Init: [FAILED]");
	}
	else
	{
		std::cout << "glew Init: [SUCCESSFUL]" << std::endl;
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // Smooth rendering

	glClearColor(0.07f, 0.07f, 0.27f, 1.0f); // https://convertingcolors.com/rgb-color-19_19_70.html?search=RGB(19,%2019,%2070)

}

void MainWindow::gameLoop() {
	while (_gameState != GameState::EXIT)
	{
		procInput();
		draw();
	}

	MainWindow::~MainWindow();
}

void MainWindow::procInput() {
	SDL_Event evnt;


	while (SDL_PollEvent(&evnt)) // https://wiki.libsdl.org/SDL_PollEvent 
	{
		switch (evnt.type) { // https://wiki.libsdl.org/SDL_Event look under:  Relationships between event types and union members
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			std::cout << "Window state: [CLOSE AND STOP (BTN)]" << std::endl;
			break;

		case SDL_KEYUP:

			if (evnt.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
				_gameState = GameState::EXIT;
				std::cout << "Window state: [CLOSE AND STOP (ESC)]" << std::endl;
			}

			break;

		case SDL_MOUSEMOTION: // Prints the X and Y cords
			std::cout << "Mouse Pos : X = " << evnt.motion.x << " || Y = " << evnt.motion.y << std::endl;
			break;

		case SDL_MOUSEBUTTONDOWN:
			std::cout << "MouseBtn pressed: " << evnt.button.type << std::endl;
			break;
		}
	}
}

void MainWindow::draw() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draws a triangle
	glEnableClientState(GL_COLOR_ARRAY);
	glBegin(GL_TRIANGLES);
	glColor3f(0.5f, 0.25f, 0.0f);
	/*glVertex2f(100, 200);
	glVertex2f(100, 350);
	glVertex2f(300, 200);*/
	glVertex2f(0, 0); // not shure why, but i dont think it's x and y cords.
	glVertex2f(0, 300);
	glVertex2f(200, 300);

	glEnd();

	SDL_GL_SwapWindow(_window);
}
