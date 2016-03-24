#include "GameLoop.h"
#include <iostream>

GameLoop::GameLoop() :
	mCurrentLvlIndex(0),
	mWindow(sf::VideoMode::getDesktopMode(), "The Six Minds of Livia") {
	mCurrentLevelDirectory = getLevelFilename(mCurrentLvlIndex);
		mCurrentLevelName = getMapName(mCurrentLvlIndex);
	mWindow.setVerticalSyncEnabled(true);
	mWindow.setKeyRepeatEnabled(false);
	Toolbox::copyCurrentLevelName(mCurrentLevelName);
	Toolbox::copyCurrentLevelDirectory(mCurrentLevelDirectory);
	updateState();
}

GameLoop::~GameLoop() {
}

void GameLoop::switchState() {
	if (!gameRunning) {
		gameRunning = true;
		mapEditing = false;
	} else if (!mapEditing) {
		mapEditing = true;
		gameRunning = false;
	}
}

void GameLoop::updateState() {
	if (gameRunning) {
		mCurrentState = GameRun::getInstance(mCurrentLevelDirectory, mCurrentLevelName);
		//mCurrentState->setCurrentLevel(mCurrentLevelDirectory, mCurrentLevelName);

	} else if (mapEditing) {
		mCurrentState = MapEditor::getInstance(mCurrentLevelDirectory, mCurrentLevelName);
		//mCurrentState->setCurrentLevel(mCurrentLevelDirectory, mCurrentLevelName);
	}
	mCurrentState->loadLevel();
	//std::cout << "Changed state" << std::endl;
}

void GameLoop::manualStateChange(int &i) {
	// Switches between the different states
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
		i++;
	} else i = 0;

	// Makes sure button acts as if pressed once
	if (i == 1) {
		switchState();
		updateState();
	}
}

void GameLoop::manualFPSChange(int &i) {
	// Switches between the different states
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
		i++;
		//std::cout << i << std::endl;
	} else i = 0;

	// Makes sure button acts as if pressed once
	if (i == 1) {
		switchFPS();
		updateFPS();
	}
}

void GameLoop::manualMapDirectoryChange(int & i){
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
		i++;
	}
	else i = 0;

	// Makes sure button acts as if pressed once
	if (i == 1) {
		mCurrentLvlIndex += 1;
		if (mCurrentLvlIndex == 4)
			mCurrentLvlIndex = 0;
		mCurrentLevelDirectory = getLevelFilename(mCurrentLvlIndex);
		mCurrentLevelName = getMapName(mCurrentLvlIndex);
		Toolbox::copyCurrentLevelName(mCurrentLevelName);
		Toolbox::copyCurrentLevelDirectory(mCurrentLevelDirectory);
		switchState();
		updateState();
	}
}

std::string GameLoop::getLevelFilename(int i){
	switch (i) {
	case 0:
		return "resources/maps/mMap0.txt";
	case 1:
		return "resources/maps/mMap1.txt";
	case 2:
		return "resources/maps/mMap2.txt";
	case 3:
		return "resources/maps/mMap3.txt";
	case 4:
		return "resources/maps/mMap4.txt";
	default:
		break;
	}
	return "resources/maps/mMap0.txt";
}

std::string GameLoop::getMapName(int i){
	switch (i) {
	case 0:
		return "Hub";
	case 1:
		return "Stomach";
	case 2:
		return "Throat";
	case 3:
		return "Mouth";
	case 4:
		return "Intestine";
	default:
		break;
	}
	return "Hub";
}

void GameLoop::switchFPS() {
	if (!highFPS) {
		highFPS = true;
		lowFPS = false;
	} else if (!lowFPS) {
		lowFPS = true;
		highFPS = false;
	}
}

void GameLoop::updateFPS() {
	if (highFPS) {
		mWindow.setFramerateLimit(60);
	} else if (lowFPS) {
		mWindow.setFramerateLimit(30);
	}
}

void GameLoop::run() {
	mWindow.setFramerateLimit(60);
	Toolbox::setWindowSize(mWindow);
	sf::Clock clock;

	// Loop
	while (mWindow.isOpen() && !sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		//std::cout << "Level name: " << Toolbox::getCurrentLevelName() << " Level directory: " << Toolbox::getCurrentLevelDirectory() << std::endl;
		//manualStateChange(clickOnce0);
		//manualFPSChange(clickOnce1);
		//manualMapDirectoryChange(clickOnce2);
		update();
		render();
		calcTimeElapsedAndFPS(clock);
	}
}

void GameLoop::update() {
	mCurrentState->update(mWindow);
}

void GameLoop::render() {
	mCurrentState->render(mWindow);
}

void GameLoop::calcTimeElapsedAndFPS(sf::Clock &clock) {
	mFrameTime = clock.restart().asSeconds();
	Toolbox::copyFrameTime(mFrameTime);
	//std::cout << FPS << " " << mTimeElapsed << std::endl;
}