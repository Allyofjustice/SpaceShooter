#include "GameEngine.h"
#include <iostream>
#include <vector>
#include <list>
#include "SDL_ttf.h"
#include <string>
#include <sstream>
using namespace std;

GameEngine::GameEngine(int width, int height, std::vector<Sprite*> gameObjects, Player *player1){
	this->width = width;
	this->height = height;
	this->gameObjects = gameObjects;
	this->player1 = player1;
	
	
	
};

void GameEngine::init(){
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	gameScreen = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE);
	textColor = { 255, 255, 255 };
	SDL_WM_SetCaption("Space game", NULL);
	font = TTF_OpenFont("lazy.ttf", 58);
	sort();
}
void GameEngine::run(){
	init();

	MyTimer fpsTimer;
	MyTimer frameTimer;
	int frames = 0;
	fpsTimer.start();
	
	quit = false;
	gameOver = false;
	while (!quit && !gameOver){

		frameTimer.start();
		checkCollisions();
		player1->handleInput(event, &collisionObjects);
		update();
		removeDead();

		if (player1->getHealth() <= 0){
			gameOver = true;
		}
		
		draw();
		
		if (SDL_PollEvent(&event)){
			if (event.type == SDL_QUIT){
				quit = true;
			}
		}	
		
		frames++;
		cout << "FPS: " << frames / (fpsTimer.getTicks() / 1000.f) << endl;
		
		if ( frameTimer.getTicks() < TICKS_PER_FRAME)
			SDL_Delay(TICKS_PER_FRAME - frameTimer.getTicks());

		frameTimer.stop();
	}//while

	cleanup();
};
void  GameEngine::update(){

	for (unsigned i = 0; i < collisionObjects.size(); i++){
		collisionObjects.at(i)->update();
	}

	for (unsigned i = 0; i < noCollisionObjects.size(); i++){
		noCollisionObjects.at(i)->update();
	}
	
};
void GameEngine::draw(){
	
	SDL_FillRect(gameScreen, &gameScreen->clip_rect, SDL_MapRGB(gameScreen->format, 0x0, 0x0, 0x0));

	//Draw background etc
	for (unsigned i = 0; i < noCollisionObjects.size(); i++){
		noCollisionObjects.at(i)->draw(gameScreen);
	}

	//Draw SolidSprite objects
	for (unsigned i = 0; i < collisionObjects.size(); i++){
		collisionObjects.at(i)->draw(gameScreen);
	}

	strLife << "Life: " << player1->getHealth();
	message = TTF_RenderText_Solid(font, strLife.str().c_str(), textColor);
	offset.x = 10; offset.y = 10;
	SDL_BlitSurface(message, NULL, gameScreen, &offset);
	strLife.str(""); //Tömmer strömmen

	if (gameOver){
		message = TTF_RenderText_Solid(font, "Game over", textColor);
		offset.x = 500; offset.y = 360;
		SDL_BlitSurface(message, NULL, gameScreen, &offset);
		SDL_Flip(gameScreen);
		SDL_Delay(2000);
	}
	else
		SDL_Flip(gameScreen);
};

void GameEngine::checkCollisions(){
	for (unsigned i = 0; i < collisionObjects.size(); i++){
		for (unsigned k = 0; k < collisionObjects.size(); k++){
			if (i != k) //Jämför inte samma objekt
				collisionObjects.at(i)->collides(collisionObjects.at(k));
			
		}
	}

	
}

void GameEngine::sort(){

	SolidSprite* resultingPtr;
	for (unsigned i = 0; i < gameObjects.size(); i++){
		resultingPtr = dynamic_cast<SolidSprite*>(gameObjects.at(i));
		if (resultingPtr != NULL){
			//std::cout << "den här har collision" << i;
			collisionObjects.push_back(resultingPtr);
		}
		else{
			noCollisionObjects.push_back(gameObjects.at(i));
		}
	}

	//std::cout <<"storlek: " << collisionObjects.size();
}

void GameEngine::removeDead(){
	SolidSprite* temp;
	for (unsigned i = 0; i < collisionObjects.size(); i++){
		if (collisionObjects.at(i)->isDead() == true){
			temp = collisionObjects.at(i);
			collisionObjects.erase(collisionObjects.begin() + i);
			std::cout << "tar bort object. Storlek " << collisionObjects.size() << std::endl;
			delete temp;
			
		}
	}
}

void GameEngine::cleanup(){

	//SDL_FreeSurface();
	SDL_FreeSurface(message);
	SDL_FreeSurface(gameScreen);
	TTF_CloseFont( font ); 
	TTF_Quit();
	SDL_Quit();
	
}

bool GameEngine::getQuit(){
	return quit;
}