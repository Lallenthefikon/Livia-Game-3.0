#pragma once

#include "Factory.h"
#include "Entityhandler.h"
#include "Terrainhandler.h"

class MapGenerator{
public:
	typedef std::vector<Terrain*> Terrains;
	typedef std::vector<BlockTerrain*> BlockTerrains;
	static MapGenerator& getInstance();

	void loadMap(std::string &mapname);

	
private:
	MapGenerator();
	~MapGenerator();

	sf::Vector2f readPosition(std::string line);

	void readTerrainfile(std::string &filename);
	void readEntityfile(std::string &filename);

	void createWorm(sf::Vector2f pos);
	void createPlayer(sf::Vector2f pos);
	void createBlock0(sf::Vector2f pos, char type);
	void createAcidMonster(sf::Vector2f pos);
	void createBlock0WallJump(sf::Vector2f pos, char type);
	void createSpikes(sf::Vector2f pos, char type);
	void createGoal(sf::Vector2f pos);
	void createCollisionBlocks();
	void mergeCollisionblocks(BlockTerrains& blockterrains);

	// Pekare till singeltonklasser
	Terrainhandler *mTerrainhandler;
	Entityhandler *mEntityhandler;

	Terrains mTempBlocks;
};

