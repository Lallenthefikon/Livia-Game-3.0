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

	mEntities.push_back(Factory::createPlayer(sf::Vector2f(WIDTHBETWEEN*0.8f, 80.f)));
	mEntities.back()->setScale(sf::Vector2f(0.6f,0.6f));
	mEntities.push_back(Factory::createWorm(sf::Vector2f(WIDTHBETWEEN * 1.7f, 70.f)));
	mEntities.back()->setScale(sf::Vector2f(0.6f, 0.6f));
	mTerrains.push_back(Factory::createBlock0(sf::Vector2f(WIDTHBETWEEN * 0.8f, 150.f), 'a'));
	mTerrains.back()->setScale(sf::Vector2f(0.6f, 0.6f));
	mTerrains.push_back(Factory::createBlock0WallJump(sf::Vector2f(WIDTHBETWEEN * 1.8f, 150.f), 'p'));
	mTerrains.back()->setScale(sf::Vector2f(0.6f, 0.6f));
	mTerrains.push_back(Factory::createSpikes(sf::Vector2f(WIDTHBETWEEN * 2.8f, 150.f), 't'));
	mTerrains.back()->setScale(sf::Vector2f(0.6f, 0.6f)); 
	mTerrains.push_back(Factory::createGoal(sf::Vector2f(WIDTHBETWEEN * 2.8f, 150.f)));
	mTerrains.back()->setScale(sf::Vector2f(0.2f, 0.2f));
	mDecorations.push_back(Factory::createDecoration(sf::Vector2f(WIDTHBETWEEN * 2.8f, 70.f), '0', 'b'));
	mDecorations.back()->setScale(sf::Vector2f(0.6f, 0.6f));
	mDecorations.push_back(Factory::createDecoration(sf::Vector2f(WIDTHBETWEEN * 2.8f, 70.f), '1', 'b'));
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

				case Terrain::SPIKES:
					mInsertType = SPIKES;
					break;

				case Terrain::BLOCKGOAL:
					mInsertType = BLOCKGOAL;
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
				case Decoration::DECORATIONID::SAYS:
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

	// Player
	mEntities[0]->setPos(sf::Vector2f(newPos.x + 10, newPos.y + 10));
	// Worm
	mEntities[1]->setPos(sf::Vector2f(newPos.x + WIDTHBETWEEN, newPos.y + 40));
	// Block0 
	for (size_t i = 0; i < mTerrains.size(); i++)
	mTerrains[i]->setPos(sf::Vector2f(newPos.x + WIDTHBETWEEN * i + 2, newPos.y + 100));

	// Decorations
	for (size_t i = 0; i < mDecorations.size(); i++) {
		mDecorations[i]->setPos(sf::Vector2f(newPos.x + WIDTHBETWEEN * i + 10, newPos.y + 180));
	}


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