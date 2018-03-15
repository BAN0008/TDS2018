#include <csignal> //Remove Me
#include <math.h>
#include "Bullet.h"
#include "Global.h"

Bullet::Bullet(GameObject* master, sf::Vector2f direction) : master(master), direction(direction)
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
	float length = 64.0f;
	sf::Color colour(255, 255, 0, 255);
	sprite.setOrigin(length / 2.0f, 0.0f);
	image.create(length, 1.0f);
	for (int i = 0; i < length; i++)
	{
		image.setPixel(i, 0, colour);
	}
	originX = length / 2.0f;
	originY = 0;
	/*
	image.create(std::max(length * abs(direction.x), 1.0f), std::max(length * abs(direction.y), 1.0f), sf::Color(255, 0, 0, 255));
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
	*/
	sf::Texture* texture;
	texture = new sf::Texture();
	texture->create(image.getSize().x, image.getSize().y);
	texture->update(image);
	sprite.setTexture(*texture);
	sprite.setRotation(atan2(direction.y, direction.x) * (180 / M_PI));

}

void Bullet::update()
{
	for (int i = 0; i < speed; i++)
	{
		GameObject *collision = collisionPoint(x + direction.x, y + direction.y, {this, master});
		if (collision == nullptr)
		{
			x += direction.x * speed;
			y += direction.y * speed;
		}
		else
		{
			sf::Image tempImage = collision->sprite.getTexture()->copyToImage();
			sf::Color colour(0.0f, 0.0f, 0.0f, 0.0f);
			tempImage.setPixel(x - collision->x, y - collision->y, colour);
			sf::Texture *newTexture = new sf::Texture();
			newTexture->create(tempImage.getSize().x, tempImage.getSize().y);
			newTexture->update(tempImage);
			collision->sprite.setTexture(*newTexture);
			delete this;
			goto end; //Jump to end of update so that the object doesn't try to access any of it's members(eg sprite)
		}
	}
	sprite.setPosition(x + originX, y + originY);
	end:
	int temp = 0; //Remove Me
}
