#include "MapEditorMeny.h"


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

	int widthBetween = 140;

	mEntities.push_back(Factory::createPlayer(sf::Vector2f(widthBetween, 100)));
	mEntities.push_back(Factory::createWorm(sf::Vector2f(widthBetween * 2, 100)));
	mTerrains.push_back(Factory::createBlock0(sf::Vector2f(widthBetween * 3, 100), 'a'));
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

				default:
					break;
				}
			}
		}
		return true;
	}
}

bool MapEditorMeny::isSpriteClicked(sf::Sprite& spr, sf::Vector2i *mousePos){
	return mousePos->x > spr.getPosition().x
		&& mousePos->x < spr.getPosition().x + spr.getLocalBounds().width
		&& mousePos->y > spr.getPosition().y
		&& mousePos->y < spr.getPosition().y + spr.getLocalBounds().height;
}