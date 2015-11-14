#ifndef SOLIDOBJ_H
#define SOLIDOBJ_H
#include "Sprite.h"


class SolidSprite : public Sprite{
public:
	SolidSprite(int xx, int yy, SDL_Surface* img);
	SolidSprite(int xx, int yy, SDL_Surface* img, int xSpeed, int ySpeed, int health, int atk);

	virtual ~SolidSprite(void);
	virtual void collides(SolidSprite* other);
	virtual void update();
	void draw(SDL_Surface* surface);
	SDL_Rect getHitBox();
	int getAttack();
	void setAttack(int newAttack);
	int getHealth();
	void setHealth(int newHealth);
	bool isDead();
	void setDead(bool dead);
	bool isBadGuy();
	void setBadGuy(bool isBad);
	void attack(SolidSprite *other);

protected:
	
	SDL_Rect hitBox;
	
private:
	bool badGuy;
	int armor = 0;
	int attackValue = 0;
	int health = 1;
	bool dead = false;
	
	
};

#endif