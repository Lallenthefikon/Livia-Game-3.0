#pragma once

#include <SFML\System.hpp>
#include "Terrain.h"
#include "Toolbox.h"

class Spikes : public Terrain{
public:
	virtual ~Spikes();
	virtual Terrain::TERRAINTYPE getType(){ return Terrain::SPIKES; }
	static Terrain* createSpikes(sf::Vector2f pos, char type);
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

private:
	Spikes(sf::Vector2f pos, char type);

	void setRotation(char type);
	sf::Sprite mSprite;
	sf::Vector2f mSpriteOffset;

	sf::Texture mTexture;

	char mTileType;

	bool mIsOnScreen = true;
};
