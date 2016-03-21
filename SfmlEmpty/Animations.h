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
	static Textures* getPlayerFallDyingANI();
	static Textures* getPlayerSlideANI();

	static Textures* getWormCrawlingANI();
	static Textures* getWormDyingANI();

	static Textures* getAcidMonsterHorizontal();
	static Textures* getAcidMonsterVertical();
	static Textures* getGermWalkingANI();
	static Textures* getGermDamagedANI();

	static Textures* getOcto_PiANI();

	static Textures* getAcidMonster();

	static Textures* getMeatballANI();

	static Textures* getHeartANI();
	static Textures* getDialogueLiviaANI();
	static Textures* getDialogueMansaANI();
	static Textures* getDialogueMuhninANI();
	static Textures* getDialogueTummyANI();

	static Textures* getSpikesANI();

	static Textures* getDecoration0ANI();
	static Textures* getDecoration1ANI();
	static Textures* getDecoration2ANI();
	static Textures* getDecoration3ANI();
	static Textures* getDecoration4ANI();
	static Textures* getDecoration5ANI();
	static Textures* getDecoration6ANI();
	static Textures* getDecoration7ANI();
	static Textures* getDecoration8ANI();
	static Textures* getDecoration9ANI();
	static Textures* getDecoration10ANI();
	static Textures* getDecoration11ANI();
	static Textures* getDecoration12ANI();
	static Textures* getDecoration13ANI();
	static Textures* getDecoration14ANI();
	static Textures* getDecoration15ANI();
	static Textures* getDecoration16ANI();
	static Textures* getDecoration17ANI();
	static Textures* getDecoration18ANI();
	static Textures* getDecoration19ANI();
	static Textures* getDecoration20ANI();
	static Textures* getDecoration21ANI();
	static Textures* getDecoration22ANI();
	static Textures* getDecoration23ANI();
	static Textures* getDecoration24ANI();
	static Textures* getDecoration25ANI();
	static Textures* getDecoration26ANI();
	static Textures* getDecoration27ANI();
	static Textures* getDecoration28ANI();
	static Textures* getDecoration29ANI();
};

