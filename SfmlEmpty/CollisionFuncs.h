#pragma once
#include <SFML\Graphics.hpp>

struct CollisionFuncs{
	static bool currentCollisionT(sf::Sprite& s0, sf::Sprite& s1);
	static bool currentCollisionB(sf::Sprite& s0, sf::Sprite& s1);
	static bool currentCollisionL(sf::Sprite& s0, sf::Sprite& s1);
	static bool currentCollisionR(sf::Sprite& s0, sf::Sprite& s1);
};

