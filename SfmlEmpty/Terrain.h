#pragma once

#include <SFML\Graphics.hpp>
#include "Toolbox.h"

class Terrain{
public:
	enum TERRAINTYPE { BLOCK0ICY, BLOCK0, BLOCK0WALLJUMP, SPIKES, BLOCKGOAL, COLLISIONBLOCK, EVENT, MEATBALLSPAWNER };
	Terrain();
	virtual ~Terrain();
	virtual TERRAINTYPE getType() = 0;
	virtual void render(sf::RenderWindow &window) = 0;
	virtual void update() = 0;
	virtual sf::Vector2f getPos() = 0;
	virtual sf::Vector2f getOffset() = 0;
	virtual float getWidth() = 0;
	virtual float getHeight() = 0;
	virtual sf::Sprite getSprite() = 0;
	virtual bool isOnScreen() = 0;
	virtual void setPos(sf::Vector2f newPos) = 0;
	virtual void setScale(sf::Vector2f newScale) = 0;
	virtual char getTileType() = 0;
	virtual void trigger() = 0;
	virtual bool getIsAlive() = 0;
};

