#pragma once

#include "GameState.h"
#include "Entityhandler.h"
#include "Terrainhandler.h"
#include "Collisionhandler.h"
#include "MapGenerator.h"
#include "Toolbox.h"
#include "Animations.h"
#include "Camera.h"
#include "Stomach.h"
#include "Throat.h"
#include "Hub.h"
#include "Mouth.h"
#include "Intestine.h"

class GameRun : public GameState{
public:
	static GameRun* getInstance(std::string &levelDirectory, std::string &levelName);
	virtual void update(sf::RenderWindow &window);
	virtual void render(sf::RenderWindow &window);
	virtual void loadLevel();
	virtual void setCurrentLevel(std::string &levelDirectory, std::string &levelName){ mCurrentLevelDirectory = levelDirectory, mCurrentLevelName = levelName; }
	void changeLevel(std::string levelName);
private:
	GameRun(std::string &mapname, std::string &levelName);
	~GameRun();

	/*Entityhandler& mEntityHandler->;
	Terrainhandler& mTerrainHandler;
	MapGenerator& mMapGenerator;
	Collisionhandler& mCollisionHandler;*/

	Level* mCurrentLevel;
	//Hub &mHub;



	std::string mCurrentLevelDirectory;
	std::string mCurrentLevelName;

	//Camera mCamera;
};

