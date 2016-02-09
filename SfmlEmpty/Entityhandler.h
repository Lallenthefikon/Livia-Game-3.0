#pragma once

#include "Entity.h"
#include <vector>

class Entityhandler{
public:
	typedef std::vector<Entity*> Entities;
	static Entityhandler& getInstance();
	void addEntity(Entity* entity);
	void renderEntities(sf::RenderWindow &window);
	void updateEntities();
	Entities& getEntities(){ return mEntities; }
	void addVector();
	void clear();
private:
	Entityhandler();
	~Entityhandler();
	void internalClear();
	Entities mEntities;
	sf::Vector2f mGravity;
};
