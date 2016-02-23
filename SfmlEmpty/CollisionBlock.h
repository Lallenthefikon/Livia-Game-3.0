#pragma once
#include "BlockTerrain.h"
#include <SFML\System.hpp>
#include "Toolbox.h"


class CollisionBlock : public BlockTerrain
{
public:

	virtual ~CollisionBlock();
	virtual Terrain::TERRAINTYPE getType() { return Terrain::BLOCK0; }
	static Terrain* createBlock0(sf::Vector2f pos, char type);
	virtual void render(sf::RenderWindow &window);
	virtual void update();
	virtual void addBlockTerrain(BlockTerrain *blockterrain);
	virtual sf::Vector2f getPos() { return mSprite.getPosition(); }
	virtual sf::Vector2f getOffset() { return mSpriteOffset; }
	virtual float getWidth() { return mSprite.getGlobalBounds().width; }
	virtual float getHeight() { return mSprite.getGlobalBounds().height; }
	virtual sf::Sprite getSprite() { return mSprite; }
	virtual bool isOnScreen() { return mIsOnScreen; }
	virtual void setPos(sf::Vector2f newPos);
	virtual void setScale(sf::Vector2f newScale) { mSprite.setScale(newScale); }
	virtual char getTileType() { return mTileType; }

private:
	CollisionBlock(sf::Vector2f pos, char type);

	sf::Sprite mSprite;
	sf::Vector2f mSpriteOffset;

	typedef std::vector<BlockTerrain*> BlockTerrains;
	typedef std::vector<BlockTerrains*> BlockTerrains2D;

	BlockTerrains2D mBlockTerrains2D;

	char mTileType;

	bool mIsOnScreen = true;

};

