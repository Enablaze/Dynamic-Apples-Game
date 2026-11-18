#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace DynamicApplesGame
{
	struct Resources
	{
		sf::Font uiFont;

		sf::Texture playerTexture;
		sf::Texture appleTexture;
		sf::Texture stoneTexture;

		sf::SoundBuffer eatBuffer;
		sf::SoundBuffer deathBuffer;
		sf::SoundBuffer throwBuffer;

		sf::Sound eatSound;
		sf::Sound deathSound;
		sf::Sound throwSound;
	};

	void LoadResources(Resources& resources);
}