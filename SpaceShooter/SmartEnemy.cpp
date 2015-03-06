#include "SmartEnemy.h"
#include <iostream>

SmartEnemy::SmartEnemy(int xx, int yy, SDL_Surface* img, Player* p1) : Enemy(xx, yy, img){
	player1 = p1;
	setXspd(-1);
	setYspd(1);
	setHealth(1);
	setBadGuy(true);
}

SmartEnemy* SmartEnemy::newSmartEnemy(int xx, int yy, SDL_Surface* img, Player* p1){

	return new SmartEnemy(xx, yy, img, p1);
}

SmartEnemy::~SmartEnemy(void){}

void SmartEnemy::move(){
	
	if (player1->getY() < getY() && getYspd() > 0)
		setYspd(getYspd() *-1);
	else if(player1->getY() > getY() && getYspd() < 0){
		setYspd(getYspd() *-1);
	}
	
	
	setX(getX() + getXspd());
	setY(getY() + getYspd());
	
}