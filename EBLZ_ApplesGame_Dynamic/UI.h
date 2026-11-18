#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"

namespace DynamicApplesGame
{
	enum class MenuItems
	{
		ResumeGame = 0,
		NewGame = 1,
		QuitGame = 2
	};

	const int NUM_MENU_ITEMS = 3;
	const int MODE_MENU_START_INDEX = NUM_MODE_OPTIONS;
	const int MODE_MENU_BACK_INDEX = NUM_MODE_OPTIONS + 1;
	const int NUM_MODE_MENU_ITEMS = NUM_MODE_OPTIONS + 2;

	struct UI
	{
		sf::RectangleShape hudShape;
		sf::RectangleShape fieldShape;
		sf::RectangleShape overlayShape;
		sf::Text scoreText;
		sf::Text numProjectilesText;
		sf::Text gameOverText;
		sf::Text menuHintText;
		sf::Text menuItemTexts[NUM_MENU_ITEMS];
		sf::Text modeMenuTexts[NUM_MODE_MENU_ITEMS];
	};

	void UpdateMenuItems(UI& ui, bool isResumeAvailable, MenuItems selectedItem);

	void InitUI(UI& ui, const sf::Font& font);

	void UpdateHUD(UI& ui, int score, int numProjectiles);

	void DrawBackground(const UI& ui, sf::RenderWindow& window);

	void UpdateMenuOverlay(UI& ui, bool isSceneVisible);

	void DrawOverlay(const UI& ui, sf::RenderWindow& window);

	void DrawGameOver(const UI& ui, sf::RenderWindow& window);

	void DrawMenu(const UI& ui, sf::RenderWindow& window);

	void UpdateGameOverFade(UI& ui, float alphaProgress);

	void DrawHUD(const UI& ui, sf::RenderWindow& window);

	void UpdateModeMenu(UI& ui, unsigned int modeMask, int selectedIndex);

	void DrawModeMenu(const UI& ui, sf::RenderWindow& window);
}