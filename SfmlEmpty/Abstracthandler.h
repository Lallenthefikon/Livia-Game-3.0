#pragma once

#include <SFML\Graphics.hpp>
#include "Factory.h"

class Terrain;
class Entity;

class Abstracthandler {
public:
	typedef std::vector<Entity*> Entities;
	typedef std::vector<Terrain*> Terrains;

	Abstracthandler();
	virtual ~Abstracthandler();
	virtual void add(sf::Vector2f pos, char id, char type = '0', char layer = '0') = 0;
	virtual void render(sf::RenderWindow &window) = 0;
	virtual void update() = 0;
	virtual void clear() = 0;
};

