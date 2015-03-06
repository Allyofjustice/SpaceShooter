#include "MyTimer.h"
#include "SDL.h"

MyTimer::MyTimer(){
	startTicks = 0;
	pausedTicks = 0;

	paused = false;
	started = false;
}

void MyTimer::start(){
	started = true;
	paused = false;

	startTicks = SDL_GetTicks();
	pausedTicks = 0;
}

void MyTimer::stop(){
	started = false;
	paused = false;
	startTicks = 0;
	pausedTicks = 0;
}

void MyTimer::pause(){
	if (started && !paused){
		paused = true;
		pausedTicks = SDL_GetTicks() - startTicks;
		startTicks = 0;
	}
}

void MyTimer::unpause(){
	if (started && paused){
		paused = false;
		startTicks = SDL_GetTicks() - pausedTicks;
		pausedTicks = 0;
	}
}

int MyTimer::getTicks(){
	int time = 0;

	if (started){
		if (paused)
			time = pausedTicks;
		else
			time = SDL_GetTicks() - startTicks;
		
	}

	return time;
}

bool MyTimer::isStarted(){
	return started;
}

bool MyTimer::isPaused(){
	return paused;
}