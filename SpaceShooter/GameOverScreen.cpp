#include "GameOverScreen.h"
#include "StartScreen.h"
#include <iostream>

//Loads the background and music
GameOverScreen::GameOverScreen(){

	std::cout << "Create GameOverScreen" << std::endl;
	background = IMG_Load("gameover.png");
	music = Mix_LoadMUS("gameover.wav");
	Mix_PlayMusic(music, 1);
}

//Frees the music and background
GameOverScreen::~GameOverScreen(){
	SDL_FreeSurface(background);
	Mix_FreeMusic(music);
}

void GameOverScreen::handle_events(){
	SDL_Event event;
	if (SDL_PollEvent(&event)){
		if (event.type == SDL_QUIT){
			exit = true;
		}
		if (event.key.keysym.sym == SDLK_RETURN){
			nextState = new StartScreen();
		}
	}
}

//No logic for the Game over screen
void GameOverScreen::logic(){
	currentFrames++;
	if (currentFrames == FRAMES_UNTIL_EXIT)
		nextState = new StartScreen();
}

void GameOverScreen::render(SDL_Surface* gameScreen){
	SDL_Rect offset;
	offset.x = 0; offset.y = 0;
	SDL_BlitSurface(background, NULL, gameScreen, &offset);
	SDL_Flip(gameScreen);
}