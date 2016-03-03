#pragma once

#include "Entity.h"
#include "Abstracthandler.h"
#include <vector>

class Entityhandler : public Abstracthandler {
public:
	typedef std::vector<Entity*> Entities;
	static Entityhandler& getInstance();

	virtual ~Entityhandler();
	virtual void add(sf::Vector2f pos, char id, char type, char layer);
	virtual void render(sf::RenderWindow &window);
	virtual void update();
	virtual void clear();
	virtual void getVector(char id);
	Entities& getEntities() { return mEntities; }

	/*void addEntity(Entity* entity);
	void renderEntities(sf::RenderWindow &window);
	void updateEntities();
	
	void bringOutTheDead();
	Entities& getEntities(){ return mEntities; }
	
	void addVector();
	void clear();
	void gameOver();
	int getPlayerLife();

	bool isPlayerAlive();

	~Entityhandler();*/
private:
	Entityhandler();
	void internalClear();

	Entities mEntities;
};
