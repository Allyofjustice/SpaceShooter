#include "GameState.h"

GameState* GameState::get_next_state(){
	return nextState;
}

void GameState::set_next_state(GameState* next){
	nextState = next;
}

bool GameState::get_exit(){
	return exit;
}