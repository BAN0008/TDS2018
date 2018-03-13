#include <math.h>
#include <iostream>
#include "Bullet.h"
#include "Global.h"

Bullet::Bullet(GameObject* master, sf::Vector2f direction) : master(master), direction(direction)
{
	x = master->x + master->originX;
	y = master->y + master->originY;
	originX = 0;
	originY = 0;
	/*
	sprite.setTexture(texBullet);
	w = 8;
	h = 8;

	objectID = BULLET_ID;

	sprite.setOrigin(3.0f, 3.0f);
	originX = 3;
	originY = 3;
	*/
	std::cout << direction.x << std::endl;
	std::cout << direction.y << std::endl;
	sf::Image image;
	float length = 64.0f;
	image.create(std::max(length * abs(direction.x), 1.0f), std::max(length * abs(direction.y), 1.0f), sf::Color(255, 0, 0, 255));
	sf::Color colour(255, 255, 0, 255);
	for (float i = 0; i < length; i++)
	{
		int px, py;
		if (direction.x > 0)
		{
			px = std::floor(abs(direction.x * i));
		}
		else
		{
			px = std::floor(image.getSize().x - (abs(direction.x * i)));
		}
		if (direction.y > 0)
		{
			py = std::floor(abs(direction.y * i));
		}
		else
		{
			py = std::floor(image.getSize().y - (abs(direction.y * i)));
		}

		if (px > 0 && px < image.getSize().x && py > 0 && py < image.getSize().y)
		{
			image.setPixel(px, py, colour);
		}
	}
	sf::Texture* texture;
	texture = new sf::Texture();
	texture->create(image.getSize().x, image.getSize().y);
	texture->update(image);
	sprite.setTexture(*texture);

}

void Bullet::update()
{
	std::cout << "Bullet Update" << std::endl;
	std::cout << direction.x << std::endl;
	//std::cout <<  << std::endl;
	std::cout << std::floor(direction.x * speed) << std::endl;
	x += std::floor(direction.x * speed);
	y += std::floor(direction.y * speed);
	sprite.setPosition(x + originX, y + originY);
}
