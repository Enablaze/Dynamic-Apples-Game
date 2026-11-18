#include "Resources.h"
#include "Constants.h"
#include <cassert>

namespace DynamicApplesGame
{
	void LoadFont(sf::Font& font, const std::string& fileName)
	{
		const bool isLoaded = font.loadFromFile(FONTS_PATH + fileName);
		assert(isLoaded);
		(void)isLoaded;
	}

	void LoadTexture(sf::Texture& texture, const std::string& fileName)
	{
		const bool isLoaded = texture.loadFromFile(TEXTURES_PATH + fileName);
		assert(isLoaded);
		(void)isLoaded;
	}

	void LoadSoundBuffer(sf::SoundBuffer& buffer, const std::string& fileName)
	{
		const bool isLoaded = buffer.loadFromFile(SOUNDS_PATH + fileName);
		assert(isLoaded);
		(void)isLoaded;
	}

	void LoadResources(Resources& resources)
	{
		LoadFont(resources.uiFont, "Roboto-Bold.ttf");
		LoadTexture(resources.playerTexture, "Player.png");
		LoadTexture(resources.appleTexture, "Apple.png");
		LoadTexture(resources.stoneTexture, "Rock.png");

		LoadSoundBuffer(resources.eatBuffer, "SFX_AppleEat.wav");
		LoadSoundBuffer(resources.deathBuffer, "SFX_Fail_Flute.wav");
		LoadSoundBuffer(resources.throwBuffer, "SFX_Throw.wav");
		
		resources.eatSound.setBuffer(resources.eatBuffer);
		resources.deathSound.setBuffer(resources.deathBuffer);
		resources.throwSound.setBuffer(resources.throwBuffer);

		resources.throwSound.setVolume(THROW_VOLUME);
		resources.eatSound.setVolume(EAT_VOLUME);
		resources.deathSound.setVolume(DEATH_VOLUME);
	}
}