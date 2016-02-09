#pragma once

#include <SFML\System.hpp>
#include "Entity.h"
#include "Toolbox.h"
#include "Animations.h"
#include "CollisionFuncs.h"

class Player : public Entity{

public:
	enum PLAYERSTATE{ JUMPING, IDLE, RUNNING, FALLING };

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
	virtual void entityCollision(Entity* entity, char direction);
	virtual void terrainCollision(Terrain* terrain, char direction);


private:

	Player(sf::Vector2f pos);


	void playerInput();
	void lerp();

	void updateState();
	void updateANI();
	void updateCollision();
	void animate();

	// Stats 
	float mJumpSpeed;
	float mMaxSpeed;
	float mSpeed;

	sf::Sprite mSprite;

	// Animations stuff
	Animations::Textures* mCurrentAnimation;
	int mAnimationIndex;
	float mTimer;

	sf::Vector2f
		mVelocity,
		mSpriteOffset,
		mVelocityGoal;

	bool mIsOnScreen;
	PLAYERSTATE mState;


	char mCollisionT;
	char mCollisionB;
	char mCollisionL;
	char mCollisionR;

	Terrain* mCurrentCollisionB;
	Terrain* mCurrentCollisionT;
	Terrain* mCurrentCollisionL;
	Terrain* mCurrentCollisionR;

};