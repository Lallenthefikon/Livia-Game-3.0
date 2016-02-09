#pragma once

#include "GameState.h"
#include <vector>
#include "Factory.h"
#include "Entity.h"
#include "Terrain.h"
#include "Toolbox.h"
#include "MapEditMaploader.h"
#include "MapEditorMeny.h"
#include "Camera.h"

class MapEditor : public GameState{
public:
	static MapEditor* getInstance(std::string &mapName);

	virtual void update(sf::RenderWindow &window);
	virtual void render(sf::RenderWindow &window);
	
	void createBlock0(sf::Vector2f mousePos);
	void createPlayer(sf::Vector2f mousePos);
	void createWorm(sf::Vector2f mousePos);

	virtual void setCurrentMap(std::string &mapname){ mCurrentMap = mapname; }
	virtual void loadMap();

	void clearMap();

	std::vector<sf::Sprite> mGrid;

private:
	MapEditor(std::string &mapName);
	~MapEditor();

	void insertObject(sf::Vector2f mousePos);
	void eraseEntity(int index);
	void eraseTerrain(int index);
	void changeInsertType();

	void saveMap();
	void writeTerrainToFile(std::string filename);
	void writeEntityToFile(std::string filename);
	char blockType(Terrain* terrain);
	void internalClear();

	std::string floatToString(float f);

	void createGrid();

	sf::Sprite determineSelectedTileInGrid(sf::Vector2f position, std::vector<sf::Sprite> *grid);
	bool isSpriteClicked(sf::Sprite& spr, sf::Vector2f *mousePos);

	void updateInsertType();

	MapEditMaploader &mMaploader;

	MapEditorMeny::INSERTTYPE mInsertType;
	std::string mCurrentMap;

	typedef std::vector<Entity*> Entities;
	typedef std::vector<Terrain*> Terrains;

	Entities mEntities;
	Terrains mTerrains;
	MapEditorMeny& mMeny;

	sf::Texture mTileTexture;

	sf::Vector2f mMapDimensionsPixels;
	sf::Vector2f mMapDimensionsTiles;
	sf::Vector2f mTileDimensions;

	// Camera Edit
	Camera mCamera;
};

