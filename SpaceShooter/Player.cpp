#include "Player.h"
#include <iostream>

Player::Player(int xx, int yy, SDL_Surface* img) : SolidSprite(xx, yy, img){
	setAttack(1);
	setHealth(PLAYER_HEALTH);
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
	
	Uint8 *keystates = SDL_GetKeyState(NULL);
	if (keystates[SDLK_UP])
		setYspd(MAX_Y_SPEED * -1); 
	else if (keystates[SDLK_DOWN])
		setYspd(MAX_Y_SPEED);
	else
		setYspd(0);
	
	if (keystates[SDLK_LEFT])
		setXspd(MAX_X_SPEED * -1);
	else if (keystates[SDLK_RIGHT])
		setXspd(MAX_X_SPEED);
	else
		setXspd(0);
		
	if (keystates[SDLK_SPACE]){
		if (frames >= SHOOT_CD){
			SDL_Surface* bulletImg = IMG_Load("bullet1.png");
			SDL_SetColorKey(bulletImg, SDL_SRCCOLORKEY, SDL_MapRGB(bulletImg->format, 0xFF, 0xFF, 0xFF));

			SolidSprite* bullet = new SolidSprite(getX(), getY(), bulletImg, 30, 0, 1, getAttack());
			bullet->setBadGuy(false);
			gameObjects->push_back(bullet);
			frames = 0;
		}
	}
	/*
	if (event.type == SDL_KEYUP){
		switch (event.key.keysym.sym){
		case SDLK_UP: setYspd(0); break;
		case SDLK_DOWN:setYspd(0); break;
		case SDLK_LEFT:setXspd(0); break;
		case SDLK_RIGHT: setXspd(0); break;

		
		}
	}
	*/
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