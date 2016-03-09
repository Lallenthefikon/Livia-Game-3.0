#pragma once

#include <SFML\System.hpp>

class Entity;
class Terrain;
class BlockTerrain;
class Decoration;
class Dialogue;
class Level;

struct Factory{
	static Entity* createPlayer(sf::Vector2f pos);
	static Terrain* createBlock0(sf::Vector2f pos, char type);
	static Entity* createWorm(sf::Vector2f pos);
	static Entity* createAcidMonster(sf::Vector2f pos);
	static Terrain* createBlock0WallJump(sf::Vector2f pos, char type);
	static Terrain* createSpikes(sf::Vector2f pos, char type);
	static Terrain* createGoal(sf::Vector2f pos);

	static Terrain* createEvent(sf::Vector2f pos, char eventType);
	static BlockTerrain* createCollisionBlock(sf::Vector2f pos);
	static Decoration* createDecoration(sf::Vector2f pos, char id, char layer);
	static Entity* createMeatball(sf::Vector2f pos);
	static Terrain* createMeatballSpawner(sf::Vector2f pos, float spawnRate);

	static Terrain* createBlock0Icy(sf::Vector2f pos, char id);
};