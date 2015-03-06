#include "Player.h"
#include <iostream>

Player::Player(int xx, int yy, SDL_Surface* img) : SolidSprite(xx, yy, img){
	setAttack(1);
	setHealth(2);
	setBadGuy(false);
	
}

Player::~Player(void)
{
}

void Player::update(){
	//ändra till hitbox?
	if (getHealth() <= 0)
		std::cout << "GAME OVER YEAAH";
	else{
		
		//Ser till att spelaren inte åker ut från vänster/höger kant.
		if (x + image->w >= 1280 && getXspd() > 0 || x <= 0 && getXspd() < 0)
			setXspd(getXspd() - getXspd());
		//Top/down
		if (y + image->h >= 720 && getYspd() > 0 || y <= 0 && getYspd() < 0)
			setYspd(getYspd() - getYspd());
		
		setX(getX() + getXspd());
		setY(getY() + getYspd());
	}
};
/*
void shoot(bool activated){
	SDL_Surface* bulletImg = IMG_Load("bullet1.png");
	SolidSprite* bullet = new SolidSprite(getX(), getY(), bulletImg, 4, 0, 1, getAttack());
	bullet->setBadGuy(false);
	gameObjects->push_back(bullet);
	std::cout << "En kula" << std::endl;
}
*/
void Player::handleInput(SDL_Event event, std::vector<SolidSprite*> *gameObjects){
	frames++;
	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym){
		case SDLK_UP: setYspd(-4); break;
		case SDLK_DOWN:setYspd(4); break;
		case SDLK_LEFT:setXspd(-4); break;
		case SDLK_RIGHT: setXspd(4); break;
		case SDLK_SPACE:
			if (frames >= SHOOT_CD){
				SDL_Surface* bulletImg = IMG_Load("bullet1.png");
				SolidSprite* bullet = new SolidSprite(getX(), getY(), bulletImg, 4, 0, 1, getAttack());
				bullet->setBadGuy(false);
				gameObjects->push_back(bullet);
				std::cout << "En kula" << std::endl;
				frames = 0;
				break;
			}
		}

	}
	else if (event.type == SDL_KEYUP){
		switch (event.key.keysym.sym){
		case SDLK_UP: setYspd(0); break;
		case SDLK_DOWN:setYspd(0); break;
		case SDLK_LEFT:setXspd(0); break;
		case SDLK_RIGHT: setXspd(0); break;

		
		}
	}

}

void Player::collides(SolidSprite* other){
	//Only check collision against enemies
	if (other->isBadGuy()){
		if (other->getX() < (getX() + getWidth()) && (other->getX() + other->getWidth()) > getX() && (getY() + getHeight()) > other->getY() && getY() < (other->getY() + other->getHeight())) {
			int newHealth = getHealth() - other->getAttack();
			setHealth(newHealth);
		}
	}
	
}