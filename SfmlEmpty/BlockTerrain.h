#pragma once

#include "Terrain.h"

class BlockTerrain : public Terrain{

public:
	typedef std::vector<Terrain*> Terrains;
	typedef std::vector<Terrains*> Terrains2D;
	BlockTerrain();
	virtual ~BlockTerrain();
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
	

	virtual void addBlockTerrain(Terrain* blockTerrain, bool newX) = 0;
	virtual Terrain* getBlock(int xIndex, int yIndex) = 0;
	virtual Terrains2D& getBlocks() = 0;
	virtual Terrain::TERRAINTYPE getType(sf::Vector2f pos, float length, char direction) = 0;
	virtual char getTileType(sf::Vector2f pos, float length, char direction) = 0;
};

