#include "GameLoop.h"
#include <iostream>

GameLoop::GameLoop():
mCurrentLevelDirectory("resources/maps/mMap0.txt"),
mCurrentLevelName("Stomach"),
mWindow(sf::VideoMode::getDesktopMode(), "Livia 2.0.2 V.2"),
mStomachMusic(Toolbox::getMusic(Toolbox::SOUNDKEY::STOMACHMUSIC)){
	mWindow.setVerticalSyncEnabled(false);
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
		mCurrentState = GameRun::getInstance(mCurrentLevelDirectory, mCurrentLevelName);
		mCurrentState->loadLevel();
		
	}
	else if (mapEditing){
		mCurrentState = MapEditor::getInstance(mCurrentLevelDirectory, mCurrentLevelName);
		mCurrentState->loadLevel();
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
	mWindow.setFramerateLimit(60);

	mStomachMusic.setVolume(25);
	mStomachMusic.setLoop(true);
	mStomachMusic.play();

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
	mCurrentState->update(mWindow, mTimeElapsed);
}

void GameLoop::render(){
	mCurrentState->render(mWindow);	
}

void GameLoop::calcTimeElapsedAndFPS(sf::Clock &clock){
	mTimeElapsed = clock.restart().asSeconds();
	FPS = 1.f / mTimeElapsed;
	//std::cout << FPS << " " << mTimeElapsed << std::endl;
}