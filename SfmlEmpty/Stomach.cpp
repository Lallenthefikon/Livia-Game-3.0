#include "Stomach.h"

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

void Stomach::update(sf::RenderWindow &window, float &frameTime){
	// Specific event loop for gameRun state
	sf::Event gEvent;
	while (window.pollEvent(gEvent)){
		if (gEvent.type == sf::Event::Closed)
			window.close();
	}
	if (mLevelState == "Cutscene"){
		mCamera.centerOnPlayer(window);
		mLevelState = "ZoomOut";
	}
	if (mLevelState == "ZoomOut"){
		if (!mZoomedOut){
			mCamera.zoomOut(0.5f, 1);
			mZoomedOut = true;
		}
		mLevelState = "ZoomedOut";
	}
	if (mLevelState == "ZoomedOut"){

		mCamera.updateStomachCam(window, mLevelState);

		mEntityHandler.updateEntities(frameTime);
		mTerrainHandler.updateTerrains();
		mCollisionHandler.checkCollision(mEntityHandler.getEntities(), mTerrainHandler.getTerrains());
		mEntityHandler.bringOutTheDead();
		window.setView(mCamera.getTileView());
		sf::Vector2f tileViewCoordPos = Toolbox::findCoordPos(sf::Vector2i(mCamera.getTileView().getCenter().x, 0), window);
		window.setView(mCamera.getSceneryView());
		sf::Vector2f sceneViewCoordPos = Toolbox::findCoordPos(sf::Vector2i(tileViewCoordPos.x, 0), window);
		mLayerHandler.moveBackground(window, mCamera, sceneViewCoordPos, tileViewCoordPos);
		mLayerHandler.updateHud(mCamera.getTileView().getCenter(), tileViewCoordPos);
	}
}

void Stomach::render(sf::RenderWindow &window){
	window.clear();
	
	window.setView(mCamera.getSceneryView());
	mLayerHandler.renderBackground(window);
	
	window.setView(mCamera.getTileView());

	mTerrainHandler.renderTerrains(window);
	mCollisionHandler.renderCollision(window);
	mEntityHandler.renderEntities(window);

	mLayerHandler.renderHud(window);
	if (!mEntityHandler.isPlayerAlive())
		mTextHandler.renderText(window);
	
	window.display();
}

void Stomach::loadLevel(){
	Toolbox::loadTextures(mMapName);
	mMapGenerator.loadMap(mMapPath);
	//if (mLevelState != "ZoomedOut"){
		mLevelState = "Cutscene";
	//}
}

void Stomach::unloadLevel(){
	//Toolbox::unloadTextures(mMapName);
}

void Stomach::setCurrentMap(std::string &mapname){
}
