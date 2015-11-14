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
#include <SDL_mixer.h>
#include "StartScreen.h"

class GameEngine{
public:
	GameEngine(int width, int height);
	void run();
	
private:
	const int FPS = 60; 
	const int TICKS_PER_FRAME = 1000 / FPS;
	double currentFPS;
	int width;
	int height;
	SDL_Surface* gameScreen; //= SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE); //640, 480, 32 SDL_SWSURFACE
	GameState *currentState; //Stores the current state of the game

	//functions
	void change_state(); 
	void cleanup();
	void init();
	void draw();
	void update();
	void pause();
	void handleInput();
	
};
#endif