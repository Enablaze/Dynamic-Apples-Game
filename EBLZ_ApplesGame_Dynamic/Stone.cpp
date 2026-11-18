#include "Stone.h"
#include "Constants.h"
#include "SpriteUtils.h"

namespace DynamicApplesGame
{
	void InitStone(Stone& stone, const sf::Texture& texture)
	{
		stone.size = { STONE_SIZE, STONE_SIZE };
		stone.sprite.setTexture(texture);
		SetSpriteSize(stone.sprite, stone.size.x, stone.size.y);
		SetSpriteRelativeOrigin(stone.sprite, 0.5f, 0.5f);

	}

	void DrawStone(Stone& stone, sf::RenderWindow& window)
	{
		stone.sprite.setPosition(stone.position.x, stone.position.y);
		window.draw(stone.sprite);
	}
	
	void RestartStone(Stone& stone, const Position2D& playerPosition)
	{
		for (int i = 0; i < STONE_MAX_SPAWN_ATTEMPTS; ++i)
		{
			stone.position = GetRandomPositionInRect(stone.size.x, { FIELD_LEFT, FIELD_TOP }, { FIELD_WIDTH, FIELD_HEIGHT });

			if (!IsCirclesCollide(stone.position, 0.f, playerPosition, STONE_SAFE_RADIUS))
			{
				return;
			}
		}
		
	}
}