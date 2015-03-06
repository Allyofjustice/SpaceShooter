#ifndef SMARTENEMY_H
#define SMARTENEMY_H

#include "Enemy.h"
#include "Player.h"

class SmartEnemy : public Enemy{
public:
	static SmartEnemy* newSmartEnemy(int xx, int yy, SDL_Surface* img, Player* player1);
	virtual ~SmartEnemy(void);
	void move();

protected:
	SmartEnemy(int xx, int yy, SDL_Surface* img, Player* p1);

private:
	Player* player1;

};


#endif