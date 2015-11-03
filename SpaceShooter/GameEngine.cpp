#include "GameEngine.h"
#include <iostream>
#include <vector>
#include <list>
#include "SDL_ttf.h"
#include <SDL_mixer.h>
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
	//SDL_INIT_EVERYTHING?
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) 
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
	
	TTF_Init();
	
	if(Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) { 
		printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n"); 
	}

	music = Mix_LoadMUS("Saturnine.wav");
	Mix_PlayMusic(music, -1);

	gameScreen = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE);
	textColor = { 255, 255, 255 };
	SDL_WM_SetCaption("Space Meme", NULL);
	font = TTF_OpenFont("lazy.ttf", 58);
	sort();
}
void GameEngine::run(){
	init();
	mainMenu();

	MyTimer fpsTimer;
	MyTimer frameTimer;
	int frames = 0;
	quit = false;
	gameOver = false;
	fpsTimer.start();

	while (!quit && !gameOver){
		frameTimer.start();
		checkCollisions();
		handleInput();
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
		if (frameTimer.getTicks() < TICKS_PER_FRAME) //cap the fps to 60
			SDL_Delay(TICKS_PER_FRAME - frameTimer.getTicks());
		frames++;
		
		currentFPS = 1 / (frameTimer.getTicks() / 1000.f);
		frameTimer.stop();
		
	}//while

	cleanup();
};

void GameEngine::pause(){
	//while ()
}

void GameEngine::handleInput(){
	player1->handleInput(event, &collisionObjects);
	/*
	if (event.type == SDL_KEYDOWN){
		switch (event.key.keysym.sym){
		case SDLK_P: setYspd(0); break;
		case SDLK_DOWN:setYspd(0); break;
		case SDLK_LEFT:setXspd(0); break;
		case SDLK_RIGHT: setXspd(0); break;


		}
	}
	*/
}
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
	
	playerHealth = player1->getHealth();
	strLife << "Health: " << playerHealth;
	SDL_FreeSurface(message); // Removes the old message before making the new
	message = TTF_RenderText_Solid(font, strLife.str().c_str(), textColor);
	offset.x = 10; offset.y = 10;
	SDL_BlitSurface(message, NULL, gameScreen, &offset);
	strLife.str(""); //Tömmer strömmen

	stringstream fps;
	fps << currentFPS;
	SDL_FreeSurface(message); // Removes the old message before making the new
	message = TTF_RenderText_Solid(font, fps.str().c_str(), textColor);
	offset.x = 1000; offset.y = 10;
	SDL_BlitSurface(message, NULL, gameScreen, &offset);
	
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

	//Free music   we call Mix_FreeChunk() to get rid of the sound effects and Mix_FreeMusic() to free the music.
	Mix_FreeMusic(music);

	//Free surfaces
	SDL_FreeSurface(message);
	SDL_FreeSurface(gameScreen);

	Mix_CloseAudio();
	TTF_CloseFont( font ); 
	TTF_Quit();
	SDL_Quit();
	
}

bool GameEngine::getQuit(){
	return quit;
}

void GameEngine::mainMenu(){
	SDL_Surface* screen = IMG_Load("mainMenu.png");
	SDL_Rect offset;
	offset.x = 0; offset.y = 0;
	SDL_BlitSurface(screen, NULL, gameScreen, &offset);
	SDL_Flip(gameScreen);

	Uint8 *keystates = SDL_GetKeyState(NULL);

	bool quit = false;
	while (!quit){
		if (SDL_PollEvent(&event)){
			if (event.type == SDL_QUIT)
				quit = true;
			
			if (event.key.keysym.sym == SDLK_RETURN)
				quit = true;
			
		}
	}
	
} 