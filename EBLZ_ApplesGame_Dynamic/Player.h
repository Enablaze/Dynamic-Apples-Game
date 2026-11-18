#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"
#include "Constants.h"

namespace DynamicApplesGame
{
	enum class PlayerDirections
	{
		Up = 0,
		Right = 1,
		Down = 2,
		Left = 3
	};

	struct Player
	{
		Position2D position;
		PlayerDirections moveDirection = PlayerDirections::Up;
		float speed = INITIAL_SPEED;
		sf::Sprite sprite;
	};

	Vector2D GetDirectionVector(PlayerDirections direction);

	void InitPlayer(Player& player, const sf::Texture& texture);

	void SetPlayerDirection(Player& player, PlayerDirections direction);

	void MovePlayer(Player& player, float deltaTime);

	void IncreasePlayerSpeed(Player& player);

	void DrawPlayer(Player& player, sf::RenderWindow& window);

	void RestartPlayer(Player& player);
}