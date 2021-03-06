#include "Terrainhandler.h"
#include <iostream>

Terrainhandler::Terrainhandler(){
}

Terrainhandler::~Terrainhandler(){
	internalClear();
}

Terrainhandler* Terrainhandler::getInstance(){
	static Terrainhandler terrainhandler;
	return &terrainhandler;
}

void Terrainhandler::add(sf::Vector2f pos, char id, char type, char layer) {

	switch (id) {
	case '2':
		mTerrains.push_back(Factory::createSpikes(pos, type));
		break;
	case '3':
		mTerrains.push_back(Factory::createGoal(pos));
		break;
	case '4':
		mTerrains.push_back(Factory::createMeatballSpawner(pos));
		break;
	case '01':
		mCollisionBlocks.push_back(Factory::createCollisionBlock(pos));
		break;
	default:
		break;
	}
}

void Terrainhandler::createEvent(sf::Vector2f pos, Level *level, char eventType, sf::Vector2f size) {
	mTerrains.push_back(Factory::createEvent(pos, level, eventType, size));
}


void Terrainhandler::render(sf::RenderWindow &window) {
	for (auto i : mTerrains) {
		if (i->getType() != Terrain::MEATBALLSPAWNER) {
			i->render(window);
		}
	}
	for (auto i : mCollisionBlocks)
		i->render(window);
}

void Terrainhandler::update() {
	for (auto i : mTerrains)
		i->update();
}

void Terrainhandler::clear(){
	Terrainhandler::internalClear();
}

void Terrainhandler::addCollisionblock(BlockTerrain* blockterrain) {
	mCollisionBlocks.push_back(blockterrain);
}

void Terrainhandler::bringOutTheDead(){
	for (Terrains::size_type i = 0; i < mTerrains.size(); i++) {
		if (!mTerrains[i]->getIsAlive()) {
			delete mTerrains[i];
			mTerrains.erase(mTerrains.begin() + i);
		}
	}
}


//void Terrainhandler::addTerrain(Terrain* terrain){
//	mTerrains.push_back(terrain);
//}
//
//void Terrainhandler::addCollisionblock(BlockTerrain* blockterrain){
//	mCollisionBlocks.push_back(blockterrain);
//}
//
//void Terrainhandler::renderTerrains(sf::RenderWindow &window){
//	for (Terrains::size_type i = 0; i < mTerrains.size(); i++){
//		if (mTerrains[i]->getType() != Terrain::MEATBALLSPAWNER) {
//			mTerrains[i]->render(window);
//		}
//	}
//	for (BlockTerrains::size_type i = 0; i < mCollisionBlocks.size(); i++) {
//		mCollisionBlocks[i]->render(window);
//	}
//}
//
//void Terrainhandler::updateTerrains(){
//	for (Terrains::size_type i = 0; i < mTerrains.size(); i++){
//		mTerrains[i]->update();
//	}
//}




// Private funcs

void Terrainhandler::internalClear(){
	while (!mTerrains.empty()){
		delete mTerrains.back();
		mTerrains.pop_back();
	}
	while (!mCollisionBlocks.empty()) {
		mCollisionBlocks.back()->clear();
		delete mCollisionBlocks.back();
		mCollisionBlocks.pop_back();
	}
}