#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "GameObject.h"

class Player : public GameObject
{
public:
	void update();

	Player(int _x, int _y);

	float vspeed, hspeed;

	int cooldown = 0;
	int health = 100;

private:
	void fire(int _x, int _y);
};

#endif
