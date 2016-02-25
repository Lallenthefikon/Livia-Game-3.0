#include "CollisionBlock.h"



CollisionBlock::CollisionBlock(sf::Vector2f pos, char type){
}


CollisionBlock::~CollisionBlock(){
}

Terrain* CollisionBlock::createBlock0(sf::Vector2f pos, char type) {
	return new CollisionBlock(pos, type);
}

void CollisionBlock::render(sf::RenderWindow &window) {
	window.draw(mSprite);
}

void CollisionBlock::update() {

}

void CollisionBlock::addBlockTerrain(BlockTerrain  *blockterrain){
}

void CollisionBlock::setPos(sf::Vector2f newPos) {
	mSprite.setPosition(newPos);
}