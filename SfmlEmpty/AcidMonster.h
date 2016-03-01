#pragma once

#include "Entity.h"
#include <SFML\System.hpp>
#include "Toolbox.h"
#include "Animations.h"
#include "CollisionFuncs.h"

	class AcidMonster : public Entity{
	public:
		enum ACIDMONSTERSTATE { MOVINGRIGHT };
		virtual ~AcidMonster();
		virtual ENTITYTYPE getType(){ return ACIDMONSTER; }
		static Entity* createAcidMonster(sf::Vector2f pos);
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
		virtual void blockterrainCollision(BlockTerrain* blockterrain, char direction);
		virtual void getHit();
		virtual void setPos(sf::Vector2f newPos);
		virtual void setScale(sf::Vector2f newScale){ mSprite.setScale(newScale); }
		virtual int getLife(){ return 0; }

	private:
		AcidMonster(sf::Vector2f pos);

		void lerp();
		void addSpeed();

		void updateState();
		void updateANI();
		void animate();


		sf::Sprite mSprite;

		// Animimations stuff
		Animations::Textures* mCurrentAnimation;
		int mAnimationIndex;
		float mTimer;

		float mAcceleration;
		float mMaxSpeed;

		sf::Vector2f mSpriteOffset,
			mVelocity,
			mVelocityGoal;

		ACIDMONSTERSTATE mState;
		bool mIsOnScreen;
		bool mIsAlive;

	};

