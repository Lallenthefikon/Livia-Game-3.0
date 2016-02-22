#pragma once

#include <SFML\System.hpp>
#include "Entity.h"

class Worm : public Entity{
public:
	enum WORMSTATE{CRAWLINGLEFT, CRAWLINGRIGHT, DEATH};
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
	virtual bool getIsAlive(){ return mIsAlive; }
	virtual void addVector(sf::Vector2f &vector);
	virtual void entityCollision(Entity* entity, char direction);
	virtual void terrainCollision(Terrain* terrain, char direction);
	virtual void getHit();
	virtual void setPos(sf::Vector2f newPos);
	virtual void setScale(sf::Vector2f newScale){ mSprite.setScale(newScale); }
	virtual int getLife(){ return mLife; }
	
	
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

	void playSound(WORMSTATE state);
	void stopSound(WORMSTATE state);

	sf::Sprite mSprite;

	// Animimations stuff
	Animations::Textures* mCurrentAnimation;
	Animations::Textures* mWormDyingAnimation;
	int mAnimationIndex;
	float mTimer;

	float mAcceleration;
	float mMaxSpeed;

	sf::Vector2f mSpriteOffset,
		mVelocity,
		mVelocityGoal;

	WORMSTATE mState;
	bool mIsOnScreen;
	bool mIsAlive;
	int mLife;

	

	char mCollisionT;
	char mCollisionB;
	char mCollisionL;
	char mCollisionR;

	Terrain* mCurrentCollisionB;
	Terrain* mCurrentCollisionT;
	Terrain* mCurrentCollisionL;
	Terrain* mCurrentCollisionR;
	
	// Sounds
	SoundFX& mSoundFX;
};

