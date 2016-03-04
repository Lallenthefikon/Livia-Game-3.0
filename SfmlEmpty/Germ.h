#pragma once

#include <SFML\System.hpp>
#include "Entity.h"

class Germ : public Entity{
public:
	enum GERMSTATE {IMWALKINGHERE, DEATH, DAMAGED};
	enum GERMTURNED { TURNEDLEFT, TURNEDRIGHT};
	virtual ~Germ();
	virtual Entity::ENTITYTYPE getType() { return Entity::GERM; }
	static Entity* createGerm(sf::Vector2f pos);

	virtual void render(sf::RenderWindow &window);
	virtual void update();

	virtual sf::Vector2f getPos() { return mCollisionBody.getPosition(); }
	virtual sf::Vector2f getOffset() { return mSpriteOffset; }
	virtual float getWidth() { return mCollisionBody.getGlobalBounds().width; }
	virtual float getHeight() { return mCollisionBody.getGlobalBounds().height; }
	virtual sf::Sprite getSprite() { return mCollisionBody; }
	virtual bool isOnScreen() { return mIsOnScreen; }
	virtual bool getIsAlive() { return mIsAlive; }
	virtual void addVector(sf::Vector2f &vector);

	virtual void entityCollision(Entity* entity, char direction);
	virtual void terrainCollision(Terrain* terrain, char direction);
	virtual void blockterrainCollision(BlockTerrain* blockterrain, char direction);

	virtual void getHit();
	virtual void setPos(sf::Vector2f newPos);
	virtual void setScale(sf::Vector2f newScale) { mCollisionBody.setScale(newScale); mSprite.setScale(newScale); }
	virtual int getLife() { return mLife; }


private:
	Germ(sf::Vector2f pos);

	void updateTexturepos();

	void lerp();
	void addSpeed();
	void updateSpeed();

	void updateState();
	void updateANI();
	void updateCollision();
	void animate();


	void playSound(GERMSTATE state);
	void stopSound(GERMSTATE state);

	sf::Sprite mSprite,
		mCollisionBody;

	// Animations stuff
	Animations::Textures* mCurrentAnimation;
	int mAnimationIndex;
	float mTimer;

	float mAcceleration;
	float mMaxSpeed;


	sf::Vector2f mSpriteOffset,
		mVelocity,
		mVelocityGoal,
		mCollisionBodyOffset;

	GERMSTATE mState;
	GERMTURNED mTurned;
	bool mIsOnScreen;
	bool mIsAlive;
	int mLife;



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
};

