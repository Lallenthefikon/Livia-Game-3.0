#include "Hub.h"
#include <iostream>

Hub::Hub() :
	// Initiate singleton classes
	mBackground(),
	mTexture(),

	mTerrainHandler(Terrainhandler::getInstance()),
	mEntityHandler(Entityhandler::getInstance()),

	mMapGenerator(MapGenerator::getInstance()),
	mCollisionHandler(Collisionhandler::getInstance()),
	mLayerHandler(LayerHandler::getInstance()),
	mTextHandler(Texthandler::getInstance()),
	mDecorationhandler(Decorationhandler::getInstance()),
	mDialoguehandler(Dialoguehandler::getInstance()),

	mCamera(),

	mMapName("Stomach"),
	mMapPath("resources/maps/mMap0.txt"),
	mLevelState("Center"),

	mZoomedOut(false),
	mLevelBounds(0.f, 0.f, 15000.f, 12300.f) {

	Toolbox::loadTextures(mMapName);
	Toolbox::loadSounds(mMapName);
	Toolbox::loadFonts(mMapName);
	Animations::loadTextures();

	Toolbox::copyLevelBounds(mLevelBounds);

	mLifeTexture.loadFromImage(Toolbox::getTexture(Toolbox::LIFETEXTURE));
	mLifeSprite.setTexture(mLifeTexture);
	mLifeSprite.setScale(1.5, 1.5);
	mLayerHandler.addLifeSprite(mLifeSprite);

	mBackgroundTexture.loadFromImage(Toolbox::getTexture(Toolbox::STOMACHBACKGROUND));
	mLayerHandler.addBackground(mBackgroundTexture);

	mAcidTexture.loadFromImage(Toolbox::getTexture(Toolbox::STOMACHACID));
	mLayerHandler.addForegroundObject(mAcidTexture);

	mMiddlegroundTexture.loadFromImage(Toolbox::getTexture(Toolbox::STOMACHMIDDLEGROUND));
	mLayerHandler.addMiddleground(mMiddlegroundTexture);
	//mLayerHandler.addMiddleground(mAcidTexture);
	//mLayerHandler.addAcid(mAcidTexture);

}

Hub::~Hub() {
}

Hub& Hub::getInstance() {
	static Hub Hub;
	return Hub;
}

void Hub::update(sf::RenderWindow &window) {
	// Specific event loop for gameRun state
	sf::Event gEvent;
	while (window.pollEvent(gEvent)) {
		if (gEvent.type == sf::Event::Closed)
			window.close();
	}
	// Updates independent of state

	if (!Toolbox::getPlayerIsAlive()) {
		resetLevel(window);
	}
	// Updates depending on state
	if (mLevelState == "Center") {
		//mCamera.updateStomachCam(window,mLevelState);
		mCamera.updateHubCam(window, mLevelState);
		mLevelState = "Standard";
	}
	if (mLevelState == "Standard") {
		mCamera.updateHubCam(window, mLevelState);

		mEntityHandler->update();
		mTerrainHandler->update();
		mCollisionHandler.checkCollision(mEntityHandler->getEntities(), mTerrainHandler->getTerrains(), mTerrainHandler->getCollisionTerrains());
		mEntityHandler->bringOutTheDead();
		mDialoguehandler.updateDialogue(Toolbox::getPlayerPosition());

		window.setView(mCamera.getTileView());
		sf::Vector2f tileViewCoordPos = Toolbox::findCoordPos(sf::Vector2i(mCamera.getTileView().getCenter().x, 0), window);
		window.setView(mCamera.getSceneryView());
		sf::Vector2f sceneViewCoordPos = Toolbox::findCoordPos(sf::Vector2i(tileViewCoordPos.x, 0), window);
		//mLayerHandler.moveStationaryBackground(window, mCamera, sceneViewCoordPos, tileViewCoordPos);
		//mLayerHandler.moveStationaryForeground(window, mCamera, sceneViewCoordPos, tileViewCoordPos);
		mLayerHandler.moveBackground(window, mCamera, sceneViewCoordPos, tileViewCoordPos);
		mLayerHandler.moveStationaryForeground(window, mCamera, sceneViewCoordPos, tileViewCoordPos);
		mLayerHandler.moveMiddleground(window, mCamera, sceneViewCoordPos, tileViewCoordPos);
		mLayerHandler.updateHud(mCamera.getTileView().getCenter(), tileViewCoordPos);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
			GameRun::getInstance(std::string(""), std::string(""))->changeLevel("Stomach");
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
			GameRun::getInstance(std::string(""), std::string(""))->changeLevel("Throat");
		}
	}
	if (mLevelState == "Reset") {
		resetLevel(window);
	}
}

void Hub::render(sf::RenderWindow &window) {
	window.clear();

	// Change view to sceneryView containing background, HUD and other estetic scene objects
	window.setView(mCamera.getSceneryView());
	mLayerHandler.renderBackground(window);

	// Middleground
	mLayerHandler.renderMiddleground(window);

	// Change view to tileView containing all entities and terrains
	window.setView(mCamera.getTileView());



	// Decorations back
	mDecorationhandler.renderDecoration(window, 'b');

	// Terrains
	mTerrainHandler->render(window);
	mCollisionHandler.renderCollision(window);

	// Entities
	mLayerHandler.renderForeground(window);
	mEntityHandler->render(window);


	// Decorations front
	mDecorationhandler.renderDecoration(window, 'f');

	// Hud
	mLayerHandler.renderHud(window);


	// Dialogue
	mDialoguehandler.renderDialogue(window);


	window.display();
}

void Hub::loadLevel() {
	Toolbox::loadTextures(mMapName);
	mMapGenerator.loadMap(mMapPath);
	mLevelState = "Center";
}

void Hub::unloadLevel() {
	//Toolbox::unloadTextures(mMapName);
}

void Hub::setCurrentMap(std::string &mapname) {
}

void Hub::resetLevel(sf::RenderWindow &window) {
	mCamera.centerOnPlayer(window, 0, -300);
	mMapGenerator.loadMap(mMapPath);
	mLevelState = "Center";
}
