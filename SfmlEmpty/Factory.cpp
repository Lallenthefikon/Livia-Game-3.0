#include "Factory.h"
#include "Player.h"
#include "Block0.h"
#include "Worm.h"
#include "AcidMonster.h"
#include "Block0WallJump.h"
#include "Spikes.h"
#include "BlockGoal.h"
#include "Decoration.h"
#include "CollisionBlock.h"

Entity* Factory::createPlayer(sf::Vector2f pos){
	return Player::createPlayer(pos);
}

Terrain* Factory::createBlock0(sf::Vector2f pos, char type){
	return Block0::createBlock0(pos, type);
}

Entity* Factory::createWorm(sf::Vector2f pos){
	return Worm::createWorm(pos);
}

Entity* Factory::createAcidMonster(sf::Vector2f pos){
	return AcidMonster::createAcidMonster(pos);
}

Terrain* Factory::createBlock0WallJump(sf::Vector2f pos, char type){
	return Block0WallJump::createBlock0WallJump(pos, type);
}

Terrain* Factory::createSpikes(sf::Vector2f pos, char type){
	return Spikes::createSpikes(pos, type);
}

Terrain* Factory::createGoal(sf::Vector2f pos) {
	return BlockGoal::createGoal(pos);
}

Decoration* Factory::createDecoration(sf::Vector2f pos, char id, char layer) {
	return Decoration::createDecoration(pos, id, layer);
}

BlockTerrain* Factory::createCollisionBlock(sf::Vector2f pos) {
	return CollisionBlock::createCollisionBlock(pos);
}