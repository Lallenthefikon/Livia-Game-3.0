#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

struct Toolbox {


	enum TEXTUREKEY { WORMTEXTURE, BLOCK0TEXTURE, RUNNINGPLAYERTEXTURE, PLAYERJUMPTEXTURE, PLAYERIDLETEXTURE, PLAYERHURTTEXTURE, TILETEXTURE, EDITORMENY, ACIDMONSTERTEXTURE, STOMACHBACKGROUND, LIFETEXTURE};
	enum SOUNDKEY { PLAYERIDLE, PLAYERRUN, PLAYERJUMP, PLAYERLAND, PLAYERDAMAGED, PLAYERDEATH, WORMIDLE, WORMRUN, WORMJUMP, WORMLAND, WORMDEATH, STOMACHMUSIC, STOMACHAMBIENCE };
	enum FONTKEY { GAMEOVER, DIALOGUE };

	static Toolbox& getInstance();
	static void loadTextures(std::string levelName);
	static void loadSounds(std::string levelName);
	static void loadFonts(std::string levelName);
	static sf::Image& getTexture(TEXTUREKEY textureKey);

	static void copyScreenInfo(sf::RenderWindow &window, sf::VideoMode &videoMode);
	static sf::Vector2f getWindowSize();
	static sf::Vector2f getResolution();
	static sf::Vector2f getWindowPos();
	static void copyPlayerSprite(sf::Sprite &playerSprite);
	static void copyPlayerVelocity(sf::Vector2f &playerVelocity);
	static sf::Sprite getPlayerSprite();
	static sf::Vector2f getPlayerVelocity();

	static sf::Vector2f findCoordPos(sf::Vector2i &pixelPos,sf::RenderWindow &window);

	// Sounds
	static sf::SoundBuffer& getSound(SOUNDKEY soundKey);
	static sf::Music& getMusic(SOUNDKEY soundKey);

	// Fonts
	static sf::Font& getFont(FONTKEY fontKey);
};

