#include "Terrainhandler.h"

Terrainhandler::Terrainhandler(){
}

Terrainhandler::~Terrainhandler(){
}

Terrainhandler& Terrainhandler::getInstance(){
	static Terrainhandler terrainhandler;
	return terrainhandler;
}

void Terrainhandler::addTerrain(Terrain* terrain){
	mTerrains.push_back(terrain);
}

void Terrainhandler::addCollisionblock(BlockTerrain* blockterrain){
	mCollisionBlocks.push_back(blockterrain);
}

void Terrainhandler::renderTerrains(sf::RenderWindow &window){
	for (Terrains::size_type i = 0; i < mTerrains.size(); i++){
		if (mTerrains[i]->getType() != Terrain::MEATBALLSPAWNER) {
			mTerrains[i]->render(window);
		}
	}
	for (BlockTerrains::size_type i = 0; i < mCollisionBlocks.size(); i++) {
		mCollisionBlocks[i]->render(window);
	}
}

void Terrainhandler::updateTerrains(){
	for (Terrains::size_type i = 0; i < mTerrains.size(); i++){
		mTerrains[i]->update();
	}
}

void Terrainhandler::clear(){
	Terrainhandler::internalClear();
}




// Private funcs

void Terrainhandler::internalClear(){
	while (!mTerrains.empty()){
		delete mTerrains.back();
		mTerrains.pop_back();
	}
	while (!mCollisionBlocks.empty()) {
		delete mCollisionBlocks.back();
		mCollisionBlocks.pop_back();
	}
}