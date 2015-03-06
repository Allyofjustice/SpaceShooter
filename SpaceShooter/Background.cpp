#include "Background.h"
#include <iostream>

Background::Background(int xx, int yy, SDL_Surface* img) : Sprite(xx, yy, img){
	setXspd(-5);
}

Background::~Background(void)
{

}

void Background::update(){
	if (getX() + getImage()->w <= 0)
		setX(0);

	setX(getX() + getXspd());
}

void Background::draw(SDL_Surface* surface){
	SDL_Rect offset;
	offset.x = x; offset.y = y;
	SDL_BlitSurface(getImage(), NULL, surface, &offset);
	offset.x = x + getImage()->w;
	SDL_BlitSurface(getImage(), NULL, surface, &offset);
	
}

