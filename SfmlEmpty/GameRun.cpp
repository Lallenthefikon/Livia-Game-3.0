#include "GameRun.h"

GameRun::GameRun(std::string &levelDirectory, std::string &levelName):
	
// Initiate singleton classes
//mTerrainHandler(Terrainhandler::getInstance()),
//mEntityHandler(Entityhandler::getInstance()),
//mMapGenerator(MapGenerator::getInstance()),
//mCollisionHandler(Collisionhandler::getInstance()),
//mCurrentMap(mapname),
//mCamera()
mIntestine(Intestine::getInstance()){
	setCurrentLevel(levelDirectory, levelName);
	//mMapGenerator.loadMap(mapname);
}

GameRun::~GameRun(){
}

GameRun* GameRun::getInstance(std::string &levelDirectory, std::string &levelName){
	static GameRun gamerun(levelDirectory, levelName);
	return &gamerun;
}

void GameRun::update(sf::RenderWindow &window){
	mIntestine.update(window);
	//// Specific event loop for gameRun state
	//sf::Event gEvent;
	//while (window.pollEvent(gEvent)){

	//	if (gEvent.type == sf::Event::Closed)
	//		window.close();
	//}
	//mEntityHandler.updateEntities();
	//mTerrainHandler.updateTerrains();
	//mCollisionHandler.checkCollision(mEntityHandler.getEntities(), mTerrainHandler.getTerrains());
	//mEntityHandler.bringOutTheDead();
	//mCamera.updateCamGAME(window);
	//window.setView(mCamera.getView());
}

void GameRun::render(sf::RenderWindow &window){
	mIntestine.render(window);
	//window.clear();
	//mTerrainHandler.renderTerrains(window);
	////mCollisionHandler.renderCollision(window);
	//mEntityHandler.renderEntities(window);
	//window.display();
}

void GameRun::loadMap(){
	mIntestine.loadLevel();
	//mMapGenerator.loadMap(mCurrentMap);
}
