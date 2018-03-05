#include "NPC.h"
#include "Player.h"
#include "Global.h"
#include <cmath>
//#include <algorithm>
#include <iostream>

NPC::NPC(int _x, int _y) : path(2560 / 32, 1080 / 32)
{
	x = _x;
	y = _y;
	w = 48;
	h = 48;
	originX = 23;
	originY = 23;

	sprite.setTexture(texPlayer);
	sprite.setOrigin(23.0f, 23.0f);
	sprite.setTextureRect(sf::IntRect(0, 0, 68, 48));
	sprite.setPosition(x, y);

	objectID = NPC_ID;

	pathPosition = 0;
	//path = Path(2560 / 32, 1080 / 32);
	for (unsigned i = 0; i < gameObjects.size(); i++)
	{
		if (gameObjects[i]->objectID == WALL_ID)
		{
			path.addWall(gameObjects[i]->x / 32 , gameObjects[i]->y / 32);
		}
	}
	path.findPath(x / 32, y / 32, 50, 20);
	path.generatePath();
	for (int i = 0; i < path.size(); i++)
	{
		std::cout << '{' << path[i]->x * 32 << ", " << path[i]->y * 32 << '}' << std::endl;
	}
	/*for (int i = 0; i < path.size(); i++)
	{
		gameObjects.push_back(new Player(path[i]->x * 32, path[i]->y * 32));
	}*/
	path.print(x / 32, y / 32, 50, 20);
	x = path[0]->x * 32;
	y = path[0]->y * 32;
}

void NPC::fire(int _x, int _y)
{
	sf::Vector2f pos(x + originX, y + originY);
	sf::Vector2f vec(_x - pos.x, _y - pos.y);
	float length = sqrt((vec.x * vec.x) + (vec.y * vec.y));
	sf::Vector2f direction(vec / length);

	while (true)
	{
		GameObject* col = GameObject::collisionPoint(pos.x, pos.y);
		if (col != nullptr && col != this)
		{
			switch (col->objectID)
			{
				case PLAYER_ID:
					static_cast<Player*>(col)->health -= 40;
					break;
			}
			break;
		}
		pos += direction;
	}
}

void NPC::update(GameObject* _player)
{
	if (health <= 0)
	{
		sf::Color temp(sprite.getColor());
		if (sprite.getColor().a == 0)
		{
			delete this;
		}
		temp.a -= 55;
		sprite.setColor(temp);
	}

	//if (!checkLineOfSight(_player, this))
	if (false)
	{
		sprite.setPosition(-72.0f, -72.0f);
	}
	else
	{
		sprite.setPosition(x, y);
		if (cooldown == 0)
		{
			cooldown = 5;
			if (globalSound)
			{
				sndGun.play();
			}
			fire(_player->x, _player->y);
		}
	}

	if (cooldown > 0)
	{
		cooldown--;
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::U))
	{
		pathPosition++;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
	{
		pathPosition--;
	}
	if (followPath)
	{
		/*
		int prevX = x;
		x += sgn(path[pathPosition]->vx) * fmin(abs(path[pathPosition]->vx * speed), abs(path[pathPosition]->vx - x));
		y += sgn(path[pathPosition]->vy) * fmin(abs(path[pathPosition]->vy * speed), abs(path[pathPosition]->vy - y));
		if (x == path[pathPosition]->x * 32 && y == path[pathPosition]->y * 32)
		{
			pathPosition++;
		}
		*/
		
		for (int i = 0; i < abs(path[pathPosition]->vy * speed); i++)
		{
			if (y != path[pathPosition]->y * 32)
			{
				y += sgn(path[pathPosition]->vy * speed);
			}
			else
			{
				//pathPosition++;
				break;
			}
		}
		for (int i = 0; i < abs(path[pathPosition]->vx * speed); i++)
		{
			if (x != path[pathPosition]->x * 32)
			{
				x += sgn(path[pathPosition]->vx * speed);
			}
			else
			{
				pathPosition++;
				break;
			}
		}

		//std::cout << (path[pathPosition]->vx) * fmin(abs(path[pathPosition]->vx * speed), abs(path[pathPosition]->vx - x));
		//std::cout << fmin(abs(path[pathPosition]->vx * speed), abs(path[pathPosition]->vx - x));
		//std::cout << path[pathPosition]->vx;
		/*
		x = path[pathPosition]->x * 32;
		y = path[pathPosition]->y * 32;
		pathPosition++;
		*/
		if (pathPosition == path.size())
		{
			followPath = false;
		}
	}
}
