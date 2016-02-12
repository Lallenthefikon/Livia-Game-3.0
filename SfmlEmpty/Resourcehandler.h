#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <map>

struct Resourcehandler {
	enum LEVELKEY { LEVEL0, LEVEL1, LEVEL2, LEVEL3, EDITOR };
	static Resourcehandler& getInstance();
	static void loadLevelAssets();
	static std::map<sf::Image&, int>& getTextures(LEVELKEY levelKey);
	static std::map<sf::SoundBuffer&, int>& getSounds(LEVELKEY levelKey);
};

