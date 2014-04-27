#include "Paddle.h"


Paddle::Paddle(int score, int speed, SDL_Renderer *ren)
{
	this->score = score;
	this->speed = speed;
	texture = IMG_LoadTexture(ren, "paddle.png");
	SDL_QueryTexture(texture, NULL, NULL, &width, &hieght);

	padRect.w = width;
	padRect.h = 120;
}
void Paddle::setPosition(float x, float y){
	padRect.x = x;
	padRect.y = y;
}
void Paddle::moveUp(){
	padRect.y -= speed;
}
void Paddle::moveDown(){
	padRect.y += speed;
}
void Paddle::performAI(float yBall){
	if (yBall < padRect.y + padRect.h / 2) {
		padRect.y -= speed;
	}
	if (yBall > padRect.y + padRect.h / 2) {
		padRect.y += speed;
	}
}
Paddle::~Paddle()
{
}
