#pragma once

#include "Factory.h"
#include "Abstracthandler.h"
#include "HandlerFactory.h"

class AddObjectsDuringGame {
public:
	static AddObjectsDuringGame& getInstance();

	void createPlayer(sf::Vector2f pos);
	void createWorm(sf::Vector2f pos);
	void createAcidMonster(sf::Vector2f pos);
	void createMeatball(sf::Vector2f pos);

	void createBlock0(sf::Vector2f pos, char type);
	void createBlock0WallJump(sf::Vector2f pos, char type);
	void createSpikes(sf::Vector2f pos, char type);
	void createGoal(sf::Vector2f pos);
	void createMeatballSpawner(sf::Vector2f pos);
	void createCollisionBlock(sf::Vector2f pos);
	~AddObjectsDuringGame();
private:
	AddObjectsDuringGame();
	Abstracthandler* mEntityHandler;
	Abstracthandler* mTerrainHandler;
};