#include "GameLoop.h"
#include <iostream>

GameLoop::GameLoop() :
	mCurrentLevelDirectory("resources/maps/mMap1.txt"),
	mCurrentLevelName("Hub"),
	mWindow(sf::VideoMode::getDesktopMode(), "Livia is DA DANKEST") {
	mWindow.setVerticalSyncEnabled(false);
	mWindow.setKeyRepeatEnabled(false);
	Toolbox::copyCurrentLevelName(mCurrentLevelName);
	Toolbox::copyCurrentLevelDirectory(mCurrentLevelDirectory);
	updateState();
	mWindow.setVerticalSyncEnabled(true);
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
		mCurrentState = GameRun::getInstance(Toolbox::getCurrentLevelDirectory(), Toolbox::getCurrentLevelName());

	} else if (mapEditing) {
		mCurrentState = MapEditor::getInstance(Toolbox::getCurrentLevelDirectory(), Toolbox::getCurrentLevelName());
	}
	mCurrentState->loadLevel();
	std::cout << "Changed state" << std::endl;
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

	int clickOnce = 0;
	Toolbox::setWindowSize(mWindow);
	sf::Clock clock;

	// Loop
	while (mWindow.isOpen() && !sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		//std::cout << "Level name: " << Toolbox::getCurrentLevelName() << " Level directory: " << Toolbox::getCurrentLevelDirectory() << std::endl;
		manualStateChange(clickOnce);
		manualFPSChange(clickOnce);
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