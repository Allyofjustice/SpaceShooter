#include "Player.h"
#include <iostream>

Player::Player(int xx, int yy, int screenWidth, int screenHeight, SDL_Surface* img) : SolidSprite(xx, yy, img){
	setAttack(1);
	setHealth(PLAYER_HEALTH);
	setBadGuy(false);
	this->screenWidth = screenWidth; //Width of the window
	this->screenHeight = screenHeight; //height of the window

	shootSound = Mix_LoadWAV("laser1.wav");
}

Player::~Player(void)
{
}

//TODO ta bort hårdkodning av fönsterdimensioner
void Player::update(){
	//Only update if player is alive
	if (getHealth() > 0){
		
		//If the player is outside of left or right border : Remove the x-speed
		if (x + image->w >= screenWidth && getXspd() > 0 || x <= 0 && getXspd() < 0)
			setXspd(getXspd() - getXspd());
		//Top/down
		if (y + image->h >= screenHeight && getYspd() > 0 || y <= 0 && getYspd() < 0)
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
void Player::handleInput(std::vector<SolidSprite*> *objectContainer){
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
			objectContainer->push_back(bullet);

			Mix_PlayChannel(-1, shootSound, 0); //Play laser sound while shooting

			frames = 0;
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