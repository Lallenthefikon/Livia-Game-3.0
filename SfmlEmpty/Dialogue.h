#pragma once

#include <SFML\Graphics.hpp>
#include "Animations.h"
#include "Terrain.h"

class Dialogue : public Terrain{
public:
	virtual ~Dialogue();

	virtual Terrain::TERRAINTYPE getType() { return Terrain::BLOCK0; }
	static Dialogue* createDialogue(sf::Vector2f pos);
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

private:
	Dialogue(sf::Vector2f pos);

	sf::Texture mTexture;
	sf::Sprite mSprite;
	sf::Vector2f mSpriteOffset;

	char mTileType;

	bool mIsOnScreen = true;

};

