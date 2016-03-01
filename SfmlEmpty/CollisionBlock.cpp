#include "CollisionBlock.h"



CollisionBlock::CollisionBlock(sf::Vector2f pos){
	//mTexture.loadFromImage(Toolbox::getTexture(Toolbox::EDITORMENY));
	//mSprite.setTexture(mTexture);
	mSprite.setPosition(pos);
	
}


CollisionBlock::~CollisionBlock(){
}

BlockTerrain* CollisionBlock::createCollisionBlock(sf::Vector2f pos) {
	return new CollisionBlock(pos);
}

void CollisionBlock::render(sf::RenderWindow &window) {
	for (Terrains2D::size_type i = 0; i < mBlockTerrains2D.size(); i++) {
		for (Terrains2D::size_type j = 0; j < mBlockTerrains2D[i]->size(); j++) {
			mBlockTerrains2D[i]->at(j)->render(window);
		}
	}
}

void CollisionBlock::update() {

}

void CollisionBlock::addBlockTerrain(Terrain  *blockterrain, bool newX ){
	if (newX) {
		mBlockTerrains2D.push_back(new Terrains);
	}
	mBlockTerrains2D.back()->push_back(blockterrain);
	CollisionBlock::updateRect();
}

Terrain * CollisionBlock::getBlock(int xIndex, int yIndex){
	return mBlockTerrains2D[xIndex]->at(yIndex);
}

CollisionBlock::Terrains2D& CollisionBlock::getBlocks() {
	return mBlockTerrains2D;
}

Terrain::TERRAINTYPE CollisionBlock::getType(sf::Vector2f pos, float length, char direction) {
	mHighestPrio = BLOCK0;
	switch (direction){
	case 'r':
		 checkCollisionR(pos, length);
		break;
	case 'l':
		 checkCollisionL(pos, length);
		break;
	case 't':
		 checkCollisionT(pos, length);
		break;
	case 'b':
		 checkCollisionB(pos, length);
		break;
	default:
		break;
	}
	return mHighestPrio;
}

void CollisionBlock::setPos(sf::Vector2f newPos) {
	mSprite.setPosition(newPos);
}

char CollisionBlock::getTileType(sf::Vector2f pos, float length, char direction){
	switch (direction) {
	case 'r':
		checkCollisionR(pos, length);
		break;
	case 'l':
		checkCollisionL(pos, length);
		break;
	case 't':
		checkCollisionT(pos, length);
		break;
	case 'b':
		checkCollisionB(pos, length);
		break;
	default:
		break;
	}
	return mTileType;
}

// Privates

void CollisionBlock::updateRect(){
	float width(0);
	float height(0);
	for (Terrains2D::size_type i = 0; i < mBlockTerrains2D.size(); i++) {
		width += mBlockTerrains2D[i]->at(0)->getWidth();
	}
	for (Terrains::size_type i = 0; i < mBlockTerrains2D[0]->size(); i++){
		height += mBlockTerrains2D[0]->at(i)->getHeight();
	}
	mSprite.setTextureRect(sf::IntRect(0, 0, width, height));
}

void CollisionBlock::checkCollisionR(sf::Vector2f pos, float length){
	for (Terrains2D::size_type i = 0; i < mBlockTerrains2D.back()->size(); i++) {
		if (!((mBlockTerrains2D.back()->at(i)->getPos().y < pos.y && mBlockTerrains2D.back()->at(i)->getPos().y + mBlockTerrains2D.back()->at(i)->getHeight() < pos.y)
			|| (mBlockTerrains2D.back()->at(i)->getPos().y > pos.y + length && mBlockTerrains2D.back()->at(i)->getPos().y + mBlockTerrains2D.back()->at(i)->getHeight() > pos.y + length))) {
			CollisionBlock::prioritizeBlockTypes(mBlockTerrains2D.back()->at(i)->getType());
			mTileType = mBlockTerrains2D.back()->at(i)->getTileType();
		}
	}
}

void CollisionBlock::checkCollisionL(sf::Vector2f pos, float length){
	for (Terrains2D::size_type i = 0; i < mBlockTerrains2D.back()->size(); i++) {
		if (!((mBlockTerrains2D[0]->at(i)->getPos().y < pos.y && mBlockTerrains2D[0]->at(i)->getPos().y + mBlockTerrains2D[0]->at(i)->getHeight() < pos.y)
			|| (mBlockTerrains2D[0]->at(i)->getPos().y > pos.y + length && mBlockTerrains2D[0]->at(i)->getPos().y + mBlockTerrains2D[0]->at(i)->getHeight() > pos.y + length))) {
			CollisionBlock::prioritizeBlockTypes(mBlockTerrains2D[0]->at(i)->getType());
			mTileType = mBlockTerrains2D[0]->at(i)->getTileType();
		}
	}
}

void CollisionBlock::checkCollisionT(sf::Vector2f pos, float length){
	for (Terrains2D::size_type i = 0; i < mBlockTerrains2D.size(); i++) {
		if (!((mBlockTerrains2D[i]->at(0)->getPos().x < pos.x && mBlockTerrains2D[i]->at(0)->getPos().x + mBlockTerrains2D[i]->at(0)->getWidth() < pos.x)
			|| (mBlockTerrains2D[i]->at(0)->getPos().x > pos.x + length && mBlockTerrains2D[i]->at(0)->getPos().x + mBlockTerrains2D[i]->at(0)->getWidth() > pos.x + length))) {
			CollisionBlock::prioritizeBlockTypes(mBlockTerrains2D[i]->at(0)->getType());
			mTileType = mBlockTerrains2D[i]->at(0)->getTileType();
		}
	}
}

void CollisionBlock::checkCollisionB(sf::Vector2f pos, float length) {
	for (Terrains2D::size_type i = 0; i < mBlockTerrains2D.size(); i++) {
		if (!((mBlockTerrains2D[i]->back()->getPos().x < pos.x && mBlockTerrains2D[i]->back()->getPos().x + mBlockTerrains2D[i]->back()->getWidth() < pos.x)
			|| (mBlockTerrains2D[i]->back()->getPos().x > pos.x + length && mBlockTerrains2D[i]->back()->getPos().x + mBlockTerrains2D[i]->back()->getWidth() > pos.x + length))) {
			CollisionBlock::prioritizeBlockTypes(mBlockTerrains2D[i]->back()->getType());
			mTileType = mBlockTerrains2D[i]->back()->getTileType();
		}
	}
}

void CollisionBlock::prioritizeBlockTypes(Terrain::TERRAINTYPE blockType){
	if (blockType > mHighestPrio) {
		mHighestPrio = blockType;
	}
}

