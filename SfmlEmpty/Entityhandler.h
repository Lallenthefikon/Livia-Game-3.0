#pragma once

#include "Entity.h"
#include "Abstracthandler.h"
#include <vector>

class Entityhandler : public Abstracthandler {
public:
	static Entityhandler* getInstance();

	virtual ~Entityhandler();
	
	/// <summary>
	/// ID: 0 = player, 1 = worm, 2 = acidMonster, 3 = meatball, 4 = extra life, 5 = germ
	/// </summary>
	virtual void add(sf::Vector2f pos, char id, char type = '0', char layer = '0');
	virtual void render(sf::RenderWindow &window);
	virtual void update();
	virtual void clear();

	void renderTummy(sf::RenderWindow &window);

	Entities& getEntities() { return mEntities; }
	
	void bringOutTheDead();
	int getPlayerLife();
	bool isPlayerAlive();
	void stopAllSound();
	void renderAcidMonster(sf::RenderWindow& window);

private:
	Entityhandler();
	void addVector();
	void gameOver();
	void internalClear();
	void sortEntities();

	Entities mEntities;
};
