#ifndef NPC_H
#define NPC_H

#include "GameObject.h"
#include "AStar.h" //Path

class NPC : public GameObject
{
public:
	int health = 100;
	int cooldown = 0;
	int pathPosition; //Should be private(only public for debug purposes. See Main.cpp)

	NPC(int _x, int _y);

	void fire(int _x, int _y);
	void update() override;
private:
	bool followPath = true;
	int speed = 5;
	Path path;
};

#endif
