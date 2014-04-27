#include "Ball.h"


Ball::Ball(float x, float y, float hieght , float width)
{
	this->x = x;
	this->y = y;
	this->speed = BALL_SPEED;
	this->hieght = hieght;
	this->width = width;


	ballRect.w = BALL_HEIGHT;
	ballRect.h = BALL_HEIGHT;

	this->dx = (rand() % 2 == 0) ? BALL_SPEED : -1 * BALL_SPEED;
	this->dy = -0.5f;
}
void Ball::Update()
{
		if (dx > BALL_MAXSPEED)
			dx = BALL_MAXSPEED;

		if (dx > BALL_MAXSPEED)
			dx = BALL_MAXSPEED;

		// Update Ball coordinates
		x += dx;
		y += dy;

}
void Ball::UpdateRect(int x, int y){
		ballRect.x = x;
		ballRect.y = y;

}
void Ball::Reset(float x, float y){
	this->x = ballRect.x =x;
	this->y = ballRect.y =y;

	dx = 0.2;
	dy = 0.2;
	this->speed = BALL_SPEED;
}

Ball::~Ball()
{
}
