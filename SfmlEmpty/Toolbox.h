#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

struct Toolbox {

	enum TEXTUREKEY { WORMTEXTURE, BLOCK0TEXTURE, RUNNINGPLAYERTEXTURE, PLAYERJUMPTEXTURE, PLAYERIDLETEXTURE, PLAYERHURTTEXTURE, TILETEXTURE, EDITORMENY, ACIDMONSTERTEXTURE, INTESTINEBACKGROUND, LIFETEXTURE};
	enum SOUNDKEY { PLAYERIDLE, PLAYERRUN, PLAYERJUMP, PLAYERLAND, PLAYERDAMAGED, WORMIDLE, WORMRUN, WORMJUMP, WORMLAND };
	static Toolbox& getInstance();
	static void loadTextures(std::string levelName);
	static sf::Image& getTexture(TEXTUREKEY textureKey);

	// Camera Edit
	static void copyScreenInfo(sf::RenderWindow &window, sf::VideoMode &videoMode);
	static sf::Vector2f getWindowSize();
	static sf::Vector2f getResolution();
	static sf::Vector2f getWindowPos();
	static void copyPlayerSprite(sf::Sprite &playerSprite);
	static void copyPlayerVelocity(sf::Vector2f &playerVelocity);
	static sf::Sprite getPlayerSprite();
	static sf::Vector2f getPlayerVelocity();

	// Sounds
	static sf::SoundBuffer& getSound(SOUNDKEY soundKey);
};

