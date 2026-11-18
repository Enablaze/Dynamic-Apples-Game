#pragma once
#include <SFML/Graphics.hpp>

namespace DynamicApplesGame
{
	void SetSpriteSize(sf::Sprite& sprite, float desiredWidth, float desiredHeight);

	void SetSpriteRelativeOrigin(sf::Sprite& sprite, float originX, float originY);
}