#include "GameObject.h"
#include "Global.h"

//The below function should probably be replaced with a checkCollision function that can check for intersection with specific types of objects
bool GameObject::placeFree(int _x, int _y) //arguments named to stop conflicts between GameObject member variables and the method arguments
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		if (gameObjects[i]->objectID == WALL_ID)
		{
			//TODO: Check to see if gameObjects[i] intersects with the calling GameObject and return an appropriate value
			//TODO: Change instances of x to _x and y to _y
			int ax, aw, ay, ah, bx, bw, by, bh;

			if (x + w > gameObjects[i]->x)
			{
				ax = _x;
				aw = ax + w;
				bx = gameObjects[i]->x;
				bw = bx + gameObjects[i]->w;
			}
			else
			{
				ax = gameObjects[i]->x;
				aw = ax + gameObjects[i]->w;
				bx = _x;
				bw = bx + w;
			}

			if (y + h > gameObjects[i]->y)
			{
				ay = _y;
				ah = ay + h;
				by = gameObjects[i]->y;
				bh = by + gameObjects[i]->h;
			}
			else
			{
				ay = gameObjects[i]->y;
				ah = ay + gameObjects[i]->h;
				by = _y;
				bh = by + h;
			}

			if (gameObjects[i] != this && aw > bx && ax < bw && ah > by && ay < bh)
			{
				return false;
			}
		}
	}
	return true;
}

GameObject* GameObject::collisionPoint(int _x, int _y)
{
	for (int i = 0; i < gameObjects.size(); i++)
	{

		if (_x >= gameObjects[i]->x && _x <= gameObjects[i]->x + gameObjects[i]->w && _y >= gameObjects[i]->y && _y <= gameObjects[i]->y + gameObjects[i]->h)
		{
			return gameObjects[i];
		}
	}
	return nullptr;
}

GameObject::~GameObject()
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		if (gameObjects[i] == this)
		{
			gameObjects[i] = nullptr;
			gameObjects.erase(gameObjects.begin() + i);
		}
	}
}

void GameObject::update() {}

void GameObject::draw(sf::RenderWindow* window)
{
	window->draw(sprite);
}