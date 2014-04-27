#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Ball.h"
class Paddle
{
public:
	Paddle(int, int, SDL_Renderer *ren);
	~Paddle();
	int speed;
	int score;
	int hieght;
	int width;
	SDL_Rect padRect;
	SDL_Texture * texture;
	void setPosition(float,float);
	void moveUp();
	void moveDown();
	void performAI(float);
};

