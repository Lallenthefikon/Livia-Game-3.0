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

void Entityhandler::updateEntities(float &frameTime){
	// Adds gravity to all entities
	addVector();

	for (Entities::size_type i = 0; i < mEntities.size(); i++){
		mEntities[i]->update(frameTime);
	}
}

void Entityhandler::bringOutTheDead(){
	for (Entities::size_type i = 0; i < mEntities.size(); i++){
		if (!mEntities[i]->getIsAlive()){
			if (mEntities[i]->getType() == Entity::PLAYER){
				Entityhandler::gameOver();
			}
			else{
				delete mEntities[i];
				mEntities.erase(mEntities.begin() + i);
			}
		}
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

void Entityhandler::gameOver(){
	
}

int Entityhandler::getPlayerLife(){
	return mEntities[0]->getLife();
}

bool Entityhandler::isPlayerAlive() {
	if (mEntities[0]->getType() == Entity::PLAYER) {
		if (mEntities[0]->getLife() == 0) {
			return false;
		} else
			return true;
	} else
		return false;
}

// Private funcs

void Entityhandler::internalClear(){
	while (!mEntities.empty()){
		delete mEntities.back();
		mEntities.pop_back();
	}
}
