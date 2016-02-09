#include "Entityhandler.h"

Entityhandler::Entityhandler():
mGravity(sf::Vector2f(0, 2)){
}

Entityhandler::~Entityhandler(){
	while (!mEntities.empty()){
		delete mEntities.back();
		mEntities.pop_back();
	}
}

Entityhandler& Entityhandler::getInstance(){
	static Entityhandler entityhandler;
	return entityhandler;
}

void Entityhandler::renderEntities(sf::RenderWindow &window){
	for (Entities::size_type i = 0; i < mEntities.size(); i++){
		mEntities[i]->render(window);
	}
}

void Entityhandler::updateEntities(){
	// Adds gravity to all entities
	addVector();

	for (Entities::size_type i = 0; i < mEntities.size(); i++){
		mEntities[i]->update();
	}
}

void Entityhandler::addEntity(Entity* entity){
	mEntities.push_back(entity);
}

void Entityhandler::addVector(){
	for (Entities::size_type i = 0; i < mEntities.size(); i++){
		mEntities[i]->addVector(mGravity);
	}
}

void Entityhandler::clear(){
	Entityhandler::internalClear();
}

// Private funcs

void Entityhandler::internalClear(){
	while (!mEntities.empty()){
		delete mEntities.back();
		mEntities.pop_back();
	}
}
