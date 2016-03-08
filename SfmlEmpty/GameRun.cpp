#include "GameRun.h"

GameRun::GameRun(std::string &levelDirectory, std::string &levelName){
	//mStomach.getInstance();
	mCurrentLevel = &Stomach::getInstance();
	//mCurrentLevel = &Stomach::getInstance();
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
	//mStomach.update(window);
}

void GameRun::render(sf::RenderWindow &window){
	mCurrentLevel->render(window);
	//mStomach.render(window);

}

void GameRun::loadLevel(){
	mCurrentLevel->loadLevel();
	//mStomach.loadLevel();
}
