#ifndef PLAYER_H
#define PLAYER_H

#include "SolidSprite.h"
#include <vector>

class Player : public SolidSprite{
public:
	Player(int xx, int yy, SDL_Surface* img);
	virtual ~Player(void);

	void handleInput(SDL_Event event, std::vector<SolidSprite*> *gameObjects);
	void update();
	void collides(SolidSprite* other);
	void getScore();

private:
	const int SHOOT_CD = 10;
	const int PLAYER_HEALTH = 10;
	const int MAX_X_SPEED = 10;
	const int MAX_Y_SPEED = 10;
	int score;
	int frames = 0;
};

#endif