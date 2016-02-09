#pragma once

#include <SFML\System.hpp>
#include "Terrain.h"
#include "Toolbox.h"

class Block0 : public Terrain{
public:
	virtual ~Block0();
	virtual Terrain::TERRAINTYPE getType(){ return Terrain::BLOCK0; }
	static Terrain* createBlock0(sf::Vector2f pos, char type);
	virtual void render(sf::RenderWindow &window);
	virtual void update();
	virtual sf::Vector2f getPos(){ return mSprite.getPosition(); }
	virtual sf::Vector2f getOffset(){ return mSpriteOffset; }
	virtual float getWidth(){ return mSprite.getGlobalBounds().width; }
	virtual float getHeight(){ return mSprite.getGlobalBounds().height; }
	virtual sf::Sprite getSprite(){ return mSprite; }
	virtual bool isOnScreen(){ return mIsOnScreen; }

private:
	Block0(sf::Vector2f pos, char type);

	void setTexture(char type);

	sf::Texture mTexture;
	sf::Sprite mSprite;
	sf::Vector2f mSpriteOffset;
	bool mIsOnScreen = true;
};

