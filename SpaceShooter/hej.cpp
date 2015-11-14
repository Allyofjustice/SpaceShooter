#include "SDL.h"
#include "SDL_image.h"
#include <SDL_mixer.h>

#include "Sprite.h"
#include "GameEngine.h"
#include <iostream>
#include "SolidSprite.h"
#include "Player.h"
#include "Enemy.h"
#include "SmartEnemy.h"
#include "Background.h"
int main(int argc, char* args[]) { 
	/*
	SDL_Surface* ship = IMG_Load("paintShip.png");
	SDL_SetColorKey(ship, SDL_SRCCOLORKEY, SDL_MapRGB(ship->format, 0xFF, 0xFF, 0xFF));
	
	Mix_Chunk *gScratch = NULL;

	SDL_Surface* rustled = IMG_Load("jimmy.jpg");
	SDL_Surface* rustled2 = IMG_Load("jimmy.jpg");

	SDL_Surface* rock = IMG_Load("rock.jpg");
	SDL_SetColorKey(rock, SDL_TRUE, SDL_MapRGB(rock->format, 0xFF, 0xFF, 0xFF));

	SDL_Surface* spaceBg = IMG_Load("poorSpace.png");
	//SDL_Surface* hehe = IMG_Load("hehe.jpg");
	
	Background bg(0, 0, spaceBg);
	Background* bgPek = &bg;

	Player p(100, 500, ship);
	Player* player1 = &p;

	Enemy* spaceMonkey1 = Enemy::newEnemy(1400, 200, rustled);
	Enemy* spaceMonkey2 = Enemy::newEnemy(500, 400, rustled2);
	SmartEnemy* rock1 = SmartEnemy::newSmartEnemy(800, 500, rock, player1);

	std::vector<Sprite*> obj;
	obj.push_back(bgPek);
	obj.push_back(spaceMonkey1);
	obj.push_back(spaceMonkey2);
	obj.push_back(rock1);
	obj.push_back(player1);

	GameEngine eng(1280, 720, obj, player1);

	eng.run();
	

	//Rensa
	delete spaceMonkey1;
	delete spaceMonkey2;
	delete rock1;
	
	
	
	*/
	return 0;
}

