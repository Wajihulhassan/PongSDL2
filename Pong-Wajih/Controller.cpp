#include "Controller.h"


Controller::Controller()
{
	InitialiseW(&ren, &win);

}


bool Controller::gameLoop(){


	

	SDL_Texture *squareTex = IMG_LoadTexture(ren, "paddle.png");
	SDL_Texture *squareTex2 = IMG_LoadTexture(ren, "paddle2.png");
	SDL_Texture *squareTex3 = IMG_LoadTexture(ren, "pong-bg-bmp.png");

	SDL_Rect bgRect;
	bgRect.x = 0;
	bgRect.y = 0;
	bgRect.h = 480;
	bgRect.w = 640;


	SDL_QueryTexture(squareTex, NULL, NULL, &board_width, &board_height);
	ball = new Ball(SCREEN_WIDTH / 2, SCREEN_WIDTH / 2, BALL_HEIGHT, BALL_HEIGHT);
	pad1 = new Paddle(0, 10, ren);
	pad2 = new Paddle(0, 3.5, ren);
	pad1->setPosition(board_width / 2 + 10, SCREEN_HEIGHT / 2 - pad1->padRect.h / 2);
	pad2->setPosition(SCREEN_WIDTH - pad2->padRect.w - 10 - pad2->padRect.w / 2, SCREEN_HEIGHT / 2 - pad2->padRect.h / 2);



	bool gameEnd = false;
	while (!gameEnd){
		gameEnd = checkKeyInput();
		pad2->performAI(ball->y);
		ball->Update();
		ballCollision();
		ball->UpdateRect(ball->x, ball->y);
		paddleCollision();
		SDL_RenderClear(ren);
		SDL_RenderCopy(ren, squareTex3, NULL, &bgRect);
		SDL_RenderCopy(ren, squareTex, NULL, &pad1->padRect);
		SDL_RenderCopy(ren, squareTex, NULL, &pad2->padRect);
		// Draw the Ball
		renderTexture(squareTex2, ren, ball->x, ball->y, BALL_WIDTH, BALL_HEIGHT);
		// Display the score;
		DisplayScore(pad1->score, pad2->score); 
	}


	SDL_DestroyTexture(squareTex);
	SDL_DestroyTexture(squareTex2);

	return true;

}
void Controller::DisplayScore(int a, int b){
	char buff[512];
	SDL_Color whiteColor = { 255, 255, 255 };
	itoa(a,buff,10);
	SDL_Texture *playerScore = renderText(buff, "customFont.ttf", whiteColor, 35, ren);
	itoa(b, buff, 10);
	SDL_Texture *comScore = renderText(buff, "customFont.ttf", whiteColor, 35, ren); 
	int width;
	SDL_QueryTexture(playerScore, NULL, NULL, &width, NULL);
	renderTexture(playerScore, ren, SCREEN_WIDTH / 2 - width - 10, 8);
	renderTexture(comScore, ren, SCREEN_WIDTH / 2 + 10, 8);
	SDL_DestroyTexture(playerScore);
	SDL_DestroyTexture(comScore);
	SDL_RenderPresent(ren);
}
bool Controller::checkKeyInput(){
	bool endGame= false;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.scancode) {
			case SDL_SCANCODE_ESCAPE:
				endGame = true;
				break;
			default:
				break;
			}
		}
	}

	const Uint8 *keystates = SDL_GetKeyboardState(NULL);
	// Movements updates
	if (keystates[SDL_SCANCODE_UP])
		pad1->padRect.y -= pad1->speed;
	if (keystates[SDL_SCANCODE_DOWN])
		pad1->padRect.y += pad1->speed;
	return endGame;

}

void Controller::ballCollision(){

	// Checking right and left ends
	if (ball->x < 0) {
		pad2->score += 1;
		ball->x = SCREEN_WIDTH/2;
		ball->y = SCREEN_HEIGHT/2;
		ball->dx = BALL_SPEED;
		ball->speed = BALL_SPEED;
	}
	if (ball->x + BALL_WIDTH >= SCREEN_WIDTH) {
		pad1->score += 1;
		ball->x = SCREEN_WIDTH/2;
		ball->y = SCREEN_HEIGHT/2;
		ball->dx = -1 * BALL_SPEED;
		ball->speed = BALL_SPEED;
	}
	// checking up and down ends
	if (ball->y < 0) {
		ball->y = 0;
		ball->dy *= -1;
	}
	if (ball->y + BALL_HEIGHT >= SCREEN_HEIGHT) {
		ball->y = SCREEN_HEIGHT - BALL_HEIGHT - 1;
		ball->dy *= -1;
	}
	// stopping the paddles
	if (pad1->padRect.y < 0) pad1->padRect.y = 0;
	if (pad1->padRect.y + pad1->padRect.h > SCREEN_HEIGHT) pad1->padRect.y = SCREEN_HEIGHT - pad1->padRect.h;
	if (pad2->padRect.y < 0) pad2->padRect.y = 0;
	if (pad2->padRect.y + pad2->padRect.h > SCREEN_HEIGHT) pad2->padRect.y = SCREEN_HEIGHT - pad2->padRect.h;




}
void Controller::paddleCollision(){

	if (SDL_HasIntersection(&pad1->padRect, &ball->ballRect)) {

		ball->x = pad1->padRect.x + pad1->padRect.w;
		ball->speed = ball->speed * BALL_ACCELERATE;

		float angle = angleCalc(pad1->padRect.y, ball->y, pad1->padRect.h);
		ball->dx = ball->speed * cos(angle);
		ball->dy = ((ball->dy > 0) ? -1 : 1) * ball->speed * sin(angle);
	}
	if (SDL_HasIntersection(&pad2->padRect, &ball->ballRect)) {

		ball->x = pad2->padRect.x - BALL_WIDTH;
		ball->speed = ball->speed * BALL_ACCELERATE;
		float angle = angleCalc(pad2->padRect.y, ball->y, pad2->padRect.h);
		ball->dx = -1 * ball->speed * cos(angle);
		ball->dy = ((ball->dy>0) ? -1 : 1) * ball->speed * sin(angle);
	}
}


float Controller::angleCalc(float y1, float y2, int height) {
	float angle = y1 + height / 2 - y2;
	angle /= height / 2.0;
	return angle * 0.5;
}
void Controller::Cleanup(SDL_Renderer **ren, SDL_Window **win) {
	SDL_DestroyRenderer(*ren);
	SDL_DestroyWindow(*win);

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}
void Controller::DisplayError(std::string str){
	printf("%s = SDL_Error: %s\n", str, SDL_GetError());

}
SDL_Texture* Controller::renderText(const std::string &msg, const std::string &fontPath, SDL_Color color, int fontSize, SDL_Renderer *ren) {
	TTF_Font *font = TTF_OpenFont(fontPath.c_str(), fontSize);
	if (font == nullptr) {
		DisplayError("Cannot Open Font ");
		return nullptr;
	}

	SDL_Surface *surface = TTF_RenderText_Blended(font, msg.c_str(), color);
	if (surface == nullptr) {
		TTF_CloseFont(font);
		DisplayError("Unable to render text to a surface");
		return nullptr;
	}

	SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, surface);
	if (tex == nullptr) {
		DisplayError("Unable to render surface to texture");
	}

	SDL_FreeSurface(surface);
	TTF_CloseFont(font);

	return tex;
}
void Controller::renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h ) {
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	dest.w = w;
	dest.h = h;
	if (w == -1 || h == -1)
		SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);
	SDL_RenderCopy(ren, tex, NULL, &dest);
}
void Controller::InitialiseW(SDL_Renderer **ren, SDL_Window **win) {
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
		DisplayError("Cannot Initialize the SDL");

	*win = SDL_CreateWindow(
		" PONG CS240 ",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH, SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN
		);

	if (*win == nullptr)
		DisplayError("Failed to create SDL Window");

	*ren = SDL_CreateRenderer(*win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (*ren == nullptr)
		DisplayError("Failed to create SDL Renderer");

	const int flags = IMG_INIT_PNG | IMG_INIT_JPG;
	if (IMG_Init(flags) != flags)
		DisplayError("Failed to load the Image loading extensions");

	if (TTF_Init() != 0)
		DisplayError("Failed to load TTF extension");
}


Controller::~Controller()
{
	Cleanup(&ren, &win);

}
