#pragma once

#include <SFML\Graphics.hpp>
#include "BlockTerrain.h"
#include "Toolbox.h"
#include "Animations.h"
#include "CollisionFuncs.h"
#include "SoundFactory.h"
#include "SoundFX.h"
#include "Texthandler.h"

class Entity{
public:
	enum ENTITYTYPE {PLAYER, WORM, ACIDMONSTER, MEATBALL, GERM, EXTRALIFE, OCTO_PI };
	
	Entity();
	virtual ~Entity();
	virtual ENTITYTYPE getType() = 0;
	
	virtual void render(sf::RenderWindow &window) = 0;
	virtual void update() = 0;
	
	virtual void entityCollision(Entity* entity, char direction) = 0;
	virtual void terrainCollision(Terrain* terrain, char direction) = 0;
	virtual void blockterrainCollision(BlockTerrain* blockterrain, char direction) = 0;
	
	virtual void addVector(sf::Vector2f &vector) = 0;
	
	virtual sf::Vector2f getPos() = 0;
	virtual sf::Vector2f getOffset() = 0;
	virtual float getWidth() = 0;
	virtual float getHeight() = 0;
	virtual sf::Sprite getSprite() = 0;
	virtual bool isOnScreen() = 0;
	virtual void getHit() = 0;
	virtual bool getIsAlive() = 0;
	virtual void setPos(sf::Vector2f newPos) = 0;
	virtual void setScale(sf::Vector2f newScale) = 0;
	virtual int getLife() = 0;

	virtual void stopAllSound() = 0;
};

