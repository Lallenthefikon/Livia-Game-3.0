#pragma once
#include "Entity.h"
class ExtraLife : public Entity {
public:
	static Entity* createExtraLife(sf::Vector2f pos);
	virtual ~ExtraLife();
	virtual void render(sf::RenderWindow &window);
	virtual void update();

	virtual ENTITYTYPE getType() { return EXTRALIFE; }
	virtual sf::Vector2f getPos() { return mSprite.getPosition(); }
	virtual sf::Vector2f getOffset() { return mSpriteOffset; }
	virtual float getWidth() { return mSprite.getGlobalBounds().width; }
	virtual float getHeight() { return mSprite.getGlobalBounds().height; }
	virtual sf::Sprite getSprite() { return mSprite; }
	virtual bool isOnScreen() { return mIsOnScreen; }
	virtual bool getIsAlive() { return mIsAlive; }
	virtual void addVector(sf::Vector2f &vector);

	virtual void entityCollision(Entity* entity, char direction);
	virtual void terrainCollision(Terrain* terrain, char direction);
	virtual void blockterrainCollision(BlockTerrain* blockterrain, char direction);

	virtual void getHit();
	virtual void setPos(sf::Vector2f newPos);
	virtual void setScale(sf::Vector2f newScale) { mSprite.setScale(newScale); }
	virtual int getLife() { return 0; }
private:
	ExtraLife(sf::Vector2f pos);

	void animate();

	sf::Sprite mSprite;

	sf::Vector2f mSpriteOffset;

	bool mIsOnScreen = true;
	bool mIsAlive;

	// Animations stuff
	Animations::Textures* mCurrentAnimation;
	int mAnimationIndex;
	float mTimer;
};

