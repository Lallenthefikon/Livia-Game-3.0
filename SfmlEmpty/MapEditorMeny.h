#pragma once

#include "Entity.h"
#include "Terrain.h"
#include "Decoration.h"
#include "Toolbox.h"
#include <vector>
#include "Factory.h"

class MapEditorMeny {
public:
	enum INSERTTYPE {
		BLOCK0ICY, BLOCK0, PLAYER, WORM, ACIDMONSTER, BLOCK0WALLJUMP,
		SPIKES, BLOCKGOAL, 
		
		DECORATION0, DECORATION1, DECORATION2, DECORATION3, DECORATION4, 
		DECORATION5, DECORATION6, DECORATION7, DECORATION8, DECORATION9,
		DECORATION10, DECORATION11, DECORATION12, DECORATION13, DECORATION14,
		DECORATION15, DECORATION16, DECORATION17, DECORATION18, DECORATION19,
		DECORATION20, DECORATION21, DECORATION22, DECORATION23, DECORATION24,
		DECORATION25, DECORATION26, DECORATION27, DECORATION28, DECORATION29,
		
		MEATBALLSPAWNER, DIALOGUE,
		MEATBALL, GERM, EVENT ,EXTRALIFE, OCTO_PI
	};

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
	

	Entities mEntities;
	Terrains mTerrains;
	Decorations mDecorations;
	
	INSERTTYPE mInsertType;

	sf::Texture mMenyTexture;
	sf::Sprite mMenySprite;

};

