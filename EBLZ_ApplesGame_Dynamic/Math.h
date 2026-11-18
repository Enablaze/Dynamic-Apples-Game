#pragma once

namespace DynamicApplesGame
{
	struct Vector2D
	{
		float x = 0.f;
		float y = 0.f;
	};

	// Actors spawn positions
	typedef Vector2D Position2D;

	Position2D GetRandomPositionInRect(float objectSize, Position2D rectTopLeft, Vector2D rectSize);

	bool IsCirclesCollide(Position2D firstPosition, float firstRadius,
		Position2D secondPosition, float secondRadius);

	bool IsRectanglesCollide(Position2D firstPosition, Vector2D firstSize,
		Position2D secondPosition, Vector2D secondSize);

	bool IsCircleRectangleCollide(Position2D firstPosition, float firstRadius,
		Position2D secondPosition, Vector2D secondSize);
}