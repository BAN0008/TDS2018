#include <math.h>
#include "Bullet.h"
#include "Global.h"

Bullet::Bullet(GameObject* master, sf::Vector2f direction) : master(master)
{
	x = master->x + master->originX;
	y = master->y + master->originY;
	/*
	sprite.setTexture(texBullet);
	w = 8;
	h = 8;

	objectID = BULLET_ID;

	sprite.setOrigin(3.0f, 3.0f);
	originX = 3;
	originY = 3;
	*/
	
	sf::Image image;
	float length = 10.0f;
	image.create(length * direction.x, length * direction.y, sf::Color(0, 0, 0, 0));
	sf::Color colour(255, 255, 0, 255);
	for (float i = 0; i < length; i++)
	{
		image.setPixel(std::floor(direction.x * i), std::floor(direction.y * i), colour);
	}
	sf::Texture* texture;
	texture->update(image);
	sprite.setTexture(*texture);

}

void Bullet::update()
{
	x += direction.x * speed;
	y += direction.y * speed;
	sprite.setPosition(x + originX, y + originY);
}
