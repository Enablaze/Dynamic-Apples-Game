#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"
#include "Player.h" // Directions

namespace DynamicApplesGame
{
	struct Projectile
	{
		Position2D position;
		PlayerDirections direction = PlayerDirections::Up;
		float speed = 0.f;
		bool isActive = false;
		sf::Sprite sprite;
	};

	void InitProjectile(Projectile& projectile, const sf::Texture& texture);

	void UpdateProjectile(Projectile& projectile, float deltaTime);

	void LaunchProjectile(Projectile& projectile, Position2D position, PlayerDirections direction, float speed);

	void DeactivateProjectile(Projectile& projectile);

	bool IsProjectileOutOfField(const Projectile& projectile);

	void DrawProjectile(Projectile& projectile, sf::RenderWindow& window);
}