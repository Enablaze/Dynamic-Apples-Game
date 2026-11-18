#include <SFML/Graphics.hpp>
#include <ctime>
#include <cstdlib>
#include "Constants.h"
#include "Game.h"

int main()
{
	using namespace DynamicApplesGame;

	int seed = (int)time(nullptr);
	srand(seed);

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Dynamic Apples Game");

	Game game;
	InitGame(game);

	sf::Clock gameClock;
	float lastTime = gameClock.getElapsedTime().asSeconds();

	window.setKeyRepeatEnabled(false);
	window.setFramerateLimit(WINDOW_FPS);

	while (window.isOpen())
	{
		float currentTime = gameClock.getElapsedTime().asSeconds();
		float deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			HandleGameEvent(game, event);
		}

		if (game.exitRequested)
			window.close();

		UpdateGame(game, deltaTime);

		DrawGame(game, window);
	}

	DeinitGame(game);

	return 0;
}