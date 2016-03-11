#pragma once

#include "Entityhandler.h"
#include "Terrainhandler.h"
#include "Collisionhandler.h"
#include "LayerHandler.h"
#include "Texthandler.h"
#include "Decorationhandler.h"
#include "MapGenerator.h"
#include "Dialoguehandler.h"
#include "Toolbox.h"
#include "Camera.h"
#include "Level.h"


class Stomach : public Level{
public:
	static Stomach& getInstance();
	~Stomach();
	virtual void update(sf::RenderWindow &window);
	virtual void render(sf::RenderWindow &window);
	virtual void loadLevel();
	virtual void unloadLevel();
	virtual std::string getLevelName(){ return mMapName; }
	virtual std::string getLevelDirectory(){ return mMapPath; }
	virtual void triggerEvent(char type);
	void setCurrentMap(std::string &mapname);
	void resetLevel(sf::RenderWindow &window);
	
private:
	Stomach();
	void eventA();
	void eventB();
	void eventC();
	void eventD();
	void eventE();
	void eventF();
	void eventG();

	Entityhandler* mEntityHandler;
	Terrainhandler* mTerrainHandler;
	MapGenerator& mMapGenerator;
	Collisionhandler& mCollisionHandler;
	LayerHandler& mLayerHandler;
	Texthandler& mTextHandler;
	Decorationhandler& mDecorationhandler;
	Dialoguehandler& mDialoguehandler;

	// Specific level graphics
	sf::Texture mBackgroundTexture;
	sf::Texture mMiddlegroundTexture;
	sf::Texture mLifeTexture;
	sf::Texture mAcidTexture;
	sf::Sprite mBackgroundSprite;
	sf::Sprite mLifeSprite;

	// Level Info
	sf::FloatRect mLevelBounds;
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