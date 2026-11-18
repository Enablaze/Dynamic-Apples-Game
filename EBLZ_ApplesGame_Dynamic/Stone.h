#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"

namespace DynamicApplesGame
{
	struct Stone
	{
		Position2D position;
		Vector2D size;
		sf::Sprite sprite;
	};

	void InitStone(Stone& stone, const sf::Texture& texture);

	void DrawStone(Stone& stone, sf::RenderWindow& window);

	void RestartStone(Stone& stone, const Position2D& playerPosition);
}