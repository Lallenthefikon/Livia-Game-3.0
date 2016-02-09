#pragma once

#include <vector>
#include "Terrain.h"

class Terrainhandler{
public:
	typedef std::vector<Terrain*> Terrains;
	static Terrainhandler& getInstance();
	void addTerrain(Terrain* terrain);
	void renderTerrains(sf::RenderWindow &window);
	void updateTerrains();
	Terrains& getTerrains(){ return mTerrains; }
	void clear();
private:
	Terrainhandler();
	~Terrainhandler();

	void internalClear();

	Terrains mTerrains;
};

