#include "Throat.h"
#include <iostream>

Throat::Throat() :
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

	mMapName("Throat"),
	mMapPath("resources/maps/mMap2.txt"),
	mLevelState("Cutscene"),

	mZoomedOut(false),
	mLevelBounds(0.f, 0.f, 15000.f, 57500.f) {

}

Throat::~Throat() {
}

Throat& Throat::getInstance() {
	static Throat Throat;
	return Throat;
}

void Throat::update(sf::RenderWindow &window) {
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
	if (mLevelState == "Cutscene") {
		mCamera.updateThroatCam(window, mLevelState);
		mLevelState = "ZoomOut";
	}
	if (mLevelState == "ZoomOut") {
		if (!mZoomedOut) {
			mCamera.updateThroatCam(window, mLevelState);
			mZoomedOut = true;
		}
		mLevelState = "ZoomedOut";
	}
	if (mLevelState == "ZoomedOut") {

		if (Toolbox::getPlayerHealth() > 0) {
			mCamera.updateThroatCam(window, mLevelState);
		}
		else {
			mCamera.updateThroatCam(window, "Stop");
		}

		mEntityHandler->update();
		mTerrainHandler->update();
		mCollisionHandler.checkCollision(mEntityHandler->getEntities(), mTerrainHandler->getTerrains(), mTerrainHandler->getCollisionTerrains());
		mEntityHandler->bringOutTheDead();

		window.setView(mCamera.getTileView());
		sf::Vector2f tileViewCoordPos = Toolbox::findCoordPos(sf::Vector2i(mCamera.getTileView().getCenter().x, 0), window);
		window.setView(mCamera.getSceneryView());
		sf::Vector2f sceneViewCoordPos = Toolbox::findCoordPos(sf::Vector2i(tileViewCoordPos.x, 0), window);
		mLayerHandler.moveBackgroundVertical(window, mCamera, sceneViewCoordPos, tileViewCoordPos);
		mLayerHandler.moveStationaryForeground(window, mCamera, sceneViewCoordPos, tileViewCoordPos);
		mLayerHandler.moveMiddleground(window, mCamera, sceneViewCoordPos, tileViewCoordPos);
		mLayerHandler.updateHud(mCamera.getTileView().getCenter(), tileViewCoordPos);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
			GameRun::getInstance(std::string(""), std::string(""))->changeLevel("Hub");
		}

	}
	if (mLevelState == "Rising") {

		mCamera.updateThroatCam(window, mLevelState);

		mEntityHandler->update();
		mTerrainHandler->update();
		mCollisionHandler.checkCollision(mEntityHandler->getEntities(), mTerrainHandler->getTerrains(), mTerrainHandler->getCollisionTerrains());
		mEntityHandler->bringOutTheDead();
		window.setView(mCamera.getTileView());
		sf::Vector2f tileViewCoordPos = Toolbox::findCoordPos(sf::Vector2i(mCamera.getTileView().getCenter().x, 0), window);
		window.setView(mCamera.getSceneryView());
		sf::Vector2f sceneViewCoordPos = Toolbox::findCoordPos(sf::Vector2i(tileViewCoordPos.x, 0), window);
		mLayerHandler.moveBackgroundVertical(window, mCamera, sceneViewCoordPos, tileViewCoordPos);
		mLayerHandler.updateHud(mCamera.getTileView().getCenter(), tileViewCoordPos);
	}
	if (mLevelState == "Reset") {
		resetLevel(window);
	}
	if (mLevelState == "Dialogue") {
		Dialoguehandler::getInstance().updateDialogue();
		if (Dialoguehandler::getInstance().isInDialogue == false)
			mLevelState = "ZoomedOut";
	}
}

void Throat::render(sf::RenderWindow &window) {
	window.clear();

	// Change view to sceneryView containing background, HUD and other estetic scene objects
	window.setView(mCamera.getSceneryView());
	mLayerHandler.renderBackground(window);

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
	if (mLevelState == "Dialogue") {
		Dialoguehandler::getInstance().renderDialogue(window);

	}

	window.display();
}

void Throat::loadLevel() {
	Toolbox::loadTextures(mMapName);
	Toolbox::copyLevelBounds(mLevelBounds);
	Toolbox::copyCurrentLevelName(mMapName);

	mMapGenerator.loadMap(mMapPath, this);

	mLifeTexture.loadFromImage(Toolbox::getTexture(Toolbox::LIFETEXTURE));
	mLifeSprite.setTexture(mLifeTexture);
	mLifeSprite.setScale(1.5, 1.5);
	mLayerHandler.addLifeSprite(mLifeSprite);

	mBackgroundTexture.loadFromImage(Toolbox::getTexture(Toolbox::THROATBACKGROUND));
	mLayerHandler.addVerticalBackground(mBackgroundTexture);

	mAcidTexture.loadFromImage(Toolbox::getTexture(Toolbox::STOMACHACID));
	mLayerHandler.addForegroundObject(mAcidTexture);

	mLevelState = "Cutscene";

}

void Throat::unloadLevel() {
	//Toolbox::unloadTextures(mMapName);
}

void Throat::triggerEvent(char type){
	switch (type) {
	case 'a':
		Throat::eventA();
		break;
	case 'b':
		Throat::eventB();
		break;

	case 'c':
		Throat::eventC();
		break;

	case 'd':
		Throat::eventD();
		break;

	case 'e':
		Throat::eventE();
		break;

	case 'f':
		Throat::eventF();
		break;

	case 'g':
		Throat::eventG();
		break;

	default:
		break;
	}
}

void Throat::setCurrentMap(std::string &mapname) {
}

void Throat::resetLevel(sf::RenderWindow &window) {
	mCamera.centerOnPlayer(window, 500, 100);
	mMapGenerator.loadMap(mMapPath, this);
	mLevelState = "Cutscene";
}


void Throat::eventA() {
	mLevelState = "Dialogue";
	Dialoguehandler::getInstance().loadDialougehandler('s');
	Dialoguehandler::getInstance().setCurrentDialogue("resources/Dialogues/Stomach Event/EventA.txt");
}
void Throat::eventB() {
	mLevelState = "Dialogue";
	Dialoguehandler::getInstance().loadDialougehandler('s');
	Dialoguehandler::getInstance().setCurrentDialogue("resources/Dialogues/Stomach Event/EventB.txt");
}
void Throat::eventC() {
	mLevelState = "Dialogue";
	Dialoguehandler::getInstance().loadDialougehandler('s');
	Dialoguehandler::getInstance().setCurrentDialogue("resources/Dialogues/Stomach Event/EventC.txt");
}
void Throat::eventD() {
	mLevelState = "Dialogue";
	Dialoguehandler::getInstance().loadDialougehandler('s');
	Dialoguehandler::getInstance().setCurrentDialogue("resources/Dialogues/Stomach Event/EventD.txt");
}
void Throat::eventE() {
	mLevelState = "Dialogue";
	Dialoguehandler::getInstance().loadDialougehandler('s');
	Dialoguehandler::getInstance().setCurrentDialogue("resources/Dialogues/Stomach Event/EventA.txt");
}
void Throat::eventF() {
	mLevelState = "Dialogue";
	Dialoguehandler::getInstance().loadDialougehandler('s');
	Dialoguehandler::getInstance().setCurrentDialogue("resources/Dialogues/Stomach Event/EventA.txt");
}

void Throat::eventG() {
	mLevelState = "Dialogue";
	Dialoguehandler::getInstance().loadDialougehandler('s');
	Dialoguehandler::getInstance().setCurrentDialogue("resources/Dialogues/Stomach Event/EventA.txt");
}