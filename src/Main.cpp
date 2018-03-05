#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string.h>
#include "Wall.h"
#include "NPC.h"
#include "Player.h"
#include "Global.h"

int main(int argc, char* argv[])
{
	if (argc == 2 && strcmp(argv[1], "--mute") == 0)
	{
		globalSound = false;
	}
	else
	{
		globalSound = true;
	}
	const sf::VideoMode vm = sf::VideoMode::getDesktopMode();
	const int resolutionX = vm.width;
	const int resolutionY = vm.height;
	sf::RenderWindow window(sf::VideoMode(resolutionX, resolutionY), "Top Down Shooter"/*, sf::Style::Fullscreen*/);
	
	windowPtr = &window;

	window.setFramerateLimit(60);
	window.setMouseCursorVisible(false);

	//Load Resources
	sf::Texture texCursor;
	texCursor.loadFromFile("res/Cursor.tga");

	texPlayer.loadFromFile("res/Player3.tga");
	
	sf::SoundBuffer sndbufGun;
	sndbufGun.loadFromFile("res/Gun.wav");
	sndGun.setBuffer(sndbufGun);

	sf::Sprite cursor(texCursor);

	cursor.setOrigin(16.0f, 16.0f); //Probably starts at 0 so I should do 15, 15

	int roomWidth = 2560;
	int roomHeight = 1080;

	bool usingViews = true;

	if (roomWidth <= resolutionX && roomHeight <= resolutionY)
	{
		usingViews = false;
	}
	//Setup Views
	sf::View view(sf::FloatRect(0, 0, resolutionX, resolutionY));

	//Create GameObjects
	gameObjects.push_back(new Wall(0, 0, 32, 1080));
	gameObjects.push_back(new Wall(32, 0, 2528, 32));
	gameObjects.push_back(new Wall(2528, 32, 32, 1048));
	gameObjects.push_back(new Wall(32, 1048, 2528, 32));

	gameObjects.push_back(new Wall(1280, 256, 32, 512));
	gameObjects.push_back(new Wall(1360, 256, 32, 512));

	gameObjects.push_back(new NPC(512, 512));
	gameObjects.push_back(new NPC(1024, 512));
	gameObjects.push_back(new NPC(512, 1024));

	GameObject* player = new Player(1400, 628);
	gameObjects.push_back(player);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
					window.close();
					break;
			}
		}

		window.setView(view);

		if (usingViews)
		{
			view.setCenter(player->x + (player->w / 2), player->y + (player->h / 2));
		}

		window.clear(sf::Color(127, 0, 0));

		for (int i = 0; i < gameObjects.size(); i++)
		{
			switch (gameObjects[i]->objectID)
			{
				case PLAYER_ID:
					static_cast<Player*>(gameObjects[i])->update();
					break;
				case NPC_ID:
					static_cast<NPC*>(gameObjects[i])->update(player);
					sf::Text text;
					sf::Font font;
					if (!font.loadFromFile("res/arial.ttf"))
					{
					    std::cout << "Can't Open Font" << std::endl;
					}
					text.setFont(font);
					text.setString(std::to_string(static_cast<NPC*>(gameObjects[i])->pathPosition));
					text.setCharacterSize(12);
					text.setFillColor(sf::Color::Blue);
					text.setStyle(sf::Text::Bold | sf::Text::Underlined);
					window.draw(text);
					break;
			}
			window.draw(gameObjects[i]->sprite);
		}

		window.setView(window.getDefaultView());
		cursor.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
		window.draw(cursor);
		window.display();
		player->sprite.setTextureRect(sf::IntRect(0, 0, 68, 48));
	}
	return 0;
}
