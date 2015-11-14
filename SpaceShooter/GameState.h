#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "SDL_image.h"

class GameState{
public:
	//Keyboard events
	virtual void handle_events() = 0;
	virtual void logic() = 0;
	virtual void render(SDL_Surface* gameScreen) = 0; // Render stuff on the gamescreen
	virtual ~GameState(){}
	GameState* get_next_state();
	void set_next_state(GameState* next);
	bool get_exit();
protected:
	GameState* nextState; // If null there's no new state to change to.
	bool exit = false; // If user exits from window this is true
};

#endif