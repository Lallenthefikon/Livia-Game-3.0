#pragma once

#include "Terrain.h"
#include "Toolbox.h"
#include <string>

class Dialogue : public Terrain {
public:
	virtual ~Dialogue();
	virtual TERRAINTYPE getType() { return Terrain::DIALOGUE; }
	static Dialogue* createDialogue();
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

	sf::FloatRect bounds;
	std::vector<std::string> pages;
private:
	Dialogue();

	void setTexture();
	

	
	sf::Texture mTexture;
	sf::Sprite mSprite;
	sf::Vector2f mSpriteOffset;

	char mTileType;

	bool mIsOnScreen = true;
};

