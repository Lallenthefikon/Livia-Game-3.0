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

	for (Decorations::size_type i = 0; i < mDecorations.size(); i++) {
		mDecorations[i]->render(window);
	}
}

void MapEditorMeny::insertObjects(){

	// Entities
	mEntities.push_back(Factory::createGerm(sf::Vector2f(WIDTHBETWEEN * 2.7, 70)));
	mEntities.back()->setScale(sf::Vector2f(0.6, 0.6));
	mEntities.push_back(Factory::createPlayer(sf::Vector2f(WIDTHBETWEEN*0.8, 80)));
	mEntities.back()->setScale(sf::Vector2f(0.6f,0.6f));
	
	mEntities.push_back(Factory::createWorm(sf::Vector2f(WIDTHBETWEEN * 1.7, 70)));
	mEntities.back()->setScale(sf::Vector2f(0.6f, 0.6f));

	mEntities.push_back(Factory::createMeatball(sf::Vector2f(WIDTHBETWEEN * 2.6f, 70.f)));
	mEntities.back()->setScale(sf::Vector2f(0.25f, 0.25f));

	mEntities.push_back(Factory::createAcidMonster(sf::Vector2f(WIDTHBETWEEN * 4.f, 70.f)));
	mEntities.back()->setScale(sf::Vector2f(0.03f, 0.03f));

	mEntities.push_back(Factory::createExtraLife(sf::Vector2f(WIDTHBETWEEN * 4.4f, 70.5)));
	mEntities.back()->setScale(sf::Vector2f(0.7f, 0.7f));

	// Terrains
	mTerrains.push_back(Factory::createBlock0(sf::Vector2f(WIDTHBETWEEN * 0.8, 150), 'a'));
	mTerrains.back()->setScale(sf::Vector2f(0.6, 0.6));
	
	mTerrains.push_back(Factory::createBlock0WallJump(sf::Vector2f(WIDTHBETWEEN * 1.8, 150), 'p'));
	mTerrains.back()->setScale(sf::Vector2f(0.6, 0.6));
	
	mTerrains.push_back(Factory::createBlock0Icy(sf::Vector2f(WIDTHBETWEEN * 2.8, 70), 'a'));
	mTerrains.back()->setScale(sf::Vector2f(0.6, 0.6));
	
	mTerrains.push_back(Factory::createSpikes(sf::Vector2f(WIDTHBETWEEN * 3.8, 150), 't'));
	mTerrains.back()->setScale(sf::Vector2f(0.6, 0.6)); 
	
	mTerrains.push_back(Factory::createGoal(sf::Vector2f(WIDTHBETWEEN * 4.8, 150)));
	mTerrains.back()->setScale(sf::Vector2f(0.2, 0.2));
	mTerrains.push_back(Factory::createMeatballSpawner(sf::Vector2f(WIDTHBETWEEN * 5.8f, 150)));
	mTerrains.back()->setScale(sf::Vector2f(0.2f, 0.2f));

	// Dialog
	mTerrains.push_back(Factory::createEditorEvent(sf::Vector2f(WIDTHBETWEEN * 2.8, 150), 'a'));
	mTerrains.back()->setScale(sf::Vector2f(0.2, 0.2));

	// Decorations
	mDecorations.push_back(Factory::createDecoration(sf::Vector2f(WIDTHBETWEEN * 0.8f, 180.f), '1', 'b'));
	mDecorations.back()->setScale(sf::Vector2f(0.6f, 0.6f));
	mDecorations.push_back(Factory::createDecoration(sf::Vector2f(WIDTHBETWEEN * 1.8f, 180.f), '0', 'b'));
	mDecorations.back()->setScale(sf::Vector2f(0.6f, 0.6f));
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

				case Entity::GERM:
					mInsertType = GERM;
					break;

				case Entity::MEATBALL:
					mInsertType = MEATBALL;
					break;

				case Entity::ACIDMONSTER:
					mInsertType = ACIDMONSTER;
					break;

				case Entity::EXTRALIFE:
					mInsertType = EXTRALIFE;
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

				case Terrain::BLOCK0ICY:
					mInsertType = BLOCK0ICY;
					break;

				case Terrain::SPIKES:
					mInsertType = SPIKES;
					break;

				case Terrain::BLOCKGOAL:
					mInsertType = BLOCKGOAL;
					break;

				case Terrain::MEATBALLSPAWNER:
					mInsertType = MEATBALLSPAWNER;
					break;

				case Terrain::EVENT:
					mInsertType = EVENT;
					break;

				default:
					break;
				}
			}
		}
		for (Decorations::size_type i = 0; i < mDecorations.size(); i++) {
			if (MapEditorMeny::isSpriteClicked(mDecorations[i]->getSprite(), &mousepos)) {
				switch (mDecorations[i]->getDecorationID()) {
				case Decoration::FLOWER:
					mInsertType = DECORATION0;
					break;
				case Decoration::SAYS:
					mInsertType = DECORATION1;
					break;
				default:
					break;
				}
			}
		}

		std::cout << std::to_string(mInsertType) << std::endl;

		return true;
	}
	return false;
}

void MapEditorMeny::resetMenusPos(sf::Vector2f newPos){
	mMenySprite.setPosition(newPos);

	//// Player
	//mEntities[0]->setPos(sf::Vector2f(newPos.x + 10, newPos.y + 10));
	//// Worm
	//mEntities[1]->setPos(sf::Vector2f(newPos.x + WIDTHBETWEEN, newPos.y + 40));

	// Entities
	sf::Vector2f offset(0.f, 0.f);
	for (size_t i = 0; i < mEntities.size(); i++) {
		if (mEntities[i]->getType() == Entity::PLAYER) {
			offset = sf::Vector2f(25.f, 20.f);
		}
		if (mEntities[i]->getType() == Entity::WORM) {
			offset = sf::Vector2f(4.2f, 60.f);
		}
		if (mEntities[i]->getType() == Entity::ACIDMONSTER) {
			offset = sf::Vector2f(28.f, 60.f);
		}
		if (mEntities[i]->getType() == Entity::MEATBALL) {
			offset = sf::Vector2f(23.f, 40.f);
		}
		if (mEntities[i]->getType() == Entity::EXTRALIFE) {
			offset = sf::Vector2f(8.f, 7.f);
		}
		mEntities[i]->setPos(sf::Vector2f(newPos.x + WIDTHBETWEEN * i + offset.x, newPos.y + offset.y));
	}

	// Block0 
	for (size_t i = 0; i < mTerrains.size(); i++)
	mTerrains[i]->setPos(sf::Vector2f(newPos.x + WIDTHBETWEEN * i + 2, newPos.y + 100));

	// Decorations
	for (size_t i = 0; i < mDecorations.size(); i++)
		mDecorations[i]->setPos(sf::Vector2f(newPos.x + WIDTHBETWEEN * i + 10, newPos.y + 180));

	
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

