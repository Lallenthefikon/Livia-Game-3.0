#include "Stomach.h"

Stomach::Stomach() :
// Initiate singleton classes
mTexture(),
mTerrainHandler(Terrainhandler::getInstance()),
mEntityHandler(Entityhandler::getInstance()),
mMapGenerator(MapGenerator::getInstance()),
mCollisionHandler(Collisionhandler::getInstance()),
mLayerHandler(LayerHandler::getInstance()),
mCamera(),
mMapName("Stomach"),
mMapPath("resources/maps/mMap0.txt"),
mLevelState("Cutscene"){
	Toolbox::loadTextures(mMapName);
	Toolbox::loadSounds(mMapName);
	Animations::loadTextures();

	mBackgroundTexture.loadFromImage(Toolbox::getTexture(Toolbox::STOMACHBACKGROUND));

	mLayerHandler.addBackground(mBackgroundTexture);

	mMapGenerator.loadMap(mMapPath);
	mCamera.zoomOut(0.5f, 1);

}

Stomach::~Stomach(){
}

Stomach& Stomach::getInstance(){
	static Stomach Stomach;
	return Stomach;
}

void Stomach::update(sf::RenderWindow &window, float &frameTime){
	// Specific event loop for gameRun state
	sf::Event gEvent;
	while (window.pollEvent(gEvent)){
		if (gEvent.type == sf::Event::Closed)
			window.close();
	}
	if (mLevelState == "Cutscene"){
		mCamera.centerOnPlayer(window);
		mLevelState = "ZoomedOut";
	}
	if (mLevelState == "ZoomedOut"){

		mCamera.updateStomachCam(window, mLevelState);
		window.setView(mCamera.getTileView());

		mEntityHandler.updateEntities(frameTime);
		mTerrainHandler.updateTerrains();
		mCollisionHandler.checkCollision(mEntityHandler.getEntities(), mTerrainHandler.getTerrains());
		mEntityHandler.bringOutTheDead();

		sf::Vector2f tileViewCoordPos = Toolbox::findCoordPos(sf::Vector2i(mCamera.getTileView().getCenter().x, 0), window);
		window.setView(mCamera.getSceneryView());
		sf::Vector2f sceneViewCoordPos = Toolbox::findCoordPos(sf::Vector2i(tileViewCoordPos.x, 0), window);
		mLayerHandler.moveBackground(window, mCamera, sceneViewCoordPos, tileViewCoordPos);
	}

}

void Stomach::render(sf::RenderWindow &window){
	window.clear();
	
	window.setView(mCamera.getSceneryView());
	mLayerHandler.render(window);
	window.setView(mCamera.getTileView());
	mTerrainHandler.renderTerrains(window);
	mCollisionHandler.renderCollision(window);
	mEntityHandler.renderEntities(window);
	
	window.display();
}

void Stomach::loadLevel(){
	Toolbox::loadTextures(mMapName);
	mMapGenerator.loadMap(mMapPath);
	mLevelState = "Cutscene";
}

void Stomach::unloadLevel(){
	//Toolbox::unloadTextures(mMapName);
}

void Stomach::setCurrentMap(std::string &mapname){
}
