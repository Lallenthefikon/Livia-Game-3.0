#pragma once

#include "Entity.h"
#include "Terrain.h"
#include "Decoration.h"
#include "Dialogue.h"
#include "Toolbox.h"
#include <vector>
#include "Factory.h"

class MapEditorMeny{
public:
	enum INSERTTYPE { BLOCK0, PLAYER, WORM, ACIDMONSTER, BLOCK0WALLJUMP, SPIKES, BLOCKGOAL, DECORATION0, DIALOGUE };

	static MapEditorMeny& getInstance();
	void render(sf::RenderWindow &window);
	void insertObjects();
	bool menyClicked(sf::Vector2i mousepos);
	INSERTTYPE& getInsertType(){ return mInsertType; }
	void resetMenusPos(sf::Vector2f newPos);

private:
	MapEditorMeny();
	~MapEditorMeny();

	bool isSpriteClicked(sf::Sprite& spr, sf::Vector2i *mousePos);

	typedef std::vector<Entity*> Entities;
	typedef std::vector<Terrain*> Terrains;
	typedef std::vector<Decoration*> Decorations;
	typedef std::vector<Dialogue*> Dialogue;

	Entities mEntities;
	Terrains mTerrains;
	Decorations mDecorations;
	Dialogue mDialogue;
	
	INSERTTYPE mInsertType;

	sf::Texture mMenyTexture;
	sf::Sprite mMenySprite;
};

