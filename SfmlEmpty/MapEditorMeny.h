#pragma once

#include "Entity.h"
#include "Terrain.h"
#include "Toolbox.h"
#include <vector>
#include "Factory.h"

class MapEditorMeny{
public:

	enum INSERTTYPE{
		BLOCK0,
		PLAYER,
		WORM
	};

	static MapEditorMeny& getInstance();

	void render(sf::RenderWindow &window);

	void insertObjects();

	bool menyClicked(sf::Vector2i mousepos);

	INSERTTYPE& getInsertType(){ return mInsertType; }

private:
	MapEditorMeny();
	~MapEditorMeny();

	bool isSpriteClicked(sf::Sprite& spr, sf::Vector2i *mousePos);

	typedef std::vector<Entity*> Entities;
	typedef std::vector<Terrain*> Terrains;

	Entities mEntities;
	Terrains mTerrains;
	
	INSERTTYPE mInsertType;

	sf::Texture mMenyTexture;

	sf::Sprite mMenySprite;
};

