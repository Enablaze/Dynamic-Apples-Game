#include "Apple.h"
#include "Constants.h"
#include "SpriteUtils.h"

namespace DynamicApplesGame
{
	void InitApple(Apple& apple, const sf::Texture& texture)
	{
		apple.sprite.setTexture(texture);
		SetSpriteSize(apple.sprite, APPLE_SIZE, APPLE_SIZE);
		SetSpriteRelativeOrigin(apple.sprite, 0.5f, 0.5f);
	}

	void DrawApple(Apple& apple, sf::RenderWindow& window)
	{
		apple.sprite.setPosition(apple.position.x, apple.position.y);
		window.draw(apple.sprite);
	}

	void RestartApple(Apple& apple)
	{
		apple.position = GetRandomPositionInRect(APPLE_SIZE, { FIELD_LEFT, FIELD_TOP }, { FIELD_WIDTH, FIELD_HEIGHT });
		apple.isEaten = false;
	}
}