/* 
	Wajih Ul Hassan 
	Pong SDL 
	Two functions rendertext() and rendertexture() are taken from following website
	https://github.com/chaficnajjar/pong/blob/master/src/utilities.hpp
*/

#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdlib.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "Paddle.h"
#include "Ball.h"
#pragma warning(disable: 4996)
#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT  480

class Controller
{
public:
	Controller();
	~Controller();

	// Main game loop
	bool gameLoop();
	// handle ball collision with boundaries
	void ballCollision();
	// handle ball collitision with paddles
	void paddleCollision();
	// calculate angle between ball and paddle 
	float angleCalc(float, float, int);
	// This free the SDL memory 
	void Cleanup(SDL_Renderer **ren, SDL_Window **win);
	// Display error in formated form
	void DisplayError(std::string str);
	// Render the message on screen
	// https://github.com/chaficnajjar/pong/blob/master/src/utilities.hpp
	SDL_Texture* renderText(const std::string &msg, const std::string &fontPath, SDL_Color color, int fontSize, SDL_Renderer *ren);
	void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w = -1, int h = -1);
	// 
	// Initialize the window 
	void InitialiseW(SDL_Renderer **ren, SDL_Window **win);
	// Display score on the Window
	void DisplayScore(int a, int b);
	bool checkKeyInput();
private:
	Paddle* pad1;
	Paddle *pad2;
	Ball *ball;
	SDL_Event event;
	SDL_Renderer *ren = nullptr;
	SDL_Window *win = nullptr;
	int board_width;
	int board_height;
	

};


