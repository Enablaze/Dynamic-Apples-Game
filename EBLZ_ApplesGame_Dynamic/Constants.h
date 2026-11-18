#pragma once
#include <string>

namespace DynamicApplesGame
{
	const std::string RESOURCES_PATH = "Resources/";
	const std::string TEXTURES_PATH = RESOURCES_PATH + "Textures/";
	const std::string SOUNDS_PATH = RESOURCES_PATH + "Sounds/";
	const std::string FONTS_PATH = RESOURCES_PATH + "Fonts/";

	// Window layout:
	const int WINDOW_FPS = 60;

	const int HUD_HEIGHT = 50;

	const float FIELD_WIDTH = 800.f;
	const float FIELD_HEIGHT = 600.f;
	const float FIELD_LEFT = 0.f;
	const float FIELD_TOP = HUD_HEIGHT;

	const int WINDOW_WIDTH = static_cast<int>(FIELD_WIDTH);
	const int WINDOW_HEIGHT = static_cast<int>(FIELD_TOP + FIELD_HEIGHT);

	// Player settings:
	const float INITIAL_SPEED = 100.0f;
	const float SPEED_PER_APPLE = 15.0f;
	const float MAX_SPEED = 400.f;
	const float PLAYER_SIZE = 20.0f;
	const float HALF_PLAYER = PLAYER_SIZE / 2.f;

	// Apple settings:
	const int NUM_APPLES = 10;
	const float APPLE_SIZE = 20.0f;
	const float HALF_APPLE = APPLE_SIZE / 2.f;

	// Stones settings:
	const int NUM_STONES = 4;
	const float STONE_SIZE = 30.f;
	const float STONE_SAFE_RADIUS = 150.f;
	const int STONE_MAX_SPAWN_ATTEMPTS = 20;

	// Game over settings:
	const float GAME_OVER_STOP_TIME = 4.f;

	// Projectiles settings:
	const int MAX_PROJECTILES = 8;
	const int PROJECTILES_LIMIT = 10;
	const float THROW_COOLDOWN = 0.25f;
	const float PROJECTILE_SPEED_MULT = 2.f;

	// volume settings:
	const float EAT_VOLUME = 35.f;
	const float DEATH_VOLUME = 25.f;
	const float THROW_VOLUME = 25.f;
}