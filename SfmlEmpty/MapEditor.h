#pragma once

#include "GameState.h"
#include <vector>
#include "Factory.h"
#include "Entity.h"
#include "Terrain.h"
#include "Decoration.h"
#include "Toolbox.h"
#include "MapEditMaploader.h"
#include "MapEditorMeny.h"
#include "Camera.h"

#include "Texthandler.h"
#include "LayerHandler.h"
#include "Dialoguehandler.h"


class MapEditor : public GameState{
public:
	static MapEditor* getInstance(std::string &levelDirectory, std::string &levelName);

	virtual void update(sf::RenderWindow &window);
	virtual void render(sf::RenderWindow &window);
	
	void createPlayer(sf::Vector2f mousePos);
	void createWorm(sf::Vector2f mousePos);
	void createGerm(sf::Vector2f mousePos);
	void createAcidMonster(sf::Vector2f mousepos);
	void createMeatball(sf::Vector2f mousePos);
	void createExtraLife(sf::Vector2f mousePos);
	void createOcto_Pi(sf::Vector2f mousePos);
	
	void createBlock0(sf::Vector2f mousePos);
	void createBlock0WallJump(sf::Vector2f mousePos);
	void createBlock0Icy(sf::Vector2f mousePos);
	void createSpikes(sf::Vector2f mousepos);
	void createGoal(sf::Vector2f mousePos);
	void createMeatballSpawner(sf::Vector2f mousePos);

	void createEditorEvent(sf::Vector2f mousePos);

	void createDecoration(sf::Vector2f mousePos, char id, char layer, char rotation);


	virtual void setCurrentLevel(std::string &levelDirectory, std::string &levelName);
	virtual void loadLevel();

	void clearMap();

	std::vector<sf::Sprite> mGrid;

private:
	MapEditor(std::string &mapName, std::string &levelName);
	~MapEditor();

	void insertObject(sf::Vector2f mousePos);
	void eraseEntity(int index);
	void eraseTerrain(int index);
	void eraseDecoration(int index);
	void changeInsertType();
	void changeRotDirection();
	void changeLayer();

	void displayCurrentLayer(sf::RenderWindow &window);
	std::string layerToString() const;

	void saveMap();
	void sortVectors();
	void writeTerrainToFile(std::string filename);
	void writeEntityToFile(std::string filename);
	void writeDecorationToFile(std::string filename);
	char blockType(Terrain* terrain);
	void internalClear();

	std::string floatToString(float f);
	/*sf::Vector2f spikeOriginpos(Terrain* terrain);*/

	void createGrid();

	sf::Sprite determineSelectedTileInGrid(sf::Vector2f position, std::vector<sf::Sprite> *grid);
	bool isSpriteClicked(sf::Sprite& spr, sf::Vector2f *mousePos);

	void updateInsertType();
	void changeEventType();

	MapEditMaploader &mMaploader;

	MapEditorMeny::INSERTTYPE mInsertType;
	char mEventType;
	char mRotDirection;
	sf::Vector2f mEventSize;
	std::string mCurrentLevelDirectory;
	std::string mCurrentLevelName;

	typedef std::vector<Entity*> Entities;
	typedef std::vector<Terrain*> Terrains;
	typedef std::vector<Decoration*> Decorations;


	Entities mEntities;
	Terrains mTerrains;
	Decorations mDecorations;

	MapEditorMeny& mMeny;

	sf::Texture mTileTexture;

	sf::Vector2f mMapDimensionsPixels;
	sf::Vector2f mMapDimensionsTiles;
	sf::Vector2f mTileDimensions;

	// Camera Edit
	Camera mCamera;

	// Decoration
	char mDecorationLayer;

	Texthandler& mTextHandler;
	LayerHandler& mLayerHandler;
	Dialoguehandler& mDialogueHandler;

	sf::Sound mAirHorn;
};

