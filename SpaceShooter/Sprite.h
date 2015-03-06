#ifndef SPRITE_H
#define SPRITE_H

#include "SDL.h"
#include "SDL_image.h"
#include <string>


class Sprite{

public:
	Sprite(int xx, int yy, SDL_Surface* img);
	virtual ~Sprite(void);

	virtual void draw(SDL_Surface* surface);
	virtual void update() =0;
	bool hasCollision();
	
	SDL_Surface* getImage();
	int getXspd();
	int getYspd();
	void setXspd(int value);
	void setYspd(int value);
	int getX();
	int getY();
	void setX(int value);
	void setY(int value);
	int getHeight();
	int getWidth();

	
protected:
	
	int x;
	int y;
	int xSpeed = 0;
	int ySpeed = 0;
	SDL_Surface* image;
	bool collidable = false;



};

#endif