#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Resources.h"
#include "Player.h"
#include "Apple.h"
#include "Stone.h"
#include "Projectile.h"
#include "UI.h"

namespace DynamicApplesGame
{
	enum class GameState
	{
		Playing,
		GameOver,
		Menu,
		ModeSelect
	};

	struct Game
	{
		Resources resources;
		UI ui;

		GameState state = GameState::Playing;
		Player player;
		Apple* apples = nullptr; // apples in heap, num is know at start. InitGame - DeinitGame.
		int numApples = 0;
		Stone stones[NUM_STONES];
		Projectile projectiles[MAX_PROJECTILES];
		MenuItems menuItemSelection = MenuItems::ResumeGame;
		unsigned int gameModeMask = DEFAULT_GAME_MODE;
		unsigned int pendingModeMask = DEFAULT_GAME_MODE;
		int modeMenuSelection = MODE_MENU_START_INDEX;


		float throwCooldownLeft = 0.f;
		float untilRestartTimeLeft = 0.f;
		int numEatenApples = 0;
		int numProjectilesToThrow = 0;
		bool isGameLive = false;
		bool exitRequested = false;
	};

	void HandleGameEvent(Game& game, const sf::Event& event);

	void StartNewRound(Game& game);

	void InitGame(Game& game);

	bool IsPlayerCollideWithWallOrActor(Game& game);

	void UpdateGame(Game& game, float deltaTime);

	void DrawGame(Game& game, sf::RenderWindow& window);

	void DeinitGame(Game&);
}