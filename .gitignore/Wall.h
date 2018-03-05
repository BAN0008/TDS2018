#ifndef WALL_H
#define WALL_H

#include <SFML/Graphics/Texture.hpp>
#include "GameObject.h"

class Wall : public GameObject
{
public:
	sf::Texture texture;

	Wall(int _x, int _y, int _w, int _h);
};
#endif