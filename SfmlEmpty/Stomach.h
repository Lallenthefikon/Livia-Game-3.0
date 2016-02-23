#pragma once

#include "Entityhandler.h"
#include "Terrainhandler.h"
#include "Collisionhandler.h"
#include "LayerHandler.h"
#include "Texthandler.h"
#include "MapGenerator.h"
#include "Toolbox.h"
#include "Camera.h"
#include "Level.h"
#include "AcidMonster.h"

class Stomach : public Level{
public:
	static Stomach& getInstance();
	virtual void update(sf::RenderWindow &window);
	virtual void render(sf::RenderWindow &window);
	virtual void loadLevel();
	virtual void unloadLevel();
	virtual std::string getLevelName(){ return mMapName; }
	virtual std::string getLevelDirectory(){ return mMapPath; }
	void setCurrentMap(std::string &mapname);
	void resetLevel(sf::RenderWindow &window);
	
private:
	Stomach();
	~Stomach();
	
	Entityhandler& mEntityHandler;
	Terrainhandler& mTerrainHandler;
	MapGenerator& mMapGenerator;
	Collisionhandler& mCollisionHandler;
	LayerHandler& mLayerHandler;
	Texthandler& mTextHandler;

	sf::Texture mBackgroundTexture;
	sf::Texture mLifeTexture;
	sf::Texture mAcidTexture;
	sf::Sprite mBackgroundSprite;
	sf::Sprite mLifeSprite;
	sf::Sprite mAcidSprite;
	
	Camera mCamera;

	std::string mMapName,
				mMapPath,
				mLevelState;

	sf::Sprite mBackground;
	sf::Texture mTexture;

	bool mGameOver = false;
	bool mZoomedOut;
};