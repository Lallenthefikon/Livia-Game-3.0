#pragma once

#include <SFML\System.hpp>
#include "Terrain.h"
#include "Toolbox.h"

class Block0Icy : public Terrain{
public:
	~Block0Icy();
	virtual Terrain::TERRAINTYPE getType() { return Terrain::BLOCK0ICY; }
	static Terrain* createBlock0Icy(sf::Vector2f pos, char type, char type1);
	virtual void render(sf::RenderWindow &window);
	virtual void update();
	virtual sf::Vector2f getPos() { return mSprite.getPosition(); }
	virtual sf::Vector2f getOffset() { return mSpriteOffset; }
	virtual float getWidth() { return mSprite.getGlobalBounds().width; }
	virtual float getHeight() { return mSprite.getGlobalBounds().height; }
	virtual sf::Sprite getSprite() { return mSprite; }
	virtual bool isOnScreen() { return mIsOnScreen; }
	virtual void setPos(sf::Vector2f newPos);
	virtual void setScale(sf::Vector2f newScale) { mSprite.setScale(newScale); }
	virtual char getTileType() { return mTileType; }
	virtual void trigger() {}
	virtual bool getIsAlive() { return mIsAlive; }

private:
	Block0Icy(sf::Vector2f pos, char type, char type1);

	void setTexture(char type);

	sf::Texture mTexture;
	sf::Sprite mSprite;
	sf::Vector2f mSpriteOffset;

	char mTileType;

	bool mIsOnScreen = true;
	bool mIsAlive = true;
};

