#include "Sprite.h"
#include <iostream>
Sprite::Sprite(int xx, int yy, SDL_Surface* img){
	x = xx;
	y = yy;
	image = img;
}

Sprite::~Sprite(void){
	SDL_FreeSurface(image);
}

void Sprite::draw(SDL_Surface* surface){
	SDL_Rect offset;
	offset.x = x; offset.y = y;
	SDL_BlitSurface(image, NULL, surface, &offset);
};
/*
void Sprite::update(){
}

*/
int Sprite::getX(){return x;};
int Sprite::getY(){ return y; };

void Sprite::setX(int value){
	x = value;
}

void Sprite::setY(int value){
	y = value;
}

SDL_Surface* Sprite::getImage(){
	return image;
};
int Sprite::getXspd(){
	return xSpeed;
};
int Sprite::getYspd(){
	return ySpeed;
};

void Sprite::setXspd(int value){
	xSpeed = value;
}

void Sprite::setYspd(int value){
	ySpeed = value;
}

int Sprite::getHeight(){
	return image->h;
}
int Sprite::getWidth(){
	return image->w;
}
