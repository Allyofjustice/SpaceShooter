#include "SolidSprite.h"
#include <iostream>

SolidSprite::SolidSprite(int xx, int yy, SDL_Surface* img) : Sprite(xx, yy, img){
	
}

SolidSprite::SolidSprite(int xx, int yy, SDL_Surface* img, int xSpeed, int ySpeed, int health, int atk) : Sprite(xx, yy, img){
	setXspd(xSpeed);
	setYspd(ySpeed);
	this->health = health;
	attackValue = atk;
}

SolidSprite::~SolidSprite(void){
}

void SolidSprite::update(){
	if (health <= 0 || getX() <= 0 || getX() >= 1280 || getY() <= 0 || getY() + getHeight()  >= 720){
		dead = true;
	}
	else{
		x += xSpeed;
		y += ySpeed;
	}
}

void SolidSprite::collides(SolidSprite* other){
	//Kolla inte collision mot andra från samma fraktion.
	if (badGuy != other->isBadGuy()){
	
		if (other->getX() < (getX() + getWidth()) && (other->getX() + other->getWidth()) > getX() && (getY() + getHeight()) > other->getY() && getY() < (other->getY() + other->getHeight())) {
			setHealth(getHealth() - other->getAttack()); //Tar bort liv om träffad
			std::cout << "Kolliderar" << std::endl;
		}
	}

}
void SolidSprite::draw(SDL_Surface* surface){
	SDL_Rect offset;
	offset.x = x; offset.y = y;
	SDL_BlitSurface(image, NULL, surface, &offset);

	//SDL_FillRect(surface, &hitBox, SDL_MapRGB(surface->format, 255, 0, 0));
	
};

SDL_Rect SolidSprite::getHitBox(){
	return hitBox;
}

int SolidSprite::getAttack(){
	return attackValue;
}

void SolidSprite::setAttack(int newAttack){
	attackValue = newAttack;
}

int SolidSprite::getHealth(){
	return health;
}

void SolidSprite::setHealth(int newHealth){
	health = newHealth;
}

bool SolidSprite::isDead(){
	return dead;
}

void SolidSprite::setDead(bool dead){
	this->dead = dead;
}

bool SolidSprite::isBadGuy(){
	return badGuy;
}

void SolidSprite::setBadGuy(bool isBad){
	badGuy = isBad;
}

//Reduce the health of the attacked object by the current object's attack value
void SolidSprite::attack(SolidSprite *other){
	other->health -= attackValue;
}