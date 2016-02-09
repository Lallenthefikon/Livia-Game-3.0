#include "GameLoop.h"
#include <iostream>



GameLoop::GameLoop():
mCurrentMap("resources/maps/mMap0.txt"),
mWindow(sf::VideoMode::getDesktopMode(), "Livia 2.0.2 V.2"),
mAmbienceBuffer(),
mAmbienceSound() {
	mWindow.setVerticalSyncEnabled(true);
	mWindow.setKeyRepeatEnabled(false);
	updateState();
}

GameLoop::~GameLoop(){
}

void GameLoop::switchState(){
	if (!gameRunning){
		gameRunning = true;
		mapEditing = false;
		return;
	}
	else if (!mapEditing){
		mapEditing = true;
		gameRunning = false;
	}
}

void GameLoop::updateState(){
	if (gameRunning){
		mCurrentState = GameRun::getInstance(mCurrentMap);
		mCurrentState->loadMap();
	}
	else if (mapEditing){
		mCurrentState = MapEditor::getInstance(mCurrentMap);
		mCurrentState->loadMap();
	}
}

void GameLoop::manualStateChange(int &i){
	// Switches between the different states
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)){
		i++;
		//std::cout << i << std::endl;
	}
	else i = 0;

	// Makes sure button acts as if pressed once
	if (i == 1){
		switchState();
		updateState();
	}
}

void GameLoop::run(){
	
	mAmbienceBuffer.loadFromFile("resources/sounds/Ambient_Stomach.ogg");
	mAmbienceSound.setBuffer(mAmbienceBuffer);
	mAmbienceSound.setLoop(true);
	mAmbienceSound.play();

	int clickOnce = 0;
	

	sf::Clock clock;

	// Loop
	while (mWindow.isOpen() && !sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
		manualStateChange(clickOnce);
		update();
		render();
		calcTimeElapsedAndFPS(clock);
	}
}

void GameLoop::update(){
	mCurrentState->update(mWindow);
}

void GameLoop::render(){
	mCurrentState->render(mWindow);	
}

void GameLoop::calcTimeElapsedAndFPS(sf::Clock &clock){
	mTimeElapsed = clock.restart().asMilliseconds();
	FPS = 1000.f / mTimeElapsed;
}