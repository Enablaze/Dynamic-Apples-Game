#pragma once
#include <SFML/Graphics.hpp>

namespace DynamicApplesGame
{
	enum class MenuItems
	{
		ResumeGame = 0,
		NewGame = 1,
		QuitGame = 2
	};

	const int NUM_MENU_ITEMS = 3;

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
}