#include "Projectile.h"
#include "Constants.h"
#include "SpriteUtils.h"

namespace DynamicApplesGame
{
	void InitProjectile(Projectile& projectile, const sf::Texture& texture)
	{
		projectile.sprite.setTexture(texture);
		SetSpriteSize(projectile.sprite, APPLE_SIZE, APPLE_SIZE);
		SetSpriteRelativeOrigin(projectile.sprite, 0.5f, 0.5f);
	}

	void UpdateProjectile(Projectile& projectile, float deltaTime)
	{
		const Vector2D direction = GetDirectionVector(projectile.direction);
		projectile.position.x += direction.x * projectile.speed * deltaTime;
		projectile.position.y += direction.y * projectile.speed * deltaTime;
	}

	void LaunchProjectile(Projectile& projectile, Position2D position, PlayerDirections direction, float speed)
	{
		projectile.position = position;
		projectile.direction = direction;
		projectile.speed = speed;
		projectile.isActive = true;
	}
	
	void DeactivateProjectile(Projectile& projectile)
	{
		projectile.isActive = false;
	}

	bool IsProjectileOutOfField(const Projectile& projectile)
	{
		return projectile.position.x - HALF_APPLE < FIELD_LEFT ||
			   projectile.position.x + HALF_APPLE > (FIELD_LEFT + FIELD_WIDTH) ||
			   projectile.position.y - HALF_APPLE < FIELD_TOP ||
			   projectile.position.y + HALF_APPLE > (FIELD_TOP + FIELD_HEIGHT);
	}

	void DrawProjectile(Projectile& projectile, sf::RenderWindow& window)
	{
		projectile.sprite.setPosition(projectile.position.x, projectile.position.y);
		window.draw(projectile.sprite);
	}
}