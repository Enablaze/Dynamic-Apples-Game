#include "UI.h"
#include "Constants.h"
#include <string>

namespace DynamicApplesGame
{
	const sf::Color HUD_COLOR(20, 20, 20);
	const sf::Color FIELD_COLOR(35, 50, 35);
	const sf::Color FIELD_OUTLINE_COLOR(90, 120, 90);
	const sf::Color MENU_BG_COLOR(0, 0, 0, 255);
	const sf::Uint8 PAUSE_OVERLAY_ALPHA = 175;

	const float FIELD_OUTLINE_THICKNESS = -2.f;
	const unsigned int HUD_FONT_SIZE = 14;
	const unsigned int GAME_OVER_FONT_SIZE = 50;
	const float HUD_TEXT_LEFT = 10.f;
	const float HUD_TEXT_TOP = 6.f;
	const float HUD_LINE_HEIGHT = 20.f;
	const unsigned int MENU_FONT_SIZE = 28;

	const float MENU_TEXT_LEFT = 60.f;
	const float MENU_TEXT_TOP = 100.f;
	const float MENU_LINE_HEIGHT = 50.f;
	const char* const MENU_ITEM_STRINGS[NUM_MENU_ITEMS] = { "Continue", "New game", "Exit" };

	const char* const MODE_OPTION_STRINGS[NUM_MODE_OPTIONS] = { "Acceleration", "Finite apples", "50 apples", "Random count" };
	const char* const MODE_MENU_START_STRING = "Start";
	const char* const MODE_MENU_BACK_STRING = "Back";


	const unsigned int MENU_HINT_FONT_SIZE = 18;
	const float MENU_HINT_RIGHT_MARGIN = 60.f;
	const sf::Color MENU_HINT_COLOR(150, 150, 150);
	const sf::Color MENU_ITEM_COLOR(255, 255, 255);
	const sf::Color MENU_ACTIVE_ITEM_COLOR(255, 255, 0);
	const sf::Color MENU_BLOCKED_ITEM_COLOR(100, 100, 100);
	const char* const MENU_HINT_STRING =
		"Game Controls\n"
		"\n"
		"In Game:\n"
		"WASD / Arrows - Move\n"
		"Space - throw an apple\n"
		"Esc - Pause\n"
		"\n"
		"\n"
		"In Menu:\n"
		"Up / Down - Choose\n"
		"Enter - Select\n"
		"1-4 - Toggle mode\n"
		"Esc - Back";


	void SetupText(sf::Text& text, const sf::Font& font, unsigned int size, const sf::Color& color, const sf::Vector2f& position)
	{
		text.setFont(font);
		text.setCharacterSize(size);
		text.setFillColor(color);
		text.setPosition(position);
	}

	void UpdateMenuItems(UI& ui, bool isResumeAvailable, MenuItems selectedItem)
	{
		for (int i = 0; i < NUM_MENU_ITEMS; ++i)
		{
			if (selectedItem == static_cast<MenuItems>(i))
			{
				ui.menuItemTexts[i].setFillColor(MENU_ACTIVE_ITEM_COLOR);
			}
			else if (MenuItems::ResumeGame == static_cast<MenuItems>(i) && !isResumeAvailable)
			{
				ui.menuItemTexts[i].setFillColor(MENU_BLOCKED_ITEM_COLOR);
			}
			else
			{
				ui.menuItemTexts[i].setFillColor(MENU_ITEM_COLOR);
			}
		}
	}

	void UpdateHUD(UI& ui, int score, int numProjectiles)
	{
		ui.scoreText.setString("Score: " + std::to_string(score));
		ui.numProjectilesText.setString("Projectiles: " + std::to_string(numProjectiles));
	}

	void InitUI(UI& ui, const sf::Font& font)
	{
		SetupText(ui.scoreText, font, HUD_FONT_SIZE, sf::Color::White, { HUD_TEXT_LEFT, HUD_TEXT_TOP });
		SetupText(ui.numProjectilesText, font, HUD_FONT_SIZE, sf::Color::White, { HUD_TEXT_LEFT, HUD_TEXT_TOP + HUD_LINE_HEIGHT });
		SetupText(ui.gameOverText, font, GAME_OVER_FONT_SIZE, sf::Color::Red, { WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f });

		for (int i = 0; i < NUM_MENU_ITEMS; ++i)
		{
			const sf::Vector2f position = { MENU_TEXT_LEFT, MENU_TEXT_TOP + i * MENU_LINE_HEIGHT };
			SetupText(ui.menuItemTexts[i], font, MENU_FONT_SIZE, sf::Color::White, position);
			ui.menuItemTexts[i].setString(MENU_ITEM_STRINGS[i]);
		}

		for (int i = 0; i < NUM_MODE_MENU_ITEMS; ++i)
		{
			const sf::Vector2f position = { MENU_TEXT_LEFT, MENU_TEXT_TOP + i * MENU_LINE_HEIGHT };
			SetupText(ui.modeMenuTexts[i], font, MENU_FONT_SIZE, MENU_ITEM_COLOR, position);
		}
		ui.modeMenuTexts[MODE_MENU_START_INDEX].setString(MODE_MENU_START_STRING);
		ui.modeMenuTexts[MODE_MENU_BACK_INDEX].setString(MODE_MENU_BACK_STRING);

		ui.gameOverText.setString("GAME OVER");

		const sf::FloatRect gameOverTextBounds = ui.gameOverText.getLocalBounds();
		ui.gameOverText.setOrigin(gameOverTextBounds.left + (gameOverTextBounds.width / 2.f), 
								  gameOverTextBounds.top + (gameOverTextBounds.height / 2.f));

		SetupText(ui.menuHintText, font, MENU_HINT_FONT_SIZE, MENU_HINT_COLOR, { WINDOW_WIDTH - MENU_HINT_RIGHT_MARGIN, MENU_TEXT_TOP });
		ui.menuHintText.setString(MENU_HINT_STRING);

		const sf::FloatRect menuHintBounds = ui.menuHintText.getLocalBounds();
		ui.menuHintText.setOrigin(menuHintBounds.left + menuHintBounds.width, 0.f);

		ui.hudShape.setSize({ FIELD_WIDTH, (float)HUD_HEIGHT });
		ui.hudShape.setPosition(0.f, 0.f);
		ui.hudShape.setFillColor(HUD_COLOR);

		ui.fieldShape.setSize({ FIELD_WIDTH, FIELD_HEIGHT });
		ui.fieldShape.setPosition(FIELD_LEFT, FIELD_TOP);
		ui.fieldShape.setFillColor(FIELD_COLOR);
		ui.fieldShape.setOutlineThickness(FIELD_OUTLINE_THICKNESS);
		ui.fieldShape.setOutlineColor(FIELD_OUTLINE_COLOR);

		ui.overlayShape.setSize({ WINDOW_WIDTH, WINDOW_HEIGHT });
	}

	void DrawBackground(const UI& ui, sf::RenderWindow& window)
	{
		window.draw(ui.hudShape);
		window.draw(ui.fieldShape);
	}

	void UpdateMenuOverlay(UI& ui, bool isSceneVisible)
	{
		if (isSceneVisible)
		{
			ui.overlayShape.setFillColor(sf::Color(0, 0, 0, PAUSE_OVERLAY_ALPHA));
		}
		else
		{
			ui.overlayShape.setFillColor(MENU_BG_COLOR);
		}
	}

	void DrawOverlay(const UI& ui, sf::RenderWindow& window)
	{
		window.draw(ui.overlayShape);
	}

	void DrawGameOver(const UI& ui, sf::RenderWindow& window)
	{
		window.draw(ui.gameOverText);
	}

	void DrawMenu(const UI& ui, sf::RenderWindow& window)
	{
		for (int i = 0; i < NUM_MENU_ITEMS; ++i)
		{
			window.draw(ui.menuItemTexts[i]);
		}

		window.draw(ui.menuHintText);
	}

	void UpdateModeMenu(UI& ui, unsigned int modeMask, int selectedIndex)
	{
		for (int i = 0; i < NUM_MODE_OPTIONS; ++i)
		{
			const bool isOn = (modeMask & MODE_OPTION_BITS[i]) != 0;
			const std::string row = std::to_string(i + 1) + ". " + MODE_OPTION_STRINGS[i] + (isOn ? "  [x]" : "  [ ]");
			ui.modeMenuTexts[i].setString(row);
		}

		for (int i = 0; i < NUM_MODE_MENU_ITEMS; ++i)
		{
			ui.modeMenuTexts[i].setFillColor(i == selectedIndex ? MENU_ACTIVE_ITEM_COLOR : MENU_ITEM_COLOR);
		}
	}

	void DrawModeMenu(const UI& ui, sf::RenderWindow& window)
	{
		for (int i = 0; i < NUM_MODE_MENU_ITEMS; ++i)
		{
			window.draw(ui.modeMenuTexts[i]);
		}

		window.draw(ui.menuHintText);
	}

	void UpdateGameOverFade(UI& ui, float alphaProgress)
	{
		if (alphaProgress < 0.f) alphaProgress = 0.f;
		if (alphaProgress > 1.f) alphaProgress = 1.f;

		sf::Color color = MENU_BG_COLOR;
		float alpha = alphaProgress * MENU_BG_COLOR.a;
		color.a = static_cast<sf::Uint8>(alpha);
		ui.overlayShape.setFillColor(color);
	}

	void DrawHUD(const UI& ui, sf::RenderWindow& window)
	{
		window.draw(ui.scoreText);
		window.draw(ui.numProjectilesText);
	}
}