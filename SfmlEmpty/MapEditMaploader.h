#pragma once

#include <SFML\System.hpp>
#include <vector>
#include "Factory.h"
#include "Entity.h"
#include "Terrain.h"
#include "Decoration.h"

class MapEditMaploader{
public:

	typedef std::vector<Entity*> Entities;
	typedef std::vector<Terrain*> Terrains;
	typedef std::vector<Decoration*> Decorations;

	static MapEditMaploader& getInstance();

	Terrains getTerrain(std::string &filename);
	Entities getEntities(std::string &filename);
	Decorations getDecorations(std::string &filename);

	void clear();

private:
	MapEditMaploader();
	~MapEditMaploader();

	void readTerrainfile(std::string &mapname);
	void readEntityfile(std::string &mapname);
	void readDecorationfile(std::string &mapname);

	void createBlock0(sf::Vector2f &pos, char type);
	void createPlayer(sf::Vector2f &pos);
	void createWorm(sf::Vector2f &pos);
	void createAcidMonster(sf::Vector2f &pos);
	void createBlock0WallJump(sf::Vector2f &pos, char type);
	void createSpikes(sf::Vector2f &pos, char type);
	void createGoal(sf::Vector2f &pos);
	void createDecoration(sf::Vector2f &pos, char id);

	sf::Vector2f readPosition(std::string line);

	void internalClear();

	Entities mEntities;
	Terrains mTerrains;
	Decorations mDecorations;
};

