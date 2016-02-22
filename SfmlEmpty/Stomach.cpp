#include "Stomach.h"
#include <iostream>

Stomach::Stomach() :
// Initiate singleton classes
mBackground(),
mTexture(),
mTerrainHandler(Terrainhandler::getInstance()),
mEntityHandler(Entityhandler::getInstance()),
mMapGenerator(MapGenerator::getInstance()),
mCollisionHandler(Collisionhandler::getInstance()),
mLayerHandler(LayerHandler::getInstance()),
mTextHandler(Texthandler::getInstance()),
mCamera(),
mMapName("Stomach"),
mMapPath("resources/maps/mMap0.txt"),
mLevelState("Cutscene"),
mZoomedOut(false){
	Toolbox::loadTextures(mMapName);
	Toolbox::loadSounds(mMapName);
	Toolbox::loadFonts(mMapName);
	Animations::loadTextures();

	mLifeTexture.loadFromImage(Toolbox::getTexture(Toolbox::LIFETEXTURE));
	mLifeSprite.setTexture(mLifeTexture);
	mLifeSprite.setScale(1.5,1.5);
	mLayerHandler.addLifeSprite(mLifeSprite);

	mBackgroundTexture.loadFromImage(Toolbox::getTexture(Toolbox::STOMACHBACKGROUND));

	mLayerHandler.addBackground(mBackgroundTexture);

	mMapGenerator.loadMap(mMapPath);
	

}

Stomach::~Stomach(){
}

Stomach& Stomach::getInstance(){
	static Stomach Stomach;
	return Stomach;
}

void Stomach::update(sf::RenderWindow &window){
	// Specific event loop for gameRun state
	sf::Event gEvent;
	while (window.pollEvent(gEvent)){
		if (gEvent.type == sf::Event::Closed)
			window.close();
	}
	// Updates independent of state
	
	if (!Toolbox::getPlayerIsAlive()){
		resetLevel(window);
	}
	// Updates depending on state
	if (mLevelState == "Cutscene"){
		//mCamera.updateStomachCam(window,mLevelState);
		mCamera.updateStomachCam(window, mLevelState);
		mLevelState = "ZoomOut";
	}
	if (mLevelState == "ZoomOut"){
		if (!mZoomedOut){
			mCamera.updateStomachCam(window, mLevelState);
			mZoomedOut = true;
		}
		mLevelState = "ZoomedOut";
	}
	if (mLevelState == "ZoomedOut"){

		mCamera.updateStomachCam(window, mLevelState);

		mEntityHandler.updateEntities();
		mTerrainHandler.updateTerrains();
		mCollisionHandler.checkCollision(mEntityHandler.getEntities(), mTerrainHandler.getTerrains());
		mEntityHandler.bringOutTheDead();
		
		window.setView(mCamera.getTileView());
		sf::Vector2f tileViewCoordPos = Toolbox::findCoordPos(sf::Vector2i(mCamera.getTileView().getCenter().x, 0), window);
		window.setView(mCamera.getSceneryView());
		sf::Vector2f sceneViewCoordPos = Toolbox::findCoordPos(sf::Vector2i(tileViewCoordPos.x, 0), window);
		mLayerHandler.moveStationaryBackground(window, mCamera, sceneViewCoordPos, tileViewCoordPos);
		//mLayerHandler.moveBackground(window, mCamera, sceneViewCoordPos, tileViewCoordPos);
		mLayerHandler.updateHud(mCamera.getTileView().getCenter(), tileViewCoordPos);
	}
	if (mLevelState == "Rising"){

		mCamera.updateStomachCam(window, mLevelState);

		mEntityHandler.updateEntities();
		mTerrainHandler.updateTerrains();
		mCollisionHandler.checkCollision(mEntityHandler.getEntities(), mTerrainHandler.getTerrains());
		mEntityHandler.bringOutTheDead();
		window.setView(mCamera.getTileView());
		sf::Vector2f tileViewCoordPos = Toolbox::findCoordPos(sf::Vector2i(mCamera.getTileView().getCenter().x, 0), window);
		window.setView(mCamera.getSceneryView());
		sf::Vector2f sceneViewCoordPos = Toolbox::findCoordPos(sf::Vector2i(tileViewCoordPos.x, 0), window);
		mLayerHandler.moveStationaryBackground(window, mCamera, sceneViewCoordPos, tileViewCoordPos);
		//mLayerHandler.moveBackground(window, mCamera, sceneViewCoordPos, tileViewCoordPos);
		mLayerHandler.updateHud(mCamera.getTileView().getCenter(), tileViewCoordPos);
	}
	if (mLevelState == "Reset"){
		resetLevel(window);
	}
}

void Stomach::render(sf::RenderWindow &window){
	window.clear();

	// Change view to sceneryView containing background, HUD and other estetic scene objects
	window.setView(mCamera.getSceneryView());
	mLayerHandler.renderBackground(window);
	
	// Change view to tileView containing all entities and terrains
	window.setView(mCamera.getTileView());

	mTerrainHandler.renderTerrains(window);
	mCollisionHandler.renderCollision(window);
	mEntityHandler.renderEntities(window);
	mLayerHandler.renderHud(window);
	
	window.display();
}

void Stomach::loadLevel(){
	Toolbox::loadTextures(mMapName);
	mMapGenerator.loadMap(mMapPath);
	//if (mLevelState != "ZoomedOut"){
	mLevelState = "Cutscene";
		//std::cout << "Loaded" << std::endl;
	//}
}

void Stomach::unloadLevel(){
	//Toolbox::unloadTextures(mMapName);
}

void Stomach::setCurrentMap(std::string &mapname){
}

void Stomach::resetLevel(sf::RenderWindow &window){
	mCamera.centerOnPlayer(window);
	mMapGenerator.loadMap(mMapPath);
	mLevelState = "Cutscene";
}
