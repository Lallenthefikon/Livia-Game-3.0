#pragma once

#include "Entityhandler.h"
#include "Terrainhandler.h"
#include "Collisionhandler.h"
#include "MapGenerator.h"
#include "Toolbox.h"
#include "Camera.h"
#include "Level.h"
#include "LayerHandler.h"

class Intestine : public Level{
public:
	static Intestine& getInstance();
	virtual void update(sf::RenderWindow &window);
	virtual void render(sf::RenderWindow &window);
	virtual void loadLevel();
	virtual void unloadLevel();
	virtual std::string getLevelName(){ return mMapName; }
	virtual std::string getLevelDirectory(){ return mMapPath; }
	void setCurrentMap(std::string &mapname);
private:
	Intestine();
	~Intestine();
	Entityhandler& mEntityHandler;
	Terrainhandler& mTerrainHandler;
	MapGenerator& mMapGenerator;
	Collisionhandler& mCollisionHandler;
	LayerHandler& mLayerHandler;

	Camera mCamera;
	std::string mMapName;
	std::string mMapPath;

	sf::Sprite mBackground;
	sf::Texture mTexture;
};