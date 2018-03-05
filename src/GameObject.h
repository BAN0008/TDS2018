#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SFML/Graphics/Sprite.hpp>

class GameObject
{
public:
	int x, y, w, h, originX, originY;
	sf::Sprite sprite;
	bool placeFree(int _x, int _y); //Should this be private?

	static GameObject* collisionPoint(int _x, int _y);

	~GameObject(); //Likely causing "pure virtual method called" runtime error

	int objectID;
};
#endif
