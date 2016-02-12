#pragma once

#include "GameState.h"
#include "Entityhandler.h"
#include "Terrainhandler.h"
#include "Collisionhandler.h"
#include "MapGenerator.h"
#include "Toolbox.h"
#include "Animations.h"
#include "Camera.h"
#include "Intestine.h"

class GameRun : public GameState{
public:
	static GameRun* getInstance(std::string &levelDirectory, std::string &levelName);
	virtual void update(sf::RenderWindow &window);
	virtual void render(sf::RenderWindow &window);
	virtual void loadMap();
	virtual void setCurrentLevel(std::string &levelDirectory, std::string &levelName){ mCurrentLevelDirectory = levelDirectory, mCurrentLevelName = levelName; }
private:
	GameRun(std::string &mapname, std::string &levelName);
	~GameRun();

	/*Entityhandler& mEntityHandler;
	Terrainhandler& mTerrainHandler;
	MapGenerator& mMapGenerator;
	Collisionhandler& mCollisionHandler;*/

	Intestine& mIntestine;

	std::string mCurrentLevelDirectory;
	std::string mCurrentLevelName;

	//Camera mCamera;
};

