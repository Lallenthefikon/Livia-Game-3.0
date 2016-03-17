#pragma once

#include "Factory.h"
#include "Entityhandler.h"
#include "Terrainhandler.h"
#include "Decorationhandler.h"
#include "Dialoguehandler.h"
#include "Level.h"

class MapGenerator{
public:
	typedef std::vector<Terrain*> Terrains;
	typedef std::vector<BlockTerrain*> BlockTerrains;
	static MapGenerator& getInstance();

	void loadMap(std::string &mapname, Level *level);

	
private:
	MapGenerator();
	~MapGenerator();

	sf::Vector2f readPosition(std::string line);

	void readTerrainfile(std::string &filename, Level *level);
	void readEntityfile(std::string &filename);
	void readDecorationfile(std::string &filename);

	// Entities
	void createWorm(sf::Vector2f pos);
	void createGerm(sf::Vector2f pos);
	void createPlayer(sf::Vector2f pos);
	void createAcidMonster(sf::Vector2f pos);
	void createMeatball(sf::Vector2f pos);
	void createExtraLife(sf::Vector2f pos);
	void createOcto_Pi(sf::Vector2f pos);
	
	// Terrains
	void createBlock0(sf::Vector2f pos, char type);
	void createBlock0WallJump(sf::Vector2f pos, char type);
	void createBlock0Icy(sf::Vector2f pos, char type);
	void createSpikes(sf::Vector2f pos, char type);
	void createGoal(sf::Vector2f pos);
	void createMeatballSpawner(sf::Vector2f pos);
	
	
	// Decoration
	void createDecoration(sf::Vector2f pos, char id, char layer, char rotation);
	void createEvent(sf::Vector2f pos,Level *level, char eventType, sf::Vector2f size);
	
	void createCollisionBlocks();
	void mergeCollisionblocks(BlockTerrains& blockterrains);


	// Pekare till singeltonklasser
	Terrainhandler *mTerrainhandler;
	Entityhandler *mEntityHandler;
	Decorationhandler *mDecorationhandler;

	Terrains mTempBlocks;
};

