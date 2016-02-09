#pragma once

#include "Factory.h"
#include "Entityhandler.h"
#include "Terrainhandler.h"

class MapGenerator{
public:

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

	// Pekare till singeltonklasser
	Terrainhandler *mTerrainhandler;
	Entityhandler *mEntityhandler;

};

