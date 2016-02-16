#include "MapEditorMeny.h"
#include <iostream>
int WIDTHBETWEEN = 70;

MapEditorMeny::MapEditorMeny():
mInsertType(BLOCK0){
	mMenyTexture.loadFromImage(Toolbox::getTexture(Toolbox::EDITORMENY));
	mMenySprite.setTexture(mMenyTexture);
	mMenySprite.setPosition(0,0);
	MapEditorMeny::insertObjects();
}


MapEditorMeny::~MapEditorMeny(){
}

MapEditorMeny& MapEditorMeny::getInstance(){
	static MapEditorMeny mapeditormeny;
	return mapeditormeny;
}

void MapEditorMeny::render(sf::RenderWindow &window){

	window.draw(mMenySprite);

	for (Terrains::size_type i = 0; i < mTerrains.size(); i++){
		mTerrains[i]->render(window);
	}

	for (Entities::size_type i = 0; i < mEntities.size(); i++){
		mEntities[i]->render(window);
	}
}

void MapEditorMeny::insertObjects(){

	mEntities.push_back(Factory::createPlayer(sf::Vector2f(WIDTHBETWEEN*0.8, 80)));
	mEntities.back()->setScale(sf::Vector2f(0.6,0.6));
	mEntities.push_back(Factory::createWorm(sf::Vector2f(WIDTHBETWEEN * 1.7, 70)));
	mEntities.back()->setScale(sf::Vector2f(0.6, 0.6));
	mTerrains.push_back(Factory::createBlock0(sf::Vector2f(WIDTHBETWEEN * 2.7, 80), 'a'));
	mTerrains.back()->setScale(sf::Vector2f(0.6, 0.6));
	mTerrains.push_back(Factory::createBlock0WallJump(sf::Vector2f(WIDTHBETWEEN * 3.7, 80), 'p'));
	mTerrains.back()->setScale(sf::Vector2f(0.6, 0.6));
}

bool MapEditorMeny::menyClicked(sf::Vector2i mousepos){
	if (MapEditorMeny::isSpriteClicked(mMenySprite, &mousepos)){
		for (Entities::size_type i = 0; i < mEntities.size(); i++){
			if (MapEditorMeny::isSpriteClicked(mEntities[i]->getSprite(), &mousepos)){
				switch (mEntities[i]->getType()){

				case Entity::PLAYER:
					mInsertType = PLAYER;
					break;

				case Entity::WORM:
					mInsertType = WORM;
					break;

				default:
					break;
				}
			}
		}
		for (Terrains::size_type i = 0; i < mTerrains.size(); i++){
			if (MapEditorMeny::isSpriteClicked(mTerrains[i]->getSprite(), &mousepos)){
				switch (mTerrains[i]->getType()){

				case Terrain::BLOCK0:
					mInsertType = BLOCK0;
					break;
					
				case Terrain::BLOCK0WALLJUMP:
					mInsertType = BLOCK0WALLJUMP;
					break;

				default:
					break;
				}
			}
		}
		return true;
	}
}

void MapEditorMeny::resetMenusPos(sf::Vector2f newPos){
	mMenySprite.setPosition(newPos);

	// Player
	mEntities[0]->setPos(sf::Vector2f(newPos.x + 10, newPos.y + 10));
	// Worm
	mEntities[1]->setPos(sf::Vector2f(newPos.x + WIDTHBETWEEN, newPos.y + 40));
	// Block0 
	mTerrains[0]->setPos(sf::Vector2f(newPos.x + WIDTHBETWEEN * 1.7, newPos.y + 20));

	//int nrOfEntities;
	//for (Entities::size_type i = 0; i < mEntities.size(); i++){
	//	nrOfEntities = i + 1;
	//	mEntities[i]->setPos(sf::Vector2f(newPos.x + WIDTHBETWEEN * (i + nrOfEntities), newPos.y + 50));
	//}
	//nrOfEntities++;
	//for (Terrains::size_type i = 0; i < mTerrains.size(); i++){
	//	mTerrains[i]->setPos(sf::Vector2f(newPos.x + WIDTHBETWEEN * nrOfEntities, newPos.y + 50));
	//}
}

bool MapEditorMeny::isSpriteClicked(sf::Sprite& spr, sf::Vector2i *mousePos){
	return mousePos->x > spr.getPosition().x
		&& mousePos->x < spr.getPosition().x + spr.getLocalBounds().width
		&& mousePos->y > spr.getPosition().y
		&& mousePos->y < spr.getPosition().y + spr.getLocalBounds().height;
}