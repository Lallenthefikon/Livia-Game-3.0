#pragma once

#include "BlockTerrain.h"
#include <SFML\System.hpp>


class CollisionBlock : public BlockTerrain
{
public:
	typedef std::vector<Terrain*> Terrains;
	typedef std::vector<Terrains*> Terrains2D;
	virtual ~CollisionBlock();
	virtual Terrain::TERRAINTYPE getType() { return Terrain::COLLISIONBLOCK; }
	static BlockTerrain* createCollisionBlock(sf::Vector2f pos);
	virtual void render(sf::RenderWindow &window);
	virtual void update();
	virtual sf::Vector2f getPos() { return mSprite.getPosition(); }
	virtual sf::Vector2f getOffset() { return mSpriteOffset; }
	virtual float getWidth() { return mSprite.getGlobalBounds().width; }
	virtual float getHeight() { return mSprite.getGlobalBounds().height; }
	virtual sf::Sprite getSprite() { return mSprite; }
	virtual bool isOnScreen() { return mIsOnScreen; }
	virtual void setPos(sf::Vector2f newPos);
	virtual void setScale(sf::Vector2f newScale) { mSprite.setScale(newScale); }
	virtual char getTileType() { return mTileType; }

	// BlockTerrain specific
	virtual void addBlockTerrain(Terrain* blockTerrain, bool newX);
	virtual Terrain* getBlock(int xIndex, int yIndex);
	virtual Terrains2D& getBlocks();
	virtual Terrain::TERRAINTYPE getType(sf::Vector2f pos, float length, char direction);
	virtual char getTileType(sf::Vector2f pos, float length, char direction);
private:
	CollisionBlock(sf::Vector2f pos);

	sf::Sprite mSprite;
	sf::Vector2f mSpriteOffset;

	void updateRect();

	void checkCollisionR(sf::Vector2f pos, float length);
	void checkCollisionL(sf::Vector2f pos, float length);
	void checkCollisionT(sf::Vector2f pos, float length);
	void checkCollisionB(sf::Vector2f pos, float length);

	void prioritizeBlockTypes(Terrain::TERRAINTYPE blockType);

	Terrains2D mBlockTerrains2D;
	sf::Texture mTexture;

	Terrain::TERRAINTYPE mHighestPrio;
	char mTileType;

	bool mIsOnScreen = true;

};

