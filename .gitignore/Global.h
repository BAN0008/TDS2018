#ifndef GLOBAL_H
#define GLOBAL_H

#define PLAYER_ID 0
#define NPC_ID 1
#define WALL_ID 2

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio/Sound.hpp>
#include "GameObject.h"

extern sf::Texture texPlayer;
extern sf::Sound sndGun;
extern bool globalSound;

extern sf::RenderWindow* windowPtr;

sf::Vector2f getMousePosition();
bool checkLineOfSight(GameObject* a, GameObject* b);
template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

extern std::vector<GameObject*> gameObjects;

#endif
