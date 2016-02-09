#pragma once

#include "Entity.h"
#include <SFML\System.hpp>
#include "Toolbox.h"
#include "Animations.h"
#include "CollisionFuncs.h"

class Worm : public Entity{
public:
	enum WORMSTATE{CRAWLINGLEFT, CRAWLINGRIGHT};
	virtual ~Worm();
	virtual ENTITYTYPE getType(){ return WORM; }
	static Entity* createWorm(sf::Vector2f pos);
	virtual void render(sf::RenderWindow &window);
	virtual void update();
	virtual sf::Vector2f getPos(){ return mSprite.getPosition(); }
	virtual sf::Vector2f getOffset(){ return mSpriteOffset; }
	virtual float getWidth(){ return mSprite.getGlobalBounds().width; }
	virtual float getHeight(){ return mSprite.getGlobalBounds().height; }
	virtual sf::Sprite getSprite(){ return mSprite; }
	virtual bool isOnScreen(){ return mIsOnScreen; }
	virtual void addVector(sf::Vector2f &vector);
	virtual void entityCollision(Entity* entity, char direction);
	virtual void terrainCollision(Terrain* terrain, char direction);
private:
	Worm(sf::Vector2f pos);

	void lerp();
	void addSpeed();

	void updateState();
	void updateANI();
	void updateCollision();
	void animate();

	bool currentCollisionT();
	bool currentCollisionB();
	bool currentCollisionL();
	bool currentCollisionR();

	sf::Sprite mSprite;

	// Animimations stuff
	Animations::Textures* mCurrentAnimation;
	int mAnimationIndex;
	float mTimer;

	float mSpeed;
	float mMaxSpeed;

	sf::Vector2f mSpriteOffset,
		mVelocity,
		mVelocityGoal;

	WORMSTATE mState;
	bool mIsOnScreen;

	char mCollisionT;
	char mCollisionB;
	char mCollisionL;
	char mCollisionR;

	Terrain* mCurrentCollisionB;
	Terrain* mCurrentCollisionT;
	Terrain* mCurrentCollisionL;
	Terrain* mCurrentCollisionR;
};

