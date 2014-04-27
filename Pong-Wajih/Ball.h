#pragma once
#include <SDL.h>
#include <random>
#define BALL_WIDTH 10
#define BALL_HEIGHT 10
#define BALL_SPEED 5.0
#define BALL_MAXSPEED  9.0
#define BALL_ACCELERATE 1.06

class Ball
{
public:
	Ball(float ,float,float ,float );
	~Ball();
	void Update();
	void Reset(float, float);
	void UpdateRect(int, int);
	
	float x;
	float y;
	float dx;
	float dy;
	float hieght;
	float width;
	float speed;
	SDL_Rect ballRect;

};

