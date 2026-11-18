#include "Player.h"
#include "SpriteUtils.h"
#include <cmath>

namespace DynamicApplesGame
{
	Vector2D GetDirectionVector(PlayerDirections direction)
	{
		switch (direction)
		{
		case PlayerDirections::Up:		return { 0.f, -1.f };
		case PlayerDirections::Right:	return { 1.f, 0.f };
		case PlayerDirections::Down:	return { 0.f, 1.f };
		case PlayerDirections::Left:	return { -1.f, 0.f };
		}
		return { 0.f, 0.f };
	}

	float GetDirectionAngle(PlayerDirections direction)
	{
		switch (direction)
		{
		case PlayerDirections::Up:		return -90.f;
		case PlayerDirections::Right:	return 0.f;
		case PlayerDirections::Down:	return 90.f;
		case PlayerDirections::Left:	return 0.f;
		}
		return 0.f;
	}

	void InitPlayer(Player& player, const sf::Texture& texture)
	{
		player.sprite.setTexture(texture);
		SetSpriteSize(player.sprite, PLAYER_SIZE, PLAYER_SIZE);
		SetSpriteRelativeOrigin(player.sprite, 0.5f, 0.5f);
	}

	void SetPlayerDirection(Player& player, PlayerDirections direction)
	{
		player.moveDirection = direction;
		
		sf::Vector2f currentScale = player.sprite.getScale();

		if (player.moveDirection == PlayerDirections::Left)
		{
			player.sprite.setScale(-std::abs(currentScale.x), std::abs(currentScale.y));
		}
		else
		{
			player.sprite.setScale(std::abs(currentScale.x), std::abs(currentScale.y));
		}

		player.sprite.setRotation(GetDirectionAngle(direction));
	}

	void MovePlayer(Player& player, float deltaTime)
	{
		const Vector2D direction = GetDirectionVector(player.moveDirection);
		player.position.x += direction.x * player.speed * deltaTime;
		player.position.y += direction.y * player.speed * deltaTime;
	}

	void IncreasePlayerSpeed(Player& player)
	{
		player.speed += SPEED_PER_APPLE;

		if (player.speed > MAX_SPEED)
		{
			player.speed = MAX_SPEED;
		}
	}

	void DrawPlayer(Player& player, sf::RenderWindow& window)
	{
		player.sprite.setPosition(player.position.x, player.position.y);
		window.draw(player.sprite);
	}

	void RestartPlayer(Player& player)
	{
		player.position = { FIELD_LEFT + (FIELD_WIDTH / 2.0f), FIELD_TOP + (FIELD_HEIGHT / 2.0f) };
		player.speed = INITIAL_SPEED;
		SetPlayerDirection(player, PlayerDirections::Up);
	}
}