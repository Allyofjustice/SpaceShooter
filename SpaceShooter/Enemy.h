#include "SolidSprite.h"
#ifndef ENEMY_H
#define ENEMY_H
class Enemy: public SolidSprite{
public:
	static Enemy* newEnemy(int xx, int yy, SDL_Surface* img);
	virtual ~Enemy(void);
	void update();
	void collides(SolidSprite* other);
	virtual void move();

protected:
	Enemy(int xx, int yy, SDL_Surface* img);


	
};

#endif