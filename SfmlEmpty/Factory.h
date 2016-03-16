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
	static Entity* createWorm(sf::Vector2f pos);
	static Entity* createAcidMonster(sf::Vector2f pos);
	static Entity* createMeatball(sf::Vector2f pos);
	static Entity* createExtraLife(sf::Vector2f pos);
	static Entity* createGerm(sf::Vector2f pos);
	static Entity* createOcto_Pi(sf::Vector2f pos);
	
	static Terrain* createBlock0(sf::Vector2f pos, char type);
	static Terrain* createBlock0WallJump(sf::Vector2f pos, char type);
	static Terrain* createSpikes(sf::Vector2f pos, char type);
	static Terrain* createMeatballSpawner(sf::Vector2f pos);
	static Terrain* createGoal(sf::Vector2f pos);
	static Terrain* createBlock0Icy(sf::Vector2f pos, char id);
	static Terrain* createEditorEvent(sf::Vector2f pos, char eventType, sf::Vector2f size);

	static Terrain* createEvent(sf::Vector2f pos, Level* level, char eventType, sf::Vector2f size);
	static BlockTerrain* createCollisionBlock(sf::Vector2f pos);
	static Decoration* createDecoration(sf::Vector2f pos, char id, char layer);

};