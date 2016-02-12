#pragma once

#include "SFML\Graphics.hpp"
#include "Toolbox.h"
#include <vector>

struct Animations{
	typedef std::vector<sf::Texture*> Textures;
	static void loadTextures();
	static Textures* getPlayerRunningLeftANI();
	static Textures* getPlayerRunningRightANI();
	static Textures* getPlayerJumpingANI();
	static Textures* getPlayerIdleLeftANI();
	static Textures* getPlayerIdleRightANI();
	static Textures* getWormCrawlingRightANI();
	static Textures* getWormCrawlingLeftANI();
	static Textures* getAcidMonster();
};

