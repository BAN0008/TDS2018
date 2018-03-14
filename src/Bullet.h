#ifndef BULLET_H
#define BULLET_H

#include <SFML/System.hpp>
#include "GameObject.h"

class Bullet : public GameObject
{
public:
	Bullet(GameObject* master, sf::Vector2f direction);
	void update() override;
//private:
	double speed;
	sf::Vector2f direction;
	GameObject* master;
};

#endif //BULLET_H