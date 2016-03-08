#pragma once

#include "Terrain.h"
#include "AddObjectsDuringGame.h"

class MeatballSpawner : public Terrain {
public:

	virtual ~MeatballSpawner();
	virtual TERRAINTYPE getType() { return Terrain::MEATBALLSPAWNER; }
	static Terrain* createMeatballSpawner(sf::Vector2f pos);
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
	MeatballSpawner(sf::Vector2f pos);

	void setTexture();
	void spawnMeatball();

	sf::Texture mTexture;
	sf::Sprite mSprite;
	sf::Vector2f mSpriteOffset;
	sf::Clock mClock;

	char mTileType;
	float mSpawnRate;
	bool mIsOnScreen = true;
	AddObjectsDuringGame& mAddObjectsDuringGame;

};

