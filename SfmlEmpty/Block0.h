#pragma once

#include <SFML\System.hpp>
#include "Terrain.h"
#include "Animations.h"
#include <vector>

class Block0 : public Terrain{
public:
	typedef std::vector<sf::Sprite*> TileDecs;
	virtual ~Block0();
	virtual Terrain::TERRAINTYPE getType(){ return Terrain::BLOCK0; }
	static Terrain* createBlock0(sf::Vector2f pos, char type, char type1);
	virtual void render(sf::RenderWindow &window);
	virtual void update();
	virtual sf::Vector2f getPos(){ return mSprite.getPosition(); }
	virtual sf::Vector2f getOffset(){ return mSpriteOffset; }
	virtual float getWidth(){ return mSprite.getGlobalBounds().width; }
	virtual float getHeight(){ return mSprite.getGlobalBounds().height; }
	virtual sf::Sprite getSprite(){ return mSprite; }
	virtual bool isOnScreen(){ return mIsOnScreen; }
	virtual void setPos(sf::Vector2f newPos);
	virtual void setScale(sf::Vector2f newScale){ mSprite.setScale(newScale); }
	virtual char getTileType(){ return mTileType; }
	virtual void trigger() {}
	virtual bool getIsAlive() { return mIsAlive; }

private:
	Block0(sf::Vector2f pos, char type, char type1);

	void setTexture(char type);
	void createDecorations(char type1);

	sf::Texture mTexture;
	sf::Sprite mSprite;
	sf::Vector2f mSpriteOffset;

	char mTileType;

	TileDecs mTileDecorations;

	bool mIsOnScreen = true;
	bool mIsAlive = true;
};

