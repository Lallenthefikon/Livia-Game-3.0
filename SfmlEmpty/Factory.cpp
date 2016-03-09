#include "Factory.h"
#include "Player.h"
#include "Block0.h"
#include "Worm.h"
#include "AcidMonster.h"
#include "Meatball.h"
#include "Block0WallJump.h"
#include "Spikes.h"
#include "BlockGoal.h"
#include "Decoration.h"
#include "Dialogue.h"
#include "CollisionBlock.h"
#include "MeatballSpawner.h"
#include "Block0Icy.h"
#include "Germ.h"

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

Terrain* Factory::createDialogue(sf::Vector2f pos) {
	return Dialogue::createDialogue(pos);
}
Decoration* Factory::createDecoration(sf::Vector2f pos, char id, char layer) {
	return Decoration::createDecoration(pos, id, layer);
}

BlockTerrain* Factory::createCollisionBlock(sf::Vector2f pos) {
	return CollisionBlock::createCollisionBlock(pos);
}

Entity* Factory::createMeatball(sf::Vector2f pos) {
	return Meatball::createMeatball(pos);
}

Terrain* Factory::createMeatballSpawner(sf::Vector2f pos) {
	return MeatballSpawner::createMeatballSpawner(pos);
}

Terrain* Factory::createBlock0Icy(sf::Vector2f pos, char type) {
	return Block0Icy::createBlock0Icy(pos, type);
}

Entity* Factory::createGerm(sf::Vector2f pos) {
	return Germ::createGerm(pos);
}