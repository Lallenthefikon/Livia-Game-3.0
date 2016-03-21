#include "Stomach.h"
#include <iostream>

Stomach::Stomach() :
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

	// Music
	mLevelMusic(LevelMusic::getInstance()),

mCamera(),

mMapName("Stomach"),
mMapPath("resources/maps/mMap1.txt"),
mLevelState("Cutscene"),

mZoomedOut(false),
	mLevelBounds(0.f, 0.f, 15000.f, 4550.f) {
	//mLayerHandler.addMiddleground(mAcidTexture);
	//mLayerHandler.addAcid(mAcidTexture);

	mLevelMusic.stopAllMusic();

}

Stomach::~Stomach() {
}

Stomach& Stomach::getInstance() {
	static Stomach Stomach;
	return Stomach;
}

void Stomach::update(sf::RenderWindow &window) {
	// Specific event loop for gameRun state
	sf::Event gEvent;
	while (window.pollEvent(gEvent)) {
		if (gEvent.type == sf::Event::Closed)
			window.close();
		if (gEvent.key.code == sf::Keyboard::R)
			resetLevel(window);
	}

	mLevelMusic.playMusic(LevelMusic::STOMACHMUSIC);
	mLevelMusic.playMusic(LevelMusic::STOMACHAMBIANCE);

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
		mLayerHandler.moveMiddleground(window, mCamera, sceneViewCoordPos, tileViewCoordPos, "Top");
		mLayerHandler.updateHud(mCamera.getTileView().getCenter(), tileViewCoordPos);
		updateVertGradiantAlpha();
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
		mLayerHandler.moveBackgroundHorizontal(window, mCamera, sceneViewCoordPos, tileViewCoordPos);
		mLayerHandler.updateHud(mCamera.getTileView().getCenter(), tileViewCoordPos);
	}
	if (mLevelState == "Reset") {
		resetLevel(window);
	}
	if (mLevelState == "Dialogue") {
		if (mDialoguehandler.getFilename() == "resources/Dialogues/Stomach Event/EventB.txt") {
			mAcidAlpha += 1;
			if (mAcidAlpha > 255)
				mAcidAlpha = 255;
			mLayerHandler.updateVertGlowAlpha(mAcidAlpha);
		}
		Dialoguehandler::getInstance().updateDialogue();
		if (Dialoguehandler::getInstance().isInDialogue == false)
			mLevelState = "ZoomedOut";
	}

	if (mSwitchLevelWhenDone && !Dialoguehandler::getInstance().isInDialogue) {
		mSwitchLevelWhenDone = false;
		eventCtriggerd = false;
		GameRun::getInstance(std::string(""), std::string(""))->changeLevel("Throat");
	}

}

void Stomach::render(sf::RenderWindow &window) {
	window.clear();

	// Change view to sceneryView containing background, HUD and other estetic scene objects
	window.setView(mCamera.getSceneryView());
	mLayerHandler.renderBackground(window);

	

	
	// Middleground
	mLayerHandler.renderMiddleground(window);
	if (mEntityHandler->getEntities().back()->getType() == Entity::ACIDMONSTER) {
	mLayerHandler.renderVertGradiant(window);
	}
	
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
	mLayerHandler.renderForeground(window);

	// Dialouge
	if (mLevelState == "Dialogue") {
		Dialoguehandler::getInstance().renderDialogue(window);
	}
	window.display();
}

void Stomach::loadLevel() {
	mLevelMusic.stopAllMusic();
	Texthandler::getInstance().loadTexts();
	Toolbox::copyCurrentLevelName(mMapName);
	Toolbox::copyLevelBounds(mLevelBounds);
	Toolbox::loadTextures(mMapName);
	Dialoguehandler::getInstance().loadDialougehandler('s');
	mMapGenerator.loadMap(mMapPath, this);
	//mLayerHandler.addHorizontalBackground(mBackgroundTexture);


	mVertAcidGradiant.loadFromImage(Toolbox::getTexture(Toolbox::STOMACHMIDDLEGROUND), sf::IntRect(0, 368, 1920, 1080));
	mLayerHandler.addAcidGradiantVertical(mVertAcidGradiant);

	mLifeTexture.loadFromImage(Toolbox::getTexture(Toolbox::LIFETEXTURE));
	mLifeSprite.setTexture(mLifeTexture);
	mLifeSprite.setScale(1.5, 1.5);
	mLayerHandler.addLifeSprite(mLifeSprite);

	mBackgroundTexture.loadFromImage(Toolbox::getTexture(Toolbox::STOMACHBACKGROUND));
	mLayerHandler.addHorizontalBackground(mBackgroundTexture);

	mAcidTexture.loadFromImage(Toolbox::getTexture(Toolbox::STOMACHACID));
	mLayerHandler.addForegroundObject(mAcidTexture);

	mMiddlegroundTexture.loadFromImage(Toolbox::getTexture(Toolbox::STOMACHMIDDLEGROUND),sf::IntRect(0,0, 1920, 363));
	mLayerHandler.addMiddleground(mMiddlegroundTexture, "Top", sf::IntRect(0, 0, 1920, 363));

	mLevelState = "Cutscene";
}

void Stomach::unloadLevel() {
	//Toolbox::unloadTextures(mMapName);
}

void Stomach::triggerEvent(char type) {
	switch (type) {
	case 'a':
		Stomach::eventA();
		break;
	case 'b':
		Stomach::eventB();
		break;

	case 'c':
		Stomach::eventC();
		break;

	case 'd':
		Stomach::eventD();
		break;

	//case 'e':
	//	Stomach::eventE();
	//	break;

	//case 'f':
	//	Stomach::eventF();
	//	break;

	//case 'g':
	//	Stomach::eventG();
	//	break;

	default:
		break;
	}
}

void Stomach::setCurrentMap(std::string &mapname) {
}

void Stomach::resetLevel(sf::RenderWindow &window) {
	eventCtriggerd = false;
	mCamera.centerOnPlayer(window, 500, 100);
	mMapGenerator.loadMap(mMapPath, this);
	mLevelState = "Cutscene";
}

void Stomach::eventA() {
	if (!eventAtriggerd) {
	mLevelState = "Dialogue";
	Dialoguehandler::getInstance().setCurrentDialogue("resources/Dialogues/Stomach Event/EventA.txt");
	eventAtriggerd = true;
}
}
void Stomach::eventB() {
	if (!eventBtriggerd) {
	mLevelState = "Dialogue";
	mAcidAlpha = 0;
	AddObjectsDuringGame::getInstance().createAcidMonster(sf::Vector2f(100, 2550));
	Dialoguehandler::getInstance().setCurrentDialogue("resources/Dialogues/Stomach Event/EventB.txt");
	eventBtriggerd = true;
}
}
void Stomach::eventC() {
	if (eventBtriggerd) {
	if (!eventCtriggerd) {
			AddObjectsDuringGame::getInstance().createAcidMonster(sf::Vector2f(-1400, 2550));
			eventCtriggerd = true;
		}
	}
}
void Stomach::eventD() {
	if (!eventDtriggerd) {
	mLevelState = "Dialogue";
	Dialoguehandler::getInstance().setCurrentDialogue("resources/Dialogues/Stomach Event/EventD.txt");
	eventDtriggerd = true;
}
}
//void Stomach::eventE() {
//		AddObjectsDuringGame::getInstance().createAcidMonster(sf::Vector2f(0, 0));
//}
//void Stomach::eventF() {
//	if (!eventFtriggerd) {
//	mLevelState = "Dialogue";
//	Dialoguehandler::getInstance().setCurrentDialogue("resources/Dialogues/Stomach Event/EventA.txt");
//	eventFtriggerd = true;
//	}
//}
//
//void Stomach::eventG() {
//	if (!eventGtriggerd) {
//	mLevelState = "Dialogue";
//	Dialoguehandler::getInstance().setCurrentDialogue("resources/Dialogues/Stomach Event/EventA.txt");
//		eventGtriggerd = true;
//	}
//}
//
//void Stomach::eventH() {
//	if (!eventHtriggerd) {
//		GameRun::getInstance(std::string(""), std::string(""))->changeLevel("Hub");
//		eventGtriggerd = true;
//	}
//
//}

void Stomach::updateVertGradiantAlpha() {
	if (mEntityHandler->getEntities().back()->getType() == Entity::ACIDMONSTER) {
		float delta = mEntityHandler->getEntities().at(0)->getPos().x -
			(mEntityHandler->getEntities().back()->getPos().x + mEntityHandler->getEntities().back()->getWidth());
		float alpha = 255 - (255 * delta / 3000);
		if (alpha < 0) {
			alpha = 0;
		}
		if (alpha > 255) {
			alpha = 255;
		}
		mLayerHandler.updateVertGlowAlpha(alpha);
	}
}