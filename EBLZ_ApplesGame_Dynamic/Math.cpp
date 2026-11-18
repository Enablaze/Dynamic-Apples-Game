#include "Math.h"
#include <cstdlib>
#include <algorithm>

namespace DynamicApplesGame
{
	Position2D GetRandomPositionInRect(float objectSize, Position2D rectTopLeft, Vector2D rectSize)
	{
		const float halfSize = objectSize / 2.f;

		Position2D result;
		result.x = rectTopLeft.x + halfSize + rand() / (float)RAND_MAX * (rectSize.x - objectSize);
		result.y = rectTopLeft.y + halfSize + rand() / (float)RAND_MAX * (rectSize.y - objectSize);

		return result;
	}

	bool IsCirclesCollide(Position2D firstPosition, float firstRadius, Position2D secondPosition, float secondRadius)
	{
		float dx = firstPosition.x - secondPosition.x;
		float dy = firstPosition.y - secondPosition.y;

		float squareDistance = dx * dx + dy * dy;
		float radiusSum = firstRadius + secondRadius;

		return squareDistance <= radiusSum * radiusSum;
	}

	bool IsRectanglesCollide(Position2D firstPosition, Vector2D firstSize, Position2D secondPosition, Vector2D secondSize)
	{
		float firstTop = firstPosition.y - firstSize.y / 2.f;
		float firstRight = firstPosition.x + firstSize.x / 2.f;
		float firstBottom = firstPosition.y + firstSize.y / 2.f;
		float firstLeft = firstPosition.x - firstSize.x / 2.f;

		float secondTop = secondPosition.y - secondSize.y / 2.f;
		float secondRight = secondPosition.x + secondSize.x / 2.f;
		float secondBottom = secondPosition.y + secondSize.y / 2.f;
		float secondLeft = secondPosition.x - secondSize.x / 2.f;

		return firstLeft < secondRight && firstRight > secondLeft &&
			firstTop < secondBottom && firstBottom > secondTop;
	}

	bool IsCircleRectangleCollide(Position2D firstPosition, float firstRadius, Position2D secondPosition, Vector2D secondSize)
	{
		float rectTop = secondPosition.y - secondSize.y / 2.f;
		float rectRight = secondPosition.x + secondSize.x / 2.f;
		float rectBottom = secondPosition.y + secondSize.y / 2.f;
		float rectLeft = secondPosition.x - secondSize.x / 2.f;

		float closestX = std::max(rectLeft, std::min(firstPosition.x, rectRight));
		float closestY = std::max(rectTop, std::min(firstPosition.y, rectBottom));

		float dx = firstPosition.x - closestX;
		float dy = firstPosition.y - closestY;

		return dx * dx + dy * dy <= firstRadius * firstRadius;
	}
}