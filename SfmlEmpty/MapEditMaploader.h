#pragma once

#include <SFML\System.hpp>
#include <vector>
#include "Factory.h"
#include "Entity.h"
#include "Terrain.h"

class MapEditMaploader{
public:

	typedef std::vector<Entity*> Entities;
	typedef std::vector<Terrain*> Terrains;

	static MapEditMaploader& getInstance();

	Terrains getTerrain(std::string &filename);
	Entities getEntities(std::string &filename);

	void clear();

private:
	MapEditMaploader();
	~MapEditMaploader();

	void readTerrainfile(std::string &mapname);
	void readEntityfile(std::string &mapname);

	void createBlock0(sf::Vector2f &pos, char type);
	void createPlayer(sf::Vector2f &pos);
	void createWorm(sf::Vector2f &pos);

	sf::Vector2f readPosition(std::string line);

	void internalClear();

	Entities mEntities;
	Terrains mTerrains;
};

