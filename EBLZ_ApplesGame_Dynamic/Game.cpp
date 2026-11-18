#include "Game.h"
#include "Math.h"

namespace DynamicApplesGame
{
	bool IsModeOn(unsigned int modeMask, unsigned int modeBit)
	{
		return (modeMask & modeBit) != 0;
	}

	void MoveMenuSelection(Game& game, int direction)
	{
		int newSelection = static_cast<int>(game.menuItemSelection) + direction;
		
		if (direction == -1 && newSelection == 0)
		{
			if (!game.isGameLive)
			{
				newSelection = NUM_MENU_ITEMS - 1;
			}
		}
		else if (direction == -1 && newSelection < 0)
		{
			newSelection = NUM_MENU_ITEMS - 1;
		}
		else if (direction == 1 && newSelection == NUM_MENU_ITEMS)
		{
			newSelection = 0;
			if (!game.isGameLive)
			{
				newSelection += 1;
			}
		}

		game.menuItemSelection = static_cast<MenuItems>(newSelection);
	}

	void HandlePlayerInput(Game& game)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			SetPlayerDirection(game.player, PlayerDirections::Up);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			SetPlayerDirection(game.player, PlayerDirections::Right);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			SetPlayerDirection(game.player, PlayerDirections::Down);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			SetPlayerDirection(game.player, PlayerDirections::Left);
		}
	}

	void StartNewRound(Game& game)
	{
		RestartPlayer(game.player);

		for (int i = 0; i < game.numApples; ++i)
		{
			RestartApple(game.apples[i]);
		}

		for (int i = 0; i < NUM_STONES; ++i)
		{
			RestartStone(game.stones[i], game.player.position);
		}

		for (int i = 0; i < MAX_PROJECTILES; ++i)
		{
			DeactivateProjectile(game.projectiles[i]);
		}

		game.throwCooldownLeft = 0.f;
		game.numEatenApples = 0;
		game.numProjectilesToThrow = 0;
		game.state = GameState::Playing;
		game.isGameLive = true;
	}

	void EnterMenu(Game& game)
	{
		if (game.isGameLive)
		{
			game.menuItemSelection = MenuItems::ResumeGame;
		}
		else
		{
			game.menuItemSelection = MenuItems::NewGame;
		}
		game.state = GameState::Menu;
	}

	void InitGame(Game& game)
	{
		LoadResources(game.resources);

		InitUI(game.ui, game.resources.uiFont);

		InitPlayer(game.player, game.resources.playerTexture);

		if (IsModeOn(game.gameModeMask, MODE_RANDOM_APPLES))		// first check priority
		{
			game.numApples = MIN_APPLES + (rand() % (MAX_APPLES - MIN_APPLES + 1));
		}
		else if (IsModeOn(game.gameModeMask, MODE_MANY_APPLES))
		{
			game.numApples = NUM_APPLES_LARGE;
		}
		else
		{
			game.numApples = NUM_APPLES_SMALL;
		}
		game.apples = new Apple[game.numApples];

		for (int i = 0; i < game.numApples; ++i)
		{
			InitApple(game.apples[i], game.resources.appleTexture);
		}

		for (int i = 0; i < NUM_STONES; ++i)
		{
			InitStone(game.stones[i], game.resources.stoneTexture);
		}

		for (int i = 0; i < MAX_PROJECTILES; ++i)
		{
			InitProjectile(game.projectiles[i], game.resources.appleTexture);
		}

		StartNewRound(game);

		game.isGameLive = false;
		EnterMenu(game);
	}

	void HandleGameEvent(Game& game, const sf::Event& event)
	{
		if (event.type != sf::Event::KeyPressed)
		{
			return;
		}

		switch (game.state)
		{
		case GameState::Playing:
			if (event.key.code == sf::Keyboard::Escape)
			{
				EnterMenu(game);
			}
			break;

		case GameState::Menu:
			if (event.key.code == sf::Keyboard::Escape && game.isGameLive)
			{
				game.state = GameState::Playing;
			}
			else if (event.key.code == sf::Keyboard::Enter)
			{
				switch (game.menuItemSelection)
				{
				case MenuItems::ResumeGame:
					game.state = GameState::Playing;
					break;
				case MenuItems::NewGame:
					StartNewRound(game);
					break;
				case MenuItems::QuitGame:
					game.exitRequested = true;
					break;
				}
			}
			else if (event.key.code == sf::Keyboard::Up)
			{
				MoveMenuSelection(game, -1);
			}
			else if (event.key.code == sf::Keyboard::Down)
			{
				MoveMenuSelection(game, 1);
			}
			break;

		case GameState::GameOver:
			// Keys are ignored until fade ends.
			break;
		}
	}

	bool IsPlayerCollideWithWallOrActor(Game& game)
	{
		// Check for player collisions with stones.
		for (int i = 0; i < NUM_STONES; ++i)
		{
			if (IsCircleRectangleCollide(game.player.position, HALF_PLAYER, game.stones[i].position, game.stones[i].size))
			{
				return true;
			}
		}

		// Check for player collisions with walls.
		if (game.player.position.x - HALF_PLAYER < FIELD_LEFT ||
			game.player.position.x + HALF_PLAYER > (FIELD_LEFT + FIELD_WIDTH) ||
			game.player.position.y - HALF_PLAYER < FIELD_TOP ||
			game.player.position.y + HALF_PLAYER > (FIELD_TOP + FIELD_HEIGHT))
		{
			return true;
		}
		return false;
	}

	void TryThrowApple(Game& game)
	{
		if (game.numProjectilesToThrow <= 0 || game.throwCooldownLeft > 0.f)
		{
			return;
		}

		for (int i = 0; i < MAX_PROJECTILES; ++i)
		{
			Projectile& projectile = game.projectiles[i];
			if (projectile.isActive)
			{
				continue;
			}

			const Vector2D direction = GetDirectionVector(game.player.moveDirection);
			const float spawnOffset = HALF_PLAYER + HALF_APPLE;

			const Position2D spawnPosition =
			{
				game.player.position.x + direction.x * spawnOffset,
				game.player.position.y + direction.y * spawnOffset

			};

			LaunchProjectile(projectile, spawnPosition, game.player.moveDirection, 
							 game.player.speed * PROJECTILE_SPEED_MULT);

			--game.numProjectilesToThrow;
			game.throwCooldownLeft = THROW_COOLDOWN;
			game.resources.throwSound.play();
			return;
		}
	}

	void EndRound(Game& game)
	{
		game.state = GameState::GameOver;
		game.isGameLive = false;
		game.untilRestartTimeLeft = GAME_OVER_STOP_TIME;
		UpdateGameOverFade(game.ui, 0.f);
	}

	void UpdatePlayingState(Game& game, float deltaTime)
	{
		// Player input movement.
		HandlePlayerInput(game);

		MovePlayer(game.player, deltaTime);

		if (game.throwCooldownLeft > 0.f)
		{
			game.throwCooldownLeft -= deltaTime;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			TryThrowApple(game);
		}

		for (int i = 0; i < MAX_PROJECTILES; ++i)
		{
			if (game.projectiles[i].isActive)
			{
				UpdateProjectile(game.projectiles[i], deltaTime);
			}
		}

		if (IsPlayerCollideWithWallOrActor(game))
		{
			EndRound(game);
			game.resources.deathSound.play();
			return;
		}

		// Eat apples, score, speed, respawn, stones
		for (int i = 0; i < game.numApples; ++i)
		{
			Apple& apple = game.apples[i];
			if (apple.isEaten)
			{
				continue; // finite mode
			}

			if (IsCirclesCollide(game.player.position, HALF_PLAYER, apple.position, HALF_APPLE))
			{
				++game.numEatenApples;

				if (game.numProjectilesToThrow < PROJECTILES_LIMIT)
				{
					++game.numProjectilesToThrow;
				}

				game.resources.eatSound.play();

				if (IsModeOn(game.gameModeMask, MODE_ACCELERATION))
				{
					IncreasePlayerSpeed(game.player);
				}

				if (IsModeOn(game.gameModeMask, MODE_FINITE_APPLES))
				{
					apple.isEaten = true;
				}
				else
				{
					RestartApple(apple);
				}
			}
		}

		if (IsModeOn(game.gameModeMask, MODE_FINITE_APPLES) && game.numEatenApples >= game.numApples)
		{
			EndRound(game);
			return;
		}

		for (int i = 0; i < MAX_PROJECTILES; ++i)
		{
			Projectile& projectile = game.projectiles[i];
			if (!projectile.isActive)
			{
				continue;
			}

			if (IsProjectileOutOfField(projectile))
			{
				DeactivateProjectile(projectile);
				continue;
			}

			for (int j = 0; j < NUM_STONES; ++j)
			{
				if (IsCircleRectangleCollide(projectile.position, HALF_APPLE, game.stones[j].position, game.stones[j].size))
				{
					DeactivateProjectile(projectile);
					RestartStone(game.stones[j], game.player.position);
					break;
				}
			}
		}
	}

	void UpdateGameOverState(Game& game, float deltaTime)
	{
		game.untilRestartTimeLeft -= deltaTime;

		const float ratioOfLeftTime = game.untilRestartTimeLeft / GAME_OVER_STOP_TIME;
		const float alphaBlackProgress = 1.f - ratioOfLeftTime;

		UpdateGameOverFade(game.ui, alphaBlackProgress);

		if (game.untilRestartTimeLeft <= 0.f)
		{
			EnterMenu(game);
		}
	}

	void UpdateGame(Game& game, float deltaTime)
	{
		switch (game.state)
		{
		case GameState::Playing:

			UpdatePlayingState(game, deltaTime);
			break;

		case GameState::GameOver:

			UpdateGameOverState(game, deltaTime);
			break;
			
		case GameState::Menu:

			UpdateMenuOverlay(game.ui, game.isGameLive);
			UpdateMenuItems(game.ui, game.isGameLive, game.menuItemSelection);
			break;
		}

		UpdateHUD(game.ui, game.numEatenApples, game.numProjectilesToThrow);
	}

	void DrawGame(Game& game, sf::RenderWindow& window)
	{
		// Update window.
		window.clear();

		DrawBackground(game.ui, window);

		// Draw apples
		for (int i = 0; i < game.numApples; ++i)
		{
			if (!game.apples[i].isEaten) // finite mode
			{
				DrawApple(game.apples[i], window);
			}
		}

		// Draw stones
		for (int i = 0; i < NUM_STONES; ++i)
		{
			DrawStone(game.stones[i], window);
		}

		// Draw projectiles
		for (int i = 0; i < MAX_PROJECTILES; ++i)
		{
			if (game.projectiles[i].isActive)
			{
				DrawProjectile(game.projectiles[i], window);
			}
		}

		DrawPlayer(game.player, window);

		DrawHUD(game.ui, window);

		if (game.state != GameState::Playing)
		{
			DrawOverlay(game.ui, window);
		}

		if (game.state == GameState::GameOver)
		{
			DrawGameOver(game.ui, window);
		}

		if (game.state == GameState::Menu)
		{
			DrawMenu(game.ui, window);
		}

		window.display();
	}

	void DeinitGame(Game& game)
	{
		delete[] game.apples;
		game.apples = nullptr;
		game.numApples = 0;
	}
}