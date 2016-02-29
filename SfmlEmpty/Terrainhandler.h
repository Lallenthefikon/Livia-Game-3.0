#pragma once

#include <vector>
#include "Terrain.h"
#include "BlockTerrain.h"

class Terrainhandler{
public:
	typedef std::vector<Terrain*> Terrains;
	typedef std::vector<BlockTerrain*> BlockTerrains;
	static Terrainhandler& getInstance();
	void addTerrain(Terrain* terrain);
	void addCollisionblock(BlockTerrain* blockterrain);
	void renderTerrains(sf::RenderWindow &window);
	void updateTerrains();
	Terrains& getTerrains(){ return mTerrains; }
	BlockTerrains& getCollisionTerrains() { return mCollisionBlocks; }
	void clear();

private:
	Terrainhandler();
	~Terrainhandler();

	void internalClear();
	
	BlockTerrains mCollisionBlocks;
	Terrains mTerrains;
};

