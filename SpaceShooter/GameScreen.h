#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include "GameState.h"
#include "Player.h"
#include "Background.h"
#include <SDL_mixer.h>
#include <map>

using namespace std;

class GameScreen : public GameState{

public:
	GameScreen();
	~GameScreen();
	void handle_events();
	void logic();
	void render(SDL_Surface* gameScreen);

private:
	//TODO: Not constant???
	const int SCREEN_WIDTH = 1280; //Width of the window
	const int SCREEN_HEIGHT = 720; //Height of the window

	Player *player1;
	Background *bg;
	Mix_Music *music;


	//map<char, vector <SolidSprite*>> gameObjects;
	//std::vector<Sprite*> gameObjects; //Holds all the game objects 
	vector<SolidSprite*> friendlyObjects; //Player and friendly bullets
	vector<SolidSprite*> enemies; // Enemies and enemy bullets.

	//Methods
	void pause();
	bool has_collided(SolidSprite *a, SolidSprite *b); //Check collision between two objects and do damage to each
	void check_collisions(); //Check collision for all solid objects in game
	void removeDead(); // Remove dead objects 
};

#endif