#include "GameRun.h"

GameRun::GameRun(std::string &mapname):
	
// Initiate singleton classes
mTerrainHandler(Terrainhandler::getInstance()),
mEntityHandler(Entityhandler::getInstance()),
mMapGenerator(MapGenerator::getInstance()),
mCollisionHandler(Collisionhandler::getInstance()),
mCurrentMap(mapname),
mCamera(){
	Toolbox::loadTextures();
	Animations::loadTextures();
	mMapGenerator.loadMap(mapname);
}

GameRun::~GameRun(){
}

GameRun* GameRun::getInstance(std::string &mapname){
	static GameRun gamerun(mapname);
	return &gamerun;
}

void GameRun::update(sf::RenderWindow &window){
	// Specific event loop for gameRun state
	sf::Event gEvent;
	while (window.pollEvent(gEvent)){

		if (gEvent.type == sf::Event::Closed)
			window.close();
	}
	mEntityHandler.updateEntities();
	mTerrainHandler.updateTerrains();
	mCollisionHandler.checkCollision(mEntityHandler.getEntities(), mTerrainHandler.getTerrains());
	mCamera.updateCamGAME(window);
	window.setView(mCamera.getView());
}

void GameRun::render(sf::RenderWindow &window){
	window.clear();
	mTerrainHandler.renderTerrains(window);
	//mCollisionHandler.renderCollision(window);
	mEntityHandler.renderEntities(window);
	window.display();
}

void GameRun::loadMap(){
	mMapGenerator.loadMap(mCurrentMap);
}
