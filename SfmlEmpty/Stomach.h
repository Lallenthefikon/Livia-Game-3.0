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

class Stomach : public Level{
public:
	static Stomach& getInstance();
	virtual void update(sf::RenderWindow &window, float &frameTime);
	virtual void render(sf::RenderWindow &window);
	virtual void loadLevel();
	virtual void unloadLevel();
	virtual std::string getLevelName(){ return mMapName; }
	virtual std::string getLevelDirectory(){ return mMapPath; }
	void setCurrentMap(std::string &mapname);
	
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
	sf::Sprite mBackgroundSprite;
	sf::Sprite mLifeSprite;
	Camera mCamera;

	std::string mMapName;
	std::string mMapPath;

	std::string mLevelState;


	sf::Sprite mBackground;
	sf::Texture mTexture;

	bool mGameOver = false;
};