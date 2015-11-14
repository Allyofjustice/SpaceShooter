#include "GameEngine.h"
#include <iostream>
#include <vector>
#include <list>
#include "SDL_ttf.h"
#include <SDL_mixer.h>
#include <string>
#include <sstream>

using namespace std;

GameEngine::GameEngine(int width, int height){
	this->width = width;
	this->height = height;
};

void GameEngine::init(){
	//SDL_INIT_EVERYTHING?
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) 
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
	
	if(Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) { 
		printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n"); 
	}
	//TODO move to states??
	gameScreen = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE);
	SDL_WM_SetCaption("Space Meme", NULL);
}
void GameEngine::run(){
	init();

	MyTimer fpsTimer;
	MyTimer frameTimer;
	int frames = 0;
	fpsTimer.start();

	currentState = new StartScreen(); //First state is always a start screen.

	//Loop until user cancels the window
	while (currentState->get_exit() == false){ 
		frameTimer.start();
		
		currentState->handle_events();
		currentState->logic();
		change_state();
		currentState->render(gameScreen);


		if (frameTimer.getTicks() < TICKS_PER_FRAME) //cap the fps to 60
			SDL_Delay(TICKS_PER_FRAME - frameTimer.getTicks());
		frames++;
		
		currentFPS = 1 / (frameTimer.getTicks() / 1000.f);
		frameTimer.stop();
		
	}//while

	cleanup();
};

//Change to the next state which is specified in the current state
void GameEngine::change_state(){

	//If there's a state to change to
	if (currentState->get_next_state() != NULL){
		GameState* temp = currentState->get_next_state();
		//free the recourses of the old state
		delete currentState;
		currentState = temp;
	}

}

void GameEngine::cleanup(){
	delete currentState;
	SDL_FreeSurface(gameScreen);
	Mix_Quit(); //Is this needed?
	IMG_Quit(); //needed?
	SDL_Quit(); //clean up all initialized subsystems
}
