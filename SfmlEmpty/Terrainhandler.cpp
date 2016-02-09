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

void Terrainhandler::renderTerrains(sf::RenderWindow &window){
	for (Terrains::size_type i = 0; i < mTerrains.size(); i++){
		mTerrains[i]->render(window);
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
}