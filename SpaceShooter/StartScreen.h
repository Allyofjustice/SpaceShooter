#ifndef STARTSCEEN_H
#define STARTSCREEN_H

#include "GameState.h"
#include <SDL_mixer.h>

class StartScreen : public GameState{
public:
	StartScreen(); //loads the media
	~StartScreen();
	void handle_events();
	void logic();
	void render(SDL_Surface* gameScreen);

private:
	SDL_Surface *background;
	Mix_Music *music;
};

#endif