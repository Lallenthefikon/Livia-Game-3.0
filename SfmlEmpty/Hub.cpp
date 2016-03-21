#include "Hub.h"
#include <iostream>

Hub::Hub() :
	// Initiate singleton classes
	//mBackground(),
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

	mMapName("Hub"),
	mMapPath("resources/maps/mMap0.txt"),
	mLevelState("Center"),

	mZoomedOut(false),
	mLevelBounds(0.f, 0.f, 15000.f, 12300.f) {

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

	mBackgroundTexture.loadFromImage(Toolbox::getTexture(Toolbox::HUBBACKGROUND));
	mLayerHandler.addHorizontalBackground(mBackgroundTexture);

	//mAcidTexture.loadFromImage(Toolbox::getTexture(Toolbox::STOMACHACID));
//	mLayerHandler.addForegroundObject(mAcidTexture);

	//mMiddlegroundTexture.loadFromImage(Toolbox::getTexture(Toolbox::STOMACHMIDDLEGROUND));
	//mLayerHandler.addMiddleground(mMiddlegroundTexture);
	//mLayerHandler.addMiddleground(mAcidTexture);
	//mLayerHandler.addAcid(mAcidTexture);

	mLevelMusic.stopAllMusic();

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
		if (gEvent.key.code == sf::Keyboard::R)
			resetLevel(window);
	}

	mLevelMusic.playMusic(LevelMusic::HUBMUSIC);

	// Updates independent of state
	if (!Toolbox::getPlayerIsAlive()) {
		resetLevel(window);
	}
	// Updates depending on state
	if (mLevelState == "Center") {
		mCamera.updateHubCam(window, mLevelState);
		mLevelState = "Standard";
	}
	if (mLevelState == "Standard") {
		mCamera.updateHubCam(window, mLevelState);

		mEntityHandler->update();
		mTerrainHandler->update();
		mCollisionHandler.checkCollision(mEntityHandler->getEntities(), mTerrainHandler->getTerrains(), mTerrainHandler->getCollisionTerrains());
		mEntityHandler->bringOutTheDead();
	

		window.setView(mCamera.getTileView());
		sf::Vector2f tileViewCoordPos = Toolbox::findCoordPos(sf::Vector2i(mCamera.getTileView().getCenter().x, 0), window);
		window.setView(mCamera.getSceneryView());
		sf::Vector2f sceneViewCoordPos = Toolbox::findCoordPos(sf::Vector2i(tileViewCoordPos.x, 0), window);
		//mLayerHandler.moveStationaryBackground(window, mCamera, sceneViewCoordPos, tileViewCoordPos);
		//mLayerHandler.moveStationaryForeground(window, mCamera, sceneViewCoordPos, tileViewCoordPos);
		mLayerHandler.moveBackgroundHorizontal(window, mCamera, sceneViewCoordPos, tileViewCoordPos);
		/*mLayerHandler.moveStationaryForeground(window, mCamera, sceneViewCoordPos, tileViewCoordPos);
		mLayerHandler.moveMiddleground(window, mCamera, sceneViewCoordPos, tileViewCoordPos);*/
		mLayerHandler.updateHud(mCamera.getTileView().getCenter(), tileViewCoordPos);

		checkIfNewMap();
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

void Hub::render(sf::RenderWindow &window) {
	window.clear();

	// Change view to sceneryView containing background, HUD and other estetic scene objects
	window.setView(mCamera.getSceneryView());
	mLayerHandler.renderBackground(window);

	// Middleground
	//mLayerHandler.renderMiddleground(window);

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

void Hub::loadLevel() {
	Toolbox::copyCurrentLevelName(mMapName);
	Toolbox::copyCurrentLevelDirectory(mMapPath);
	Toolbox::loadTextures(mMapName);
	mMapGenerator.loadMap(mMapPath, this);
	mLayerHandler.addHorizontalBackground(mBackgroundTexture);
	mLevelState = "Center";

}

void Hub::unloadLevel() {
	//Toolbox::unloadTextures(mMapName);
}

void Hub::triggerEvent(char type){
	switch (type) {
	case 'a':
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			mEventA = true;
		break;
	case 'b':
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			mEventB = true;
		break;

	case 'c':
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			mEventC = true;
		break;

	case 'd':
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			mEventD = true;
		break;

	case 'e':
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			mEventE = true;
		break;

	case 'f':
		Hub::eventF();
		break;

	case 'g':
		Hub::eventG();
		break;

	default:
		break;
	}
}

void Hub::setCurrentMap(std::string &mapname) {
}

void Hub::resetLevel(sf::RenderWindow &window) {
	mCamera.centerOnPlayer(window, 0, -300);
	mMapGenerator.loadMap(mMapPath, this);
	mLevelState = "Center";
}

void Hub::eventA() {
	Hub::stopAllMusic();
	GameRun::getInstance(std::string(""), std::string(""))->changeLevel("Stomach");
}
void Hub::eventB() {
	Hub::stopAllMusic();
	GameRun::getInstance(std::string(""), std::string(""))->changeLevel("Throat");
}
void Hub::eventC() {
	Hub::stopAllMusic();
	GameRun::getInstance(std::string(""), std::string(""))->changeLevel("Mouth");
}
void Hub::eventD() {
	Hub::stopAllMusic();
	GameRun::getInstance(std::string(""), std::string(""))->changeLevel("Intestine");
}
void Hub::eventE() {
	Hub::stopAllMusic();
	GameRun::getInstance(std::string(""), std::string(""))->changeLevel("Hub");
}
void Hub::eventF() {
	mLevelState = "Dialogue";
	Dialoguehandler::getInstance().loadDialougehandler('s');
	Dialoguehandler::getInstance().setCurrentDialogue("resources/Dialogues/Hub Event/EventA.txt");
}

void Hub::eventG() {
	mLevelState = "Dialogue";
	Dialoguehandler::getInstance().loadDialougehandler('s');
	Dialoguehandler::getInstance().setCurrentDialogue("resources/Dialogues/Hub Event/EventA.txt");
}

void Hub::checkIfNewMap(){
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) || mEventA) {
		Hub::eventA();
		mEventA = false;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) || mEventB) {
		Hub::eventB();
		mEventB = false;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) || mEventC) {
		Hub::eventC();
		mEventC = false;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4) || mEventD ) {	
		Hub::eventD();
		mEventD = false;
	}
	else if (mEventE) {
		Hub::eventE();
		mEventE = false;
	}
}

void Hub::stopAllMusic() {
	mLevelMusic.stopAllMusic();
}
