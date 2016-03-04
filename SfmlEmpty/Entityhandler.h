#pragma once

#include "Entity.h"
#include "Abstracthandler.h"
#include <vector>

class Entityhandler : public Abstracthandler {
public:
	static Entityhandler* getInstance();

	virtual ~Entityhandler();
	
	/// <summary>
	/// ID: 0 = player, 1 = worm, 2 = acidMonster, 3 = meatball
	/// </summary>
	virtual void add(sf::Vector2f pos, char id, char type = '0', char layer = '0');
	virtual void render(sf::RenderWindow &window);
	virtual void update();
	virtual void clear();

	Entities& getEntities() { return mEntities; }
	
	void bringOutTheDead();
	int getPlayerLife();
	bool isPlayerAlive();

private:
	Entityhandler();
	void addVector();
	void gameOver();
	void internalClear();
	void sortEntities();

	Entities mEntities;
};
