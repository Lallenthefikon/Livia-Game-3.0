#pragma once

#include "Entity.h"
#include <vector>

class Entityhandler{
public:
	typedef std::vector<Entity*> Entities;
	static Entityhandler& getInstance();

	void addEntity(Entity* entity);
	void renderEntities(sf::RenderWindow &window);
	void updateEntities(float &frameTime);
	
	void bringOutTheDead();
	Entities& getEntities(){ return mEntities; }
	
	void addVector();
	void clear();
	void gameOver();
	int getPlayerLife();

	bool isPlayerAlive();

private:
	Entityhandler();
	~Entityhandler();
	void internalClear();
	
	Entities mEntities;
	sf::Vector2f mGravity;
};
