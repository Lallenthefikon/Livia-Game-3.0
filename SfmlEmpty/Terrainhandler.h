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
	void renderTerrains(sf::RenderWindow &window);
	void updateTerrains();
	Terrains& getTerrains(){ return mTerrains; }
	void clear();
	void createCollisionBlocks();
private:
	Terrainhandler();
	~Terrainhandler();

	void internalClear();
	
	BlockTerrains mBlockTerrains;
	Terrains mTerrains;
};

