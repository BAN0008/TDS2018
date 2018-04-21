#include "NPC.h"
#include "Player.h"
#include "Bullet.h"
#include "Global.h"

#include <math.h>
#include <SFML/Window/Keyboard.hpp> //Remove when keyboard functions are no longer required in the scope
#include <SFML/Window/Mouse.hpp> //------^

int sgn(float a)
{
	if (a < 0)
	{
		return -1;
	}
	if (a == 0)
	{
		return 0;
	}
	if (a > 0)
	{
		return 1;
	}
}

Player::Player(int _x, int _y)
{
	sprite.setTexture(texPlayer);
	x = _x;
	y = _y;
	w = 48;
	h = 48;

	hspeed = 0;
	vspeed = 0;

	objectID = PLAYER_ID;

	sprite.setOrigin(23.0f, 23.0f);
	//sprite.setOrigin(12.0f, 24.0f); //Probably starts at 0 so I should do 11, 23
	originX = 23;
	originY = 23;
	sprite.setTextureRect(sf::IntRect(0, 0, 68, 48));
}

void Player::update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if (hspeed < 8)
		{
			hspeed += 2;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		if (hspeed > -8)
		{
			hspeed -= 2;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		if (vspeed < 8)
		{
			vspeed += 2;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		if (vspeed > -8)
		{
			vspeed -= 2;
		}
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && cooldown == 0)
	{
		if (globalSound)
		{
			sndGun.play();
		}
		sf::Vector2f mousePos = getMousePosition();
		fire(mousePos.x, mousePos.y);
		cooldown = 25;
		sprite.setTextureRect(sf::IntRect(0, 48, 68, 48)); //Offset is wrong to create a shaking effect
	}

	for (int i = 0; i < floor(abs(hspeed)) && placeFree(x + sgn(hspeed), y); i++)
	{
		x += sgn(hspeed);
	}
	for (int i = 0; i < floor(abs(vspeed)) && placeFree(x, y + sgn(vspeed)); i++)
	{
		y += sgn(vspeed);
	}

	if (cooldown > 0)
	{
		cooldown--;
	}

	//Apply Friction
	hspeed = (sgn(hspeed) * (abs(hspeed) * 0.85));
	vspeed = (sgn(vspeed) * (abs(vspeed) * 0.85));
	hspeed = sgn(hspeed) * floor(abs(hspeed));
	vspeed = sgn(vspeed) * floor(abs(vspeed));

	sprite.setPosition(x + originX, y + originY);

	sf::Vector2f mousePos = getMousePosition();
	sprite.setRotation(atan2(mousePos.y - (y + originY), mousePos.x - (x + originX)) * (180.0f / M_PI));



	//Death Code
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
}

void Player::fire(int _x, int _y)
{
	const float angle = sprite.getRotation(); //TODO: change to radians
	const sf::Vector2i firePoint(72, 31);

	sf::Vector2i rotatedFirePoint(std::cos(angle) * );

	//sf::Vector2f pos(x + originX, y + originY);
	sf::Vector2f pos(rotatedFirePoint);
	sf::Vector2f vec(_x - pos.x, _y - pos.y);
	float length = std::sqrt((vec.x * vec.x) + (vec.y * vec.y));
	sf::Vector2f direction(vec / length);

	gameObjects.push_back(new Bullet(this, direction));
	//static_cast<Bullet*>(gameObjects[gameObjects.size() - 1])->direction = direction;
	static_cast<Bullet*>(gameObjects[gameObjects.size() - 1])->speed = 32;

	/*
	while (true)
	{
		GameObject* col = GameObject::collisionPoint(pos.x, pos.y);
		if (col != nullptr && col != this)
		{
			switch (col->objectID)
			{
				case NPC_ID:
					static_cast<NPC*>(col)->health -= 40;
					break;
			}
			break;
		}
		pos += direction;
	}
	*/
}
