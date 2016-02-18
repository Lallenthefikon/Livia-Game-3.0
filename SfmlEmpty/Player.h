#pragma once

#include <SFML\System.hpp>
#include "Entity.h"

class Player : public Entity{

public:
	enum PLAYERSTATE { JUMPING, IDLE, RUNNING, FALLING, DAMAGED, WALLSTUCK, DEATH };
	enum PLAYERTURNED { TURNEDLEFT, TURNEDRIGHT };

	virtual ~Player();
	virtual Entity::ENTITYTYPE getType(){ return PLAYER; }
	static Entity* createPlayer(sf::Vector2f pos);

	virtual void render(sf::RenderWindow &window);
	virtual void update(float &frameTime);
	virtual void addVector(sf::Vector2f &vector);

	virtual sf::Vector2f getPos(){ return mCollisionBody.getPosition(); }
	virtual sf::Vector2f getVelocity(){ return mVelocity; }
	virtual sf::Vector2f getOffset(){ return mSpriteOffset; }
	virtual float getWidth(){ return mCollisionBody.getLocalBounds().width; }
	virtual float getHeight(){ return mCollisionBody.getLocalBounds().height; }
	virtual sf::Sprite getSprite(){ return mCollisionBody; }
	virtual bool isOnScreen(){ return mIsOnScreen; }
	virtual bool getIsAlive() { return mIsAlive; }
	virtual void entityCollision(Entity* entity, char direction);
	virtual void terrainCollision(Terrain* terrain, char direction);
	virtual void getHit();
	virtual void setPos(sf::Vector2f newPos);
	virtual void setScale(sf::Vector2f newScale){ mSprite.setScale(newScale); }
	virtual int getLife() { return mLife; }
	void blink();

private:

	Player(sf::Vector2f pos);


	void playerInput();
	void lerp();
	void clickOnce(sf::Keyboard::Key key);

	void jump();
	void move();
	void playSoundManually();

	void updateState();
	void updateANI();
	void updateCollision();
	//void checkTerrainTypes();
	void animate();

	void updateTexturepos();

	void playSound(PLAYERSTATE state);
	void stopSound(PLAYERSTATE state);

	// Stats 
	float mJumpSpeedInitial;
	float mJumpSpeedDouble;
	float mJumpSpeedMax;
	float mMaxSpeed;
	float mAcceleration;
	float mWallSlideSpeed;
	

	sf::Sprite mSprite;
	sf::Sprite mCollisionBody;
	sf::Clock mInvulnerableTimer;
	sf::Time mTimeInvulnerable;
	sf::Clock mJumpClockTimer;

	// Animations stuff
	Animations::Textures* mCurrentAnimation;
	int mAnimationIndex,
		mClickOnce,
		mNrOfJumps;
	float mTimerANI,
		mFrameTime;

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