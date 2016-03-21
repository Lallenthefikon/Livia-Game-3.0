#include "Mouth.h"
#include <iostream>

Mouth::Mouth() :
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

	mMapName("Mouth"),
	mMapPath("resources/maps/mMap3.txt"),
	mLevelState("Cutscene"),

	mZoomedOut(false),
	mLevelBounds(0.f, 0.f, 15000.f, 4230.f) {


	Toolbox::loadTextures(mMapName);
	Toolbox::loadSounds(mMapName);
	Toolbox::loadFonts(mMapName);
	Animations::loadTextures();

	Toolbox::copyCurrentLevelName(mMapName);
	Toolbox::copyLevelBounds(mLevelBounds);

	mLifeTexture.loadFromImage(Toolbox::getTexture(Toolbox::LIFETEXTURE));
	mLifeSprite.setTexture(mLifeTexture);
	mLifeSprite.setScale(1.5, 1.5);
	mLayerHandler.addLifeSprite(mLifeSprite);

	

	//mAcidTexture.loadFromImage(Toolbox::getTexture(Toolbox::STOMACHACID));
	//	mLayerHandler.addForegroundObject(mAcidTexture);

	//mMiddlegroundTexture.loadFromImage(Toolbox::getTexture(Toolbox::STOMACHMIDDLEGROUND));
	//mLayerHandler.addMiddleground(mMiddlegroundTexture);
	//mLayerHandler.addMiddleground(mAcidTexture);
	//mLayerHandler.addAcid(mAcidTexture);

	
	Toolbox::copyCurrentLevelName(mMapName);
	Toolbox::copyCurrentLevelDirectory(mMapPath);

	//mLayerHandler.addMiddleground(mAcidTexture);
	//mLayerHandler.addAcid(mAcidTexture);

	mLevelMusic.stopAllMusic();

}

Mouth::~Mouth() {
}

Mouth& Mouth::getInstance() {
	static Mouth Mouth;
	return Mouth;
}

void Mouth::update(sf::RenderWindow &window) {
	// Specific event loop for gameRun state
	sf::Event gEvent;
	while (window.pollEvent(gEvent)) {
		if (gEvent.type == sf::Event::Closed)
			window.close();
		if (gEvent.key.code == sf::Keyboard::R)
			resetLevel(window);
	}

	mLevelMusic.playMusic(LevelMusic::MOUTHMUSIC);

	// Updates independent of state
	if (!Toolbox::getPlayerIsAlive()) {
		resetLevel(window);
	}
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
		mLayerHandler.moveBackgroundHorizontal(window, mCamera, sceneViewCoordPos, tileViewCoordPos);
		mLayerHandler.moveStationaryForeground(window, mCamera, sceneViewCoordPos, tileViewCoordPos);
		mLayerHandler.moveMiddleground(window, mCamera, sceneViewCoordPos, tileViewCoordPos);
		mLayerHandler.updateHud(mCamera.getTileView().getCenter(), tileViewCoordPos);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
			mLevelMusic.stopAllMusic();
			mEntityHandler->stopAllSound();
			GameRun::getInstance(std::string(""), std::string(""))->changeLevel("Hub");
		}

		if (mSwitchLevelWhenDone && !Dialoguehandler::getInstance().isInDialogue) {
			mSwitchLevelWhenDone = false;
			eventGtriggerd = false;
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
		mLayerHandler.moveBackgroundHorizontal(window, mCamera, sceneViewCoordPos, tileViewCoordPos);
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

void Mouth::render(sf::RenderWindow &window) {
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

void Mouth::loadLevel() {
	mLevelMusic.stopAllMusic();

	Texthandler::getInstance().loadTexts();
	Toolbox::copyCurrentLevelName(mMapName);
	Toolbox::copyCurrentLevelDirectory(mMapPath);
	Toolbox::loadTextures(mMapName);
	Dialoguehandler::getInstance().loadDialougehandler('s');
	Toolbox::copyLevelBounds(mLevelBounds);

	mMapGenerator.loadMap(mMapPath, this);
	//mLayerHandler.addHorizontalBackground(mBackgroundTexture);


	mLifeTexture.loadFromImage(Toolbox::getTexture(Toolbox::LIFETEXTURE));
	mLifeSprite.setTexture(mLifeTexture);
	mLifeSprite.setScale(1.5, 1.5);
	mLayerHandler.addLifeSprite(mLifeSprite);

	mBackgroundTexture.loadFromImage(Toolbox::getTexture(Toolbox::MOUTHBACKGROUND));
	mLayerHandler.addHorizontalBackground(mBackgroundTexture);

	mAcidTexture.loadFromImage(Toolbox::getTexture(Toolbox::STOMACHACID));
	mLayerHandler.addForegroundObject(mAcidTexture);

	mMiddlegroundTexture.loadFromImage(Toolbox::getTexture(Toolbox::MOUTHMIDDLEGROUND));
	mLayerHandler.addMiddleground(mMiddlegroundTexture, "Bottom");

	mLevelState = "Cutscene";
}

void Mouth::unloadLevel() {
	//Toolbox::unloadTextures(mMapName);
}

void Mouth::triggerEvent(char type) {
	switch (type) {
	case 'a':
		Mouth::eventA();
		break;
	case 'b':
		Mouth::eventB();
		break;

	case 'c':
		Mouth::eventC();
		break;

	case 'd':
		Mouth::eventD();
		break;

	case 'e':
		Mouth::eventE();
		break;

	case 'f':
		Mouth::eventF();
		break;

	case 'g':
		Mouth::eventG();
		break;

	default:
		break;
	}
}

void Mouth::setCurrentMap(std::string &mapname) {
}

void Mouth::resetLevel(sf::RenderWindow &window) {
	mCamera.centerOnPlayer(window, 500, 100);
	mMapGenerator.loadMap(mMapPath, this);
	mLevelState = "Cutscene";
}

void Mouth::eventA() {
	if (!eventAtriggerd) {
	mLevelState = "Dialogue";
		Dialoguehandler::getInstance().setCurrentDialogue("resources/Dialogues/Mouth Event/EventA.txt");
		eventAtriggerd = true;
}
}
void Mouth::eventB() {
	if (!eventBtriggerd) {
	mLevelState = "Dialogue";
		Dialoguehandler::getInstance().setCurrentDialogue("resources/Dialogues/Mouth Event/EventB.txt");
		eventBtriggerd = true;
}
}
void Mouth::eventC() {
	if (!eventCtriggerd) {
	mLevelState = "Dialogue";
		Dialoguehandler::getInstance().setCurrentDialogue("resources/Dialogues/Mouth Event/EventC.txt");
		eventCtriggerd = true;
}
}
void Mouth::eventD() {
	if (!eventDtriggerd) {
	mLevelState = "Dialogue";
		Dialoguehandler::getInstance().setCurrentDialogue("resources/Dialogues/Mouth Event/EventD.txt");
		eventDtriggerd = true;
	}
}
void Mouth::eventE() {
	if (!eventEtriggerd) {
		mLevelState = "Dialogue";
		Dialoguehandler::getInstance().setCurrentDialogue("resources/Dialogues/Mouth Event/EventE.txt");
		eventEtriggerd = true;
	}
}
void Mouth::eventF() {
	if (!eventFtriggerd) {
	mLevelState = "Dialogue";
		Dialoguehandler::getInstance().setCurrentDialogue("resources/Dialogues/Mouth Event/EventF.txt");
		eventFtriggerd = true;
	}
}

void Mouth::eventG() {
	if (!eventGtriggerd) {
	mLevelState = "Dialogue";
		Dialoguehandler::getInstance().setCurrentDialogue("resources/Dialogues/Mouth Event/EventG.txt");
		eventGtriggerd = true;
		mSwitchLevelWhenDone = true;
	}
}