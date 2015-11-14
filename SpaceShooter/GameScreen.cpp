#include "GameScreen.h"
#include <iostream>
#include "StartScreen.h"
#include "GameOverScreen.h"

GameScreen::GameScreen()
{
	std::cout << "Create GameScreen" << std::endl;

	//Background
	SDL_Surface* spaceBg = IMG_Load("poorSpace.png");
	bg = new Background(0, 0, spaceBg);

	//Player ship
	SDL_Surface* ship = IMG_Load("paintShip.png");
	SDL_SetColorKey(ship, SDL_SRCCOLORKEY, SDL_MapRGB(ship->format, 0xFF, 0xFF, 0xFF));
	player1 = new Player(100,500, SCREEN_WIDTH, SCREEN_HEIGHT, ship);
	player1->setHealth(3);
	friendlyObjects.push_back(player1);

	//Music
	music = Mix_LoadMUS("Saturnine.wav");
	Mix_PlayMusic(music, -1);

	//Enemies
	SDL_Surface* rock = IMG_Load("rock.jpg");
	SDL_SetColorKey(rock, SDL_SRCCOLORKEY, SDL_MapRGB(rock->format, 0xFF, 0xFF, 0xFF));
	enemies.push_back(new SolidSprite(1000, 500, rock, -10, 0, 1, 1));
	enemies.push_back(new SolidSprite(1000, 600, IMG_Load("rock.jpg") , -5, 0, 1, 1));
	enemies.push_back(new SolidSprite(1000, 300, IMG_Load("rock.jpg"), -2, 0, 1, 1));
}

//TODO
GameScreen::~GameScreen(){
	Mix_FreeMusic(music);
	delete bg;

	//Delete all objects
	for (SolidSprite* obj : friendlyObjects)
		delete obj;

	for (SolidSprite* obj : enemies)
		delete obj;
}

void GameScreen::handle_events(){
	SDL_Event event;
	if (SDL_PollEvent(&event)){
		if (event.type == SDL_QUIT){
			exit = true;
		}
		//pause game if p-key is pressed
		if (event.key.keysym.sym == SDLK_p){
			pause();
		}
		//Restarts the game
		if (event.key.keysym.sym == SDLK_ESCAPE){
			nextState = new StartScreen();
		}
	}

	player1->handleInput(&friendlyObjects);
}

//Update all game objects
void GameScreen::logic(){
	
		check_collisions();
		bg->update();
		for (Sprite *obj : friendlyObjects){
			obj->update();
		}

		for (Sprite *obj : enemies){
			obj->update();
		}
		removeDead();

		//Go to game over screen If the player dies 
		if (player1->getHealth() <= 0)
			nextState = new GameOverScreen();
}

//Render all game objects
void GameScreen::render(SDL_Surface* gameScreen){
	bg->draw(gameScreen);

	for (Sprite *obj : friendlyObjects){
		obj->draw(gameScreen);
	}

	for (Sprite *obj : enemies){
		obj->draw(gameScreen);
	}
	
	SDL_Flip(gameScreen);
}

//pause until 'o'-key is pressed
void GameScreen::pause(){
	SDL_Event event;

	while (true){

		if (SDL_PollEvent(&event)){
			if (event.key.keysym.sym == SDLK_o){
				break;
			}
		}
	}
}

//Check collision for all objects and do damage to both if collided
void GameScreen::check_collisions(){
	for (SolidSprite* friendly : friendlyObjects){
		for (SolidSprite* enemy : enemies){
			if (has_collided(friendly, enemy)){
				if (cout << "Collision detected" << endl)
				friendly->attack(enemy);
				enemy->attack(friendly);
			}
			
		}
	}
}
bool GameScreen::has_collided(SolidSprite *a, SolidSprite *b){
	
		//if the hitboxes overlap return true     
		if (a->getX() < (b->getX() + b->getWidth()) && (a->getX() + a->getWidth()) > b->getX() && (b->getY() + b->getHeight()) > a->getY() && b->getY() < (a->getY() + a->getHeight())){
			return true;
		}
		else{
			return false;
		}
	

	
}

// Remove objects that are dead. TODO: Can I use shared pointers here???
void GameScreen::removeDead(){
	//Check for dead good guys
	for (unsigned i = 0; i < friendlyObjects.size(); i++){
		if (friendlyObjects[i]->isDead()){
			delete friendlyObjects[i];
			friendlyObjects.erase(friendlyObjects.begin() + i);
			//friendlyObjects.erase(friendlyObjects.begin() + i);
		}
	}
	//Check for dead bad guys
	for (unsigned i = 0; i < enemies.size(); i++){
		if (enemies[i]->isDead()){
			delete enemies[i];
			enemies.erase(enemies.begin() + i);
			//enemies.erase(enemies.begin() + i);
		}
	}
}