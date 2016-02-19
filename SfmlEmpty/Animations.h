#pragma once

#include "SFML\Graphics.hpp"
#include "Toolbox.h"
#include <vector>

struct Animations{
	typedef std::vector<sf::Texture*> Textures;
	static void loadTextures();
	static Textures* getPlayerRunningANI();
	static Textures* getPlayerJumpingANI();
	static Textures* getPlayerIdleANI();
	static Textures* getPlayerHurtANI();
	static Textures* getPlayerFallingANI();
	static Textures* getPlayerDyingANI();
	static Textures* getPlayerSlideANI();

	static Textures* getWormCrawlingANI();
	static Textures* getWormDyingANI();

	static Textures* getAcidMonster();
	static Textures* getHeartANI();
};

