#include "Intestine.h"

Intestine::Intestine() :
// Initiate singleton classes
mTerrainHandler(Terrainhandler::getInstance()),
mEntityHandler(Entityhandler::getInstance()),
mMapGenerator(MapGenerator::getInstance()),
mCollisionHandler(Collisionhandler::getInstance()),
mCamera(),
mMapName("Intestine"),
mMapPath("resources/maps/mMap0.txt"){
	Toolbox::loadTextures("Intestine");
	Animations::loadTextures();
	mMapGenerator.loadMap(mMapPath);
}

Intestine::~Intestine(){
}

Intestine& Intestine::getInstance(){
	static Intestine intestine;
	return intestine;
}

void Intestine::update(sf::RenderWindow &window){
	// Specific event loop for gameRun state
	sf::Event gEvent;
	while (window.pollEvent(gEvent)){

		if (gEvent.type == sf::Event::Closed)
			window.close();
	}
	mEntityHandler.updateEntities();
	mTerrainHandler.updateTerrains();
	mCollisionHandler.checkCollision(mEntityHandler.getEntities(), mTerrainHandler.getTerrains());
	mEntityHandler.bringOutTheDead();
	mCamera.updateCamGAME(window);
	window.setView(mCamera.getView());
}

void Intestine::render(sf::RenderWindow &window){
	window.clear();
	mTerrainHandler.renderTerrains(window);
	mCollisionHandler.renderCollision(window);
	mEntityHandler.renderEntities(window);
	window.display();
}

void Intestine::loadLevel(){
	Toolbox::loadTextures(mMapName);
	mMapGenerator.loadMap(mMapPath);
}

void Intestine::unloadLevel(){
	//Toolbox::unloadTextures(mMapName);
}

void Intestine::setCurrentMap(std::string &mapname){
}