#pragma once
#include "Entity.h"
class Meatball : public Entity {
public:

	virtual ~Meatball();
	virtual ENTITYTYPE getType() { return MEATBALL; }
	static Entity* createMeatball(sf::Vector2f pos);

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
	virtual int getLife() { return 0; }
private:
	Meatball(sf::Vector2f pos);

	void updateTexturepos();

	void lerp();

	void updateState();
	void updateANI();
	void updateCollision();
	void animate();
	void checkOutOfBounds();
	void kill();

	void randDirection();

	void playSound();
	void stopSound();

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

	bool mIsOnScreen;
	bool mIsAlive;

};

