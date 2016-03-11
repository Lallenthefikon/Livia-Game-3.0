#pragma once

#include <vector>
#include "Terrain.h"
#include "BlockTerrain.h"
#include "Abstracthandler.h"

class Terrainhandler : public Abstracthandler {
public:
	typedef std::vector<BlockTerrain*> BlockTerrains;
	static Terrainhandler* getInstance();

	virtual ~Terrainhandler();

	///<summary>
	/// ID: 0 = Block0, 1 = Wall jump, 2 = Spikes, 3 = Goal, 4 = Meatball spawner, 01 = Collision block
	///</summary>
	virtual void add(sf::Vector2f pos, char id, char type = '0', char layer = '0');
	virtual void render(sf::RenderWindow &window);
	virtual void update();
	virtual void clear();

	void addCollisionblock(BlockTerrain* blockterrain);
	void createEvent(sf::Vector2f pos, Level *level, char eventType, sf::Vector2f size);
	void bringOutTheDead();
	Terrains& getTerrains() { return mTerrains; }
	BlockTerrains& getCollisionTerrains() { return mCollisionBlocks; }

	/*void addTerrain(Terrain* terrain);
	void renderTerrains(sf::RenderWindow &window);
	void updateTerrains();
	
	Terrains& getTerrains(){ return mTerrains; }
	
	void clear();

	~Terrainhandler();*/
private:
	Terrainhandler();
	void internalClear();

	BlockTerrains mCollisionBlocks;
	Terrains mTerrains;
};

