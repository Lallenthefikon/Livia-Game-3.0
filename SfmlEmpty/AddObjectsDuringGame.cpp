#include "AddObjectsDuringGame.h"



AddObjectsDuringGame::AddObjectsDuringGame():
	mEntityHandler(Entityhandler::getInstance()),
	mTerrainHandler(Terrainhandler::getInstance()){
}


AddObjectsDuringGame::~AddObjectsDuringGame() {
}

AddObjectsDuringGame& AddObjectsDuringGame::getInstance() {
	static AddObjectsDuringGame addObjectsDuringGame;
	return addObjectsDuringGame;
}

void AddObjectsDuringGame::createPlayer(sf::Vector2f pos) {
}

void AddObjectsDuringGame::createWorm(sf::Vector2f pos) {
}

void AddObjectsDuringGame::createAcidMonster(sf::Vector2f pos) {
}

void AddObjectsDuringGame::createMeatball(sf::Vector2f pos) {
	mEntityHandler.addEntity(Factory::createMeatball(pos));
}

void AddObjectsDuringGame::createBlock0(sf::Vector2f pos, char type) {
}

void AddObjectsDuringGame::createBlock0WallJump(sf::Vector2f pos, char type) {
}

void AddObjectsDuringGame::createSpikes(sf::Vector2f pos, char type) {
}

void AddObjectsDuringGame::createGoal(sf::Vector2f pos) {
}

void AddObjectsDuringGame::createMeatballSpawner(sf::Vector2f pos) {
}

void AddObjectsDuringGame::createCollisionBlock(sf::Vector2f pos) {
}

void AddObjectsDuringGame::createDialogue(sf::Vector2f pos) {
}

void AddObjectsDuringGame::createDecoration(sf::Vector2f pos, char id, char layer) {
}
