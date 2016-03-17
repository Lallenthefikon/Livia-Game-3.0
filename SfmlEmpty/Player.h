#pragma once

#include <SFML\System.hpp>
#include "Entity.h"


class Player : public Entity{

public:
	enum PLAYERSTATE { JUMPING, IDLE, RUNNING, FALLING, DAMAGED, WALLSTUCK, DEATH, FALLDEATH, DROWN, LANDED };
	enum PLAYERTURNED { TURNEDLEFT, TURNEDRIGHT };
	enum BLINKSTATES { BLINKIN, BLINKOUT };

	virtual ~Player();
	virtual Entity::ENTITYTYPE getType(){ return PLAYER; }
	static Entity* createPlayer(sf::Vector2f pos);

	virtual void render(sf::RenderWindow &window);
	virtual void update();
	virtual void addVector(sf::Vector2f &vector);

	virtual void entityCollision(Entity* entity, char direction);
	virtual void terrainCollision(Terrain* terrain, char direction);
	virtual void blockterrainCollision(BlockTerrain* blockterrain, char direction);
	
	virtual sf::Vector2f getPos(){ return mCollisionBody.getPosition(); }
	virtual sf::Vector2f getVelocity(){ return mVelocity; }
	virtual sf::Vector2f getOffset(){ return mSpriteOffset; }
	virtual float getWidth(){ return mCollisionBody.getLocalBounds().width; }
	virtual float getHeight(){ return mCollisionBody.getLocalBounds().height; }
	virtual sf::Sprite getSprite(){ return mCollisionBody; }
	virtual bool isOnScreen(){ return mIsOnScreen; }
	virtual bool getIsAlive() { return mIsAlive; }
	virtual void getHit();
	virtual void setPos(sf::Vector2f newPos);
	virtual void setScale(sf::Vector2f newScale) { mCollisionBody.setScale(newScale); mSprite.setScale(newScale); }
	virtual int getLife() { return mLife; }
	void invulnerableBlink();
	void checkPlayerWithinBounds();

private:

	Player(sf::Vector2f pos);

	void playerInput();
	void lerp();

	void jump();
	void move();
	void playSoundManually();

	void updateState();
	void updateANI();
	void updateCollisionForce();
	void updateCollision();
	void addForces();
	void animate();

	void updateTexturepos();

	void playSound(PLAYERSTATE state);
	void stopSound(PLAYERSTATE state);

	// Stats 
	float mJumpSpeedInitial;
	float mJumpSpeedDouble;
	float mJumpSpeedMax;
	float mMaxSpeed, mIcyMaxSpeed;
	sf::Vector2f mAcceleration, mIcyAcceleration;
	float mWallSlideSpeed;
	float mAirbornAcc, mIcyAirborn;

	

	sf::Sprite mSprite;
	sf::Sprite mCollisionBody;
	sf::Clock mJumpClockTimer;

	int mPlayerTransparency;
	sf::Clock mInvulnerableTimer;
	sf::Time mTimeInvulnerable;
	int mTimesBlinked;

	// Animations stuff
	Animations::Textures* mCurrentAnimation;
	int mAnimationIndex,
		mClickOnce,
		mNrOfJumps;
	float mTimerANI,
		mFrameTime,
		mCurrentAnimationRate;

	sf::Vector2f
		mVelocity,
		mSpriteOffset,
		mVelocityGoal;

	bool mIsOnScreen;
	PLAYERSTATE mState;
	PLAYERTURNED mTurned;
	
	bool mInvulnerable;
	bool mJumpStarted;
	bool mDoubleJumped;
	bool mJumpReleased;
	bool mBlinkOut;
	Terrain::TERRAINTYPE mLastBlockToched;

	// outside Bounds
	bool mAtLeftBorder;
	bool mAtRightBorder;
	bool mFallenOutsideBounds;
	
	bool mIsAlive;
	bool mWin;
	bool mIsInDialogue;
	int mLife;
	bool jumpReleased;

	char mCollisionT;
	char mCollisionB;
	char mCollisionL;
	char mCollisionR;

	BlockTerrain* mCurrentCollisionB;
	BlockTerrain* mCurrentCollisionT;
	BlockTerrain* mCurrentCollisionL;
	BlockTerrain* mCurrentCollisionR;

	// Sounds
	SoundFX& mSoundFX;

	// Text
	sf::Text mText;

	Texthandler& mTextHandler;
};