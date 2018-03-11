#include "Global.h"
#include <math.h> //For checkLineOfSight()

sf::Texture texPlayer;
sf::Texture texBullet;

sf::Sound sndGun;
bool globalSound;

std::vector<GameObject*> gameObjects;

sf::RenderWindow* windowPtr;

sf::Vector2f getMousePosition()
{
	return windowPtr->mapPixelToCoords(sf::Mouse::getPosition(*windowPtr));
}

bool checkLineOfSight(GameObject* a, GameObject* b) //Should this be defined under GameObject.h?
{

	sf::Vector2i pointsA[5];
	sf::Vector2i pointsB[5];

	//Assign the points values
	pointsA[0] = sf::Vector2i(a->x, a->y);
	pointsA[1] = sf::Vector2i(a->x + a->w, a->y);
	pointsA[2] = sf::Vector2i(a->x + a->w, a->y + a->h);
	pointsA[3] = sf::Vector2i(a->x, a->y + a->h);
	pointsA[4] = sf::Vector2i(a->x + a->originX, a->y + a->originY);

	pointsB[0] = sf::Vector2i(b->x, b->y);
	pointsB[1] = sf::Vector2i(b->x + b->w, b->y);
	pointsB[2] = sf::Vector2i(b->x + b->w, b->y + b->h);
	pointsB[3] = sf::Vector2i(b->x, b->y + b->h);
	pointsB[4] = sf::Vector2i(b->x + b->originX, b->y + b->originY);


	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			sf::Vector2f pos(pointsA[i]);
			sf::Vector2f vec(pointsB[j].x - pos.x, pointsB[j].y - pos.y);
			float length = sqrt((vec.x * vec.x) + (vec.y * vec.y));
			sf::Vector2f direction(vec / length);

			while (true)
			{
				GameObject* col = GameObject::collisionPoint(pos.x, pos.y);
				if (col != nullptr && col != a)
				{
					if (col == b)
					{
						return true;
					}
					if (col->objectID == WALL_ID)
					{
						break;
					}
				}
				pos += direction;
			}
		}
	}
	return false;
}