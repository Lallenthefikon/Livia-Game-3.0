#include "Intestine.h"
#include <iostream>

Intestine::Intestine() :
	// Initiate singleton classes
	mBackground(),
	mTexture(),

	mEntityHandler(Entityhandler::getInstance()),
	mTerrainHandler(Terrainhandler::getInstance()),

	mMapGenerator(MapGenerator::getInstance()),
	mCollisionHandler(Collisionhandler::getInstance()),
	mLayerHandler(LayerHandler::getInstance()),
	mTextHandler(Texthandler::getInstance()),
	mDecorationhandler(Decorationhandler::getInstance()),
	mDialoguehandler(Dialoguehandler::getInstance()),

	mLevelMusic(LevelMusic::getInstance()),

	mCamera(),

	mMapName("Intestine"),
	mMapPath("resources/maps/mMap4.txt"),
	mLevelState("Cutscene"),

	mZoomedOut(false),
	mLevelBounds(0.f, 0.f, 15000.f, 4230.f) {

	Toolbox::loadTextures(mMapName);
	Toolbox::loadSounds(mMapName);
	Toolbox::loadFonts(mMapName);
	Animations::loadTextures();
	Texthandler::getInstance().loadTexts();
	Toolbox::copyLevelBounds(mLevelBounds);
	Toolbox::copyCurrentLevelName(mMapName);


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

	mLevelMusic.stopAllMusic();

}

Intestine::~Intestine() {
}

Intestine& Intestine::getInstance() {
	static Intestine Intestine;
	return Intestine;
}

void Intestine::update(sf::RenderWindow &window) {
	// Specific event loop for gameRun state
	sf::Event gEvent;
	while (window.pollEvent(gEvent)) {
		if (gEvent.type == sf::Event::Closed)
			window.close();
		if (gEvent.key.code == sf::Keyboard::R)
			resetLevel(window);
	}
	// Updates independent of state
	if (!Toolbox::getPlayerIsAlive()) {
		resetLevel(window);
	}

	mLevelMusic.playMusic(LevelMusic::INTESTINEMUSIC);

	// Updates depending on state
	if (mLevelState == "Cutscene") {
		mCamera.updateStomachCam(window, mLevelState);
		mLevelState = "ZoomOut";
	}
	if (mLevelState == "ZoomOut") {
		if (!mZoomedOut) {
			mCamera.updateStomachCam(window, mLevelState);
			mZoomedOut = true;
		}
		mLevelState = "ZoomedOut";
	}
	if (mLevelState == "ZoomedOut") {

		mCamera.updateStomachCam(window, mLevelState);

		mEntityHandler->update();
		mTerrainHandler->update();
		mCollisionHandler.checkCollision(mEntityHandler->getEntities(), mTerrainHandler->getTerrains(), mTerrainHandler->getCollisionTerrains());
		mEntityHandler->bringOutTheDead();
		mTerrainHandler->bringOutTheDead();

		window.setView(mCamera.getTileView());
		sf::Vector2f tileViewCoordPos = Toolbox::findCoordPos(sf::Vector2i(mCamera.getTileView().getCenter().x, 0), window);
		window.setView(mCamera.getSceneryView());
		sf::Vector2f sceneViewCoordPos = Toolbox::findCoordPos(sf::Vector2i(tileViewCoordPos.x, 0), window);
		mLayerHandler.moveBackground(window, mCamera, sceneViewCoordPos, tileViewCoordPos);
		mLayerHandler.moveStationaryForeground(window, mCamera, sceneViewCoordPos, tileViewCoordPos);
		mLayerHandler.moveMiddleground(window, mCamera, sceneViewCoordPos, tileViewCoordPos);
		mLayerHandler.updateHud(mCamera.getTileView().getCenter(), tileViewCoordPos);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
			mLevelMusic.stopAllMusic();
			mEntityHandler->stopAllSound();
			GameRun::getInstance(std::string(""), std::string(""))->changeLevel("Hub");
		}

	}
	if (mLevelState == "Rising") {

		mCamera.updateStomachCam(window, mLevelState);

		mEntityHandler->update();
		mTerrainHandler->update();
		mCollisionHandler.checkCollision(mEntityHandler->getEntities(), mTerrainHandler->getTerrains(), mTerrainHandler->getCollisionTerrains());
		mEntityHandler->bringOutTheDead();
		mTerrainHandler->bringOutTheDead();
		window.setView(mCamera.getTileView());
		sf::Vector2f tileViewCoordPos = Toolbox::findCoordPos(sf::Vector2i(mCamera.getTileView().getCenter().x, 0), window);
		window.setView(mCamera.getSceneryView());
		sf::Vector2f sceneViewCoordPos = Toolbox::findCoordPos(sf::Vector2i(tileViewCoordPos.x, 0), window);
		mLayerHandler.moveBackground(window, mCamera, sceneViewCoordPos, tileViewCoordPos);
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

void Intestine::render(sf::RenderWindow &window) {
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

	// Foreground
	window.setView(mCamera.getSceneryView());

	// Dialouge
	if (mLevelState == "Dialogue") {
		Dialoguehandler::getInstance().renderDialogue(window);

	}


	window.display();
}

void Intestine::loadLevel() {
	Toolbox::copyCurrentLevelName(mMapName);
	Toolbox::loadTextures(mMapName);
	mMapGenerator.loadMap(mMapPath, this);
	mLevelState = "Cutscene";
}

void Intestine::unloadLevel() {
	//Toolbox::unloadTextures(mMapName);
}

void Intestine::triggerEvent(char type) {
	switch (type) {
	case 'a':
		Intestine::eventA();
		break;
	case 'b':
		Intestine::eventB();
		break;

	case 'c':
		Intestine::eventC();
		break;

	case 'd':
		Intestine::eventD();
		break;

	case 'e':
		Intestine::eventE();
		break;

	case 'f':
		Intestine::eventF();
		break;

	case 'g':
		Intestine::eventG();
		break;

	default:
		break;
	}
}

void Intestine::setCurrentMap(std::string &mapname) {
}

void Intestine::resetLevel(sf::RenderWindow &window) {
	mCamera.centerOnPlayer(window, 500, 100);
	mMapGenerator.loadMap(mMapPath, this);
	mLevelState = "Cutscene";
}

void Intestine::eventA() {
	mLevelState = "Dialogue";
	Dialoguehandler::getInstance().loadDialougehandler('s');
	Dialoguehandler::getInstance().setCurrentDialogue("resources/Dialogues/Stomach Event/EventA.txt");
}
void Intestine::eventB() {
	mLevelState = "Dialogue";
	Dialoguehandler::getInstance().loadDialougehandler('s');
	Dialoguehandler::getInstance().setCurrentDialogue("resources/Dialogues/Stomach Event/EventB.txt");
}
void Intestine::eventC() {
	mLevelState = "Dialogue";
	Dialoguehandler::getInstance().loadDialougehandler('s');
	Dialoguehandler::getInstance().setCurrentDialogue("resources/Dialogues/Stomach Event/EventC.txt");
}
void Intestine::eventD() {
	mLevelState = "Dialogue";
	Dialoguehandler::getInstance().loadDialougehandler('s');
	Dialoguehandler::getInstance().setCurrentDialogue("resources/Dialogues/Stomach Event/EventD.txt");
}
void Intestine::eventE() {
	mLevelState = "Dialogue";
	Dialoguehandler::getInstance().loadDialougehandler('s');
	Dialoguehandler::getInstance().setCurrentDialogue("resources/Dialogues/Stomach Event/EventA.txt");
}
void Intestine::eventF() {
	mLevelState = "Dialogue";
	Dialoguehandler::getInstance().loadDialougehandler('s');
	Dialoguehandler::getInstance().setCurrentDialogue("resources/Dialogues/Stomach Event/EventA.txt");
}

void Intestine::eventG() {
	mLevelState = "Dialogue";
	Dialoguehandler::getInstance().loadDialougehandler('s');
	Dialoguehandler::getInstance().setCurrentDialogue("resources/Dialogues/Stomach Event/EventA.txt");
}