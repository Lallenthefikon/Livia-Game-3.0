#include "GameRun.h"

GameRun::GameRun(std::string &levelDirectory, std::string &levelName){
	mCurrentLevel = &Hub::getInstance();
	setCurrentLevel(levelDirectory, levelName);
}

GameRun::~GameRun(){
}

GameRun* GameRun::getInstance(std::string &levelDirectory, std::string &levelName){
	static GameRun gamerun(levelDirectory, levelName);
	return &gamerun;
}

void GameRun::update(sf::RenderWindow &window){
	mCurrentLevel->update(window);
}

void GameRun::render(sf::RenderWindow &window){
	mCurrentLevel->render(window);
}

void GameRun::loadLevel(){
	mCurrentLevel->loadLevel();
}

void GameRun::changeLevel(std::string levelName){
	if (levelName == "Hub") {
		mCurrentLevel = &Hub::getInstance();
	}
	else if(levelName == "Stomach"){
		mCurrentLevel = &Stomach::getInstance();
	}
	else if (levelName == "Throat") {
		mCurrentLevel = &Throat::getInstance();
	}
	else if (levelName == "Mouth") {
		mCurrentLevel = &Mouth::getInstance();
	}
	else if (levelName == "Intestine"){
		mCurrentLevel = &Intestine::getInstance();
	}
	loadLevel();
}