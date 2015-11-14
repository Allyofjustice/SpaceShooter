#include "StartScreen.h"
#include "GameScreen.h"
#include <iostream>
//Loads the background and music
StartScreen::StartScreen(){
	
	std::cout << "Create startscreen" << std::endl;
	background = IMG_Load("mainMenu.png");
	music = Mix_LoadMUS("intro.wav");
	Mix_PlayMusic(music, -1); 
}

//Frees the music and background
StartScreen::~StartScreen(){
	SDL_FreeSurface(background);
	Mix_FreeMusic(music);
}

void StartScreen::handle_events(){
	SDL_Event event;
	if (SDL_PollEvent(&event)){
		if (event.type == SDL_QUIT){
			exit = true;
		}
		if (event.key.keysym.sym == SDLK_RETURN){
			nextState = new GameScreen();
		}
	}
}

//No logic for the start screen
void StartScreen::logic(){
}

void StartScreen::render(SDL_Surface* gameScreen){
	SDL_Rect offset;
	offset.x = 0; offset.y = 0;
	SDL_BlitSurface(background, NULL, gameScreen, &offset);
	SDL_Flip(gameScreen);
}