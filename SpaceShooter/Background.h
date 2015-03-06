#ifndef BACKGROUND_H
#define BACKGROUND_H
#include "Sprite.h"
class Background : public Sprite{
public:
	Background(int xx, int yy, SDL_Surface* img);
	Background::~Background(void);
	
	int getWidth();
	int getHeight();
	void draw(SDL_Surface* surface);
	void update();

};

#endif