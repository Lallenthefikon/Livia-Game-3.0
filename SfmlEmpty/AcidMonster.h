#pragma once

#include "Entity.h"
#include <SFML\System.hpp>
#include "Toolbox.h"
#include "Animations.h"
#include "CollisionFuncs.h"

	class AcidMonster : public Entity{
	public:
		enum ACIDMONSTERSTATE { MOVINGRIGHT, MOVINGUP };
		virtual ~AcidMonster();
		virtual ENTITYTYPE getType(){ return ACIDMONSTER; }
		static Entity* createAcidMonster(sf::Vector2f pos);
		virtual void render(sf::RenderWindow &window);
		virtual void update();
		virtual sf::Vector2f getPos(){ return mCollisionBody.getPosition(); }
		virtual sf::Vector2f getOffset(){ return mSpriteOffset; }
		virtual float getWidth(){ return mCollisionBody.getGlobalBounds().width; }
		virtual float getHeight(){ return mCollisionBody.getGlobalBounds().height; }
		virtual sf::Sprite getSprite(){ return mCollisionBody; }
		virtual bool isOnScreen(){ return mIsOnScreen; }
		virtual bool getIsAlive(){ return mIsAlive; }
		virtual void addVector(sf::Vector2f &vector);

		virtual void entityCollision(Entity* entity, char direction);
		virtual void terrainCollision(Terrain* terrain, char direction);
		virtual void blockterrainCollision(BlockTerrain* blockterrain, char direction);
		virtual void getHit();
		virtual void setPos(sf::Vector2f newPos);
		virtual void setScale(sf::Vector2f newScale){ mCollisionBody.setScale(newScale), mSprite.setScale(newScale); }
		virtual int getLife(){ return 0; }

	private:
		AcidMonster(sf::Vector2f pos);

		void updateTexturepos();

		void lerp();
		void addSpeed();

		void updateState();
		void updateANI();
		void animate();

		void setup();
		void setAnimation();

		void playSound(ACIDMONSTERSTATE state);
		void stopSound(ACIDMONSTERSTATE state);
		void updateSound();

		float calculateVolume(sf::Vector2f &pos1, sf::Vector2f &pos2);

		sf::Sprite mSprite,
			mCollisionBody;

		// Animimations stuff
		Animations::Textures* mCurrentAnimation;
		int mAnimationIndex;
		float mTimer;

		float mAcceleration;
		float mMaxSpeed;

		sf::Vector2f mSpriteOffset,
			mVelocity,
			mVelocityGoal,
			mCollisionBodyOffset;

		ACIDMONSTERSTATE mState;
		bool mIsOnScreen;
		bool mIsAlive;

		// Sounds
		SoundFX& mSoundFX;
	};

