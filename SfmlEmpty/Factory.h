#pragma once

#include <SFML\System.hpp>

class Entity;
class Terrain;
class Decoration;
class Dialogue;

struct Factory{
	static Entity* createPlayer(sf::Vector2f pos);
	static Terrain* createBlock0(sf::Vector2f pos, char type);
	static Entity* createWorm(sf::Vector2f pos);
	static Entity* createAcidMonster(sf::Vector2f pos);
	static Terrain* createBlock0WallJump(sf::Vector2f pos, char type);
	static Terrain* createSpikes(sf::Vector2f pos, char type);
	static Terrain* createGoal(sf::Vector2f pos);
	static Dialogue* createDialogue(sf::Vector2f pos);
	static Decoration* createDecoration(sf::Vector2f pos, char id);
};