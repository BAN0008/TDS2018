#include "Wall.h"
#include <SFML/Graphics/Image.hpp>
#include "Global.h"

Wall::Wall(int _x, int _y, int _w, int _h)
{
	x = _x;
	y = _y;
	w = _w;
	h = _h;

	objectID = WALL_ID;

	sf::Image tempImage;
	tempImage.create(w, h, sf::Color::White);
	texture.loadFromImage(tempImage);
	sprite.setTexture(texture);
	sprite.setPosition(x, y);
}
