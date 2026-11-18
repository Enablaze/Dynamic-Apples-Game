#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"

namespace DynamicApplesGame
{
	struct Apple
	{
		Position2D position;
		sf::Sprite sprite;
		bool isEaten = false; // finite mode only.
	};

	void InitApple(Apple& apple, const sf::Texture& texture);

	void DrawApple(Apple& apple, sf::RenderWindow& window);

	void RestartApple(Apple& apple);
}