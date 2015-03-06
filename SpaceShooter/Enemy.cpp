#include "Enemy.h"
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include <time.h> 

Enemy::Enemy(int xx, int yy, SDL_Surface* img) : SolidSprite(xx, yy, img){
	setXspd(-3);
	setAttack(1);
	setHealth(1);
	setBadGuy(true);
	srand(time(NULL));
}

Enemy* Enemy::newEnemy(int xx, int yy, SDL_Surface* img){
	return new Enemy(xx, yy, img);
}

Enemy::~Enemy(void)
{
	
}

void Enemy::move(){
	setX(getX() + getXspd());
	setY(getY() + getYspd());
}

void Enemy::update(){
	if (getHealth() <= 0 || getX() + getWidth() <= 0){
		//setDead(true);
		setHealth(1);
		setX(1300 + (rand() % 100));
		setY(rand() % 600);
	}	
	else{
		move();
	}
};

void Enemy::collides(SolidSprite* other){
	//Kolla inte collision mot andra fiender.
	if (!other->isBadGuy()){
		//ändrar heheh
		if (other->getX() < (getX() + getWidth()) && (other->getX() + other->getWidth()) > getX() && (getY() + getHeight()) > other->getY() && getY() < (other->getY() + other->getHeight())) {
			std::cout << "Träffad" << std::endl;
			setHealth(getHealth() - other->getAttack()); //Tar bort liv om träffad
		}
	}

}




