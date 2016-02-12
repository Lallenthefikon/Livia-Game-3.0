#pragma once

#include <SFML\System.hpp>
#include "Entity.h"

class Player : public Entity{

public:
	enum PLAYERSTATE { JUMPING, IDLELEFT, IDLERIGHT, RUNNINGLEFT, RUNNINGRIGHT, FALLING, DAMAGED };

	virtual ~Player();
	virtual Entity::ENTITYTYPE getType(){ return PLAYER; }
	static Entity* createPlayer(sf::Vector2f pos);

	virtual void render(sf::RenderWindow &window);
	virtual void update();
	virtual void addVector(sf::Vector2f &vector);

	virtual sf::Vector2f getPos(){ return mSprite.getPosition(); }
	virtual sf::Vector2f getOffset(){ return mSpriteOffset; }
	virtual float getWidth(){ return mSprite.getLocalBounds().width; }
	virtual float getHeight(){ return mSprite.getLocalBounds().height; }
	virtual sf::Sprite getSprite(){ return mSprite; }
	virtual bool isOnScreen(){ return mIsOnScreen; }
	virtual bool getIsAlive() { return mIsAlive; }
	virtual void entityCollision(Entity* entity, char direction);
	virtual void terrainCollision(Terrain* terrain, char direction);
	virtual void getHit();
	virtual void setPos(sf::Vector2f newPos);
	virtual void setScale(sf::Vector2f newScale){ mSprite.setScale(newScale); }

private:

	Player(sf::Vector2f pos);


	void playerInput();
	void lerp();
	void clickOnce(sf::Keyboard::Key key);

	void updateState();
	void updateANI();
	void updateCollision();
	void animate();

	void playSound(PLAYERSTATE state);

	// Stats 
	float mJumpSpeedFirst;
	float mJumpSpeedSecond;
	float mJumpSpeedMax;
	//float mJumpTimer;
	float mMaxSpeed;
	float mAcceleration;
	

	sf::Sprite mSprite;
	sf::Clock mInvulnerableTime;
	sf::Clock mJumpClockTimer;

	// Animations stuff
	Animations::Textures* mCurrentAnimation;
	int mAnimationIndex,
		mClickOnce,
		mNrOfJumps;
	float mTimerANI;

	sf::Vector2f
		mVelocity,
		mSpriteOffset,
		mVelocityGoal;

	bool mIsOnScreen;
	PLAYERSTATE mState;
	bool mInvulnerable;
	bool mJumpClock;
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

	// Sounds // Niclas
	SoundFX& mSoundFX;

};