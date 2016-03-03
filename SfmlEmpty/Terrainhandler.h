#pragma once

#include <vector>
#include "Terrain.h"
#include "BlockTerrain.h"
#include "Abstracthandler.h"

class Terrainhandler : public Abstracthandler {
public:
	typedef std::vector<BlockTerrain*> BlockTerrains;
	typedef std::vector<Terrain*> Terrains;
	static Terrainhandler* getInstance();

	virtual ~Terrainhandler();
	virtual void add(sf::Vector2f pos, char id, char type, char layer);
	virtual void render(sf::RenderWindow &window);
	virtual void update();
	virtual void clear();

	Terrains& getTerrains() { return mTerrains; }

	/*void addTerrain(Terrain* terrain);
	void addCollisionblock(BlockTerrain* blockterrain);
	void renderTerrains(sf::RenderWindow &window);
	void updateTerrains();
	
	Terrains& getTerrains(){ return mTerrains; }
	BlockTerrains& getCollisionTerrains() { return mCollisionBlocks; }
	void clear();

	~Terrainhandler();*/
private:
	Terrainhandler();
	void internalClear();
	BlockTerrains& getCollisionTerrains() { return mCollisionBlocks; }

	BlockTerrains mCollisionBlocks;
	Terrains mTerrains;
};

