#pragma once

#include <SFML\System.hpp>
#include "Terrain.h"

class EditorEventBlock : public Terrain
{
public:
	virtual ~EditorEventBlock();
	virtual Terrain::TERRAINTYPE getType() { return Terrain::EVENT; }
	static Terrain* createEventblock(sf::Vector2f pos, char type);
	virtual void render(sf::RenderWindow &window);
	virtual void update();
	virtual sf::Vector2f getPos() { return mSprite.getPosition(); }
	virtual sf::Vector2f getOffset() { return mSpriteOffset; }
	virtual float getWidth() { return mSprite.getGlobalBounds().width; }
	virtual float getHeight() { return mSprite.getGlobalBounds().height; }
	virtual sf::Sprite getSprite() { return mSprite; }
	virtual bool isOnScreen() { return true; }
	virtual void setPos(sf::Vector2f newPos);
	virtual void setScale(sf::Vector2f newScale) { mSprite.setScale(newScale); }
	virtual char getTileType() { return mTileType; }
	virtual void trigger() {}
	virtual bool getIsAlive() { return mIsAlive; }

private:
	EditorEventBlock(sf::Vector2f pos, char type);

	sf::Texture mTexture;
	sf::Sprite mSprite;
	sf::Vector2f mSpriteOffset;

	char mTileType;
	bool mIsAlive = true;
	sf::Text mTextType;
};


