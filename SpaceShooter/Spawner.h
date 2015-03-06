#ifndef SPAWNER_H
#define SPAWNER_H

#include "Sprite.h"
#include <vector>

class Spawner{
public:
	Spawner();
	void spawn(std::vector<Sprite*>* gameObjects, int ticks);
private:
	bool wave1;
	bool wave2;
	bool wave3;
	bool wave4;
	bool wave5;
};

#endif