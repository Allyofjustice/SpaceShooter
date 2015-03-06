#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "SDL.h"
#include <vector>
#include <list>
#include "Sprite.h"
#include "player.h"
#include "Timer.h"
#include "SDL_ttf.h"
#include <string> 
#include <sstream>
#include "MyTimer.h"

class GameEngine{
public:
	GameEngine(int width, int height, std::vector<Sprite*> gameObjects, Player *player1);
	void run();
	bool getQuit();
	
private:
	const int FPS = 60; 
	const int TICKS_PER_FRAME = 1000 / FPS;

	void cleanup();
	void init();
	void removeDead();
	void sort();
	void checkCollisions();
	void draw();
	void update();

	std::vector<Sprite*> gameObjects;
	std::vector<SolidSprite*> collisionObjects;
	std::vector<Sprite*> noCollisionObjects;
	int width;
	int height;
	SDL_Surface* gameScreen; //= SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE); //640, 480, 32 SDL_SWSURFACE
	SDL_Surface *message;

	TTF_Font *font;
	SDL_Event event;
	Player* player1;
	SDL_Rect offset;
	SDL_Color textColor;
	int score;
	int scoreTimerGap = 10000;
	std::stringstream strScore;
	std::stringstream strLife;
	bool quit = false;
	bool gameOver;
	
	
};
#endif