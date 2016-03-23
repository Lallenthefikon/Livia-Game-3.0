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

	mLevelMusic(LevelMusic::getInstance()),

	mCamera(),

	mMapName("Throat"),
	mMapPath("resources/maps/mMap2.txt"),
	mLevelState("Cutscene"),

	mZoomedOut(false),
	mLevelBounds(0.f, 0.f, 15000.f, 57500.f) {

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
	mLayerHandler.addVerticalBackground(mBackgroundTexture);

	mAcidTexture.loadFromImage(Toolbox::getTexture(Toolbox::STOMACHACID));
	mLayerHandler.addForegroundObject(mAcidTexture);

	//mMiddlegroundTexture.loadFromImage(Toolbox::getTexture(Toolbox::STOMACHMIDDLEGROUND));
	//mLayerHandler.addMiddleground(mMiddlegroundTexture, "Bottom", sf::IntRect(0, 0, 1920, 1080));
	//mLayerHandler.addMiddleground(mAcidTexture);
	//mLayerHandler.addAcid(mAcidTexture);
	
	mLevelMusic.stopAllMusic();

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
		if (gEvent.key.code == sf::Keyboard::R)
			resetLevel(window);
	}

	mLevelMusic.playMusic(LevelMusic::THROATMUSIC);
	
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
		} else {
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
		mLayerHandler.moveStationaryBackground(window, mCamera, sceneViewCoordPos, tileViewCoordPos);
		mLayerHandler.moveStationaryForeground(window, mCamera, sceneViewCoordPos, tileViewCoordPos);
		mLayerHandler.moveMiddleground(window, mCamera, sceneViewCoordPos, tileViewCoordPos, "Top");
		mLayerHandler.updateHud(mCamera.getTileView().getCenter(), tileViewCoordPos);
		updateGradiantAlpha();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
			mLevelMusic.stopAllMusic();
			mEntityHandler->stopAllSound();
			GameRun::getInstance(std::string(""), std::string(""))->changeLevel("Hub");
		}

		if (mSwitchLevelWhenDone && !Dialoguehandler::getInstance().isInDialogue) {
			mSwitchLevelWhenDone = false;
			eventAtriggerd = false;
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

	if (mSwitchLevelWhenDone && !Dialoguehandler::getInstance().isInDialogue) {
		mSwitchLevelWhenDone = false;
		eventBtriggerd = false;
		GameRun::getInstance(std::string(""), std::string(""))->changeLevel("Hub");
	}
}

void Throat::render(sf::RenderWindow &window) {
	window.clear();

	// Change view to sceneryView containing background, HUD and other estetic scene objects
	window.setView(mCamera.getSceneryView());
	mLayerHandler.renderBackground(window);

	// Middleground
	mLayerHandler.renderMiddleground(window);
	mLayerHandler.renderVertGradiant(window);

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
	mEntityHandler->renderAcidMonster(window);

	// Hud
	mLayerHandler.renderHud(window);

	//Foreground
	window.setView(mCamera.getSceneryView());

	// Dialogue
	if (mLevelState == "Dialogue") {
		Dialoguehandler::getInstance().renderDialogue(window);

	}

	window.display();
}

void Throat::loadLevel() {
	mLevelMusic.stopAllMusic();
	Toolbox::loadTextures(mMapName);
	Toolbox::copyLevelBounds(mLevelBounds);
	Toolbox::copyCurrentLevelName(mMapName);
	Toolbox::copyCurrentLevelDirectory(mMapPath);
	Dialoguehandler::getInstance().loadDialougehandler('s');
	mMapGenerator.loadMap(mMapPath, this);

	mVertAcidGradiant.loadFromImage(Toolbox::getTexture(Toolbox::STOMACHMIDDLEGROUND), sf::IntRect(1970, 0, 1920, 1347));
	mLayerHandler.addAcidGradiantVertical(mVertAcidGradiant);

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

void Throat::triggerEvent(char type) {
	switch (type) {
	case 'a':
		Throat::eventA();
		break;
	case 'b':
		Throat::eventB();
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
	if (!eventAtriggerd) {
	mLevelState = "Dialogue";
		Dialoguehandler::getInstance().setCurrentDialogue("resources/Dialogues/Throat Event/EventA.txt");
		eventAtriggerd = true;
	}
}
void Throat::eventB() {
	if (!eventBtriggerd) {
	mLevelState = "Dialogue";
		Dialoguehandler::getInstance().setCurrentDialogue("resources/Dialogues/Throat Event/EventB.txt");
		eventBtriggerd = true;
		mSwitchLevelWhenDone = true;
}
}

void Throat::updateGradiantAlpha() {
	if (mEntityHandler->getEntities().back()->getType() == Entity::ACIDMONSTER) {
		float delta = mEntityHandler->getEntities().at(0)->getPos().x + mEntityHandler->getEntities().at(0)->getHeight() -
			mEntityHandler->getEntities().back()->getPos().y;
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
