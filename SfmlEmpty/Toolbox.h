#pragma once

#include <SFML\Graphics.hpp>

struct Toolbox{
	
	enum TEXTUREKEY { WORMTEXTURE, BLOCK0TEXTURE, PLAYERTEXTURE, TILETEXTURE, EDITORMENY };
	
	static Toolbox& getInstance();
	static void loadTextures();
	static sf::Image& getTexture(TEXTUREKEY textureKey);
	// Camera Edit
	static void copyScreenInfo(sf::RenderWindow &window, sf::VideoMode &videoMode);
	static sf::Vector2f getWindowSize();
	static sf::Vector2f getResolution();
	static sf::Vector2f getWindowPos();
	static void copyPlayerInfo(sf::Sprite &playerSprite);
	static sf::Sprite getPlayerSprite();
};

