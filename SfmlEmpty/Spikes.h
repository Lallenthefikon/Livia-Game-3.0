#pragma once

#include <SFML\System.hpp>
#include "Animations.h"
#include "Terrain.h"

class Spikes : public Terrain{
public:
	virtual ~Spikes();
	virtual Terrain::TERRAINTYPE getType(){ return Terrain::SPIKES; }
	static Terrain* createSpikes(sf::Vector2f pos, char type);
	
	virtual void render(sf::RenderWindow &window);
	virtual void update();
	virtual void setPos(sf::Vector2f newPos);

	virtual sf::Vector2f getPos(){ return mCollisionBody.getPosition(); }
	virtual sf::Vector2f getOffset(){ return mSpriteOffset; }
	virtual float getWidth(){ return mCollisionBody.getGlobalBounds().width; }
	virtual float getHeight(){ return mCollisionBody.getGlobalBounds().height; }
	virtual sf::Sprite getSprite(){ return mCollisionBody; }
	virtual bool isOnScreen(){ return mIsOnScreen; }
	virtual void setScale(sf::Vector2f newScale) { mCollisionBody.setScale(newScale); mSprite.setScale(newScale); }
	virtual char getTileType(){ return mTileType; }

private:
	Spikes(sf::Vector2f pos, char type);

	void setRotation(char type);
	void updateTexturepos();
	void animate();
	sf::Sprite mSprite,
		mCollisionBody;
	sf::Vector2f mSpriteOffset;

	sf::Texture mTexture;

	Animations::Textures* mCurrentAnimation;
	int mAnimationIndex;
	float mTimer;


	char mTileType;

	bool mIsOnScreen = true;
};

