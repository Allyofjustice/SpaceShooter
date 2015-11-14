#ifndef GAMEOVERSCREEN_H
#define GAMEOVERSCREEN_H

#include "GameState.h"
#include <SDL_mixer.h>

class GameOverScreen : public GameState{
public:
	GameOverScreen(); 
	~GameOverScreen();
	void handle_events();
	void logic();
	void render(SDL_Surface* gameScreen);
private:
	const int FRAMES_UNTIL_EXIT = 60 * 4; // Frames until next screen. ~4 seconds
	int currentFrames = 0; //Counts up with every frame
	SDL_Surface *background;
	Mix_Music *music;
};

#endif