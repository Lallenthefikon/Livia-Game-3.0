#include "Entityhandler.h"
#include <iostream>

Entityhandler::Entityhandler(){
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
		mEntities[i]->addVector(Toolbox::getGravity());
	}
	//std::cout << "Gravity: " << Toolbox::getGravity().y * Toolbox::getFrameTime() << " Frame time: " << Toolbox::getFrameTime() << std::endl;
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

void Entityhandler::keyReleased(sf::Keyboard::Key key){
	switch (key) {
	case sf::Keyboard::Space:
		mEntities[0]->keyReleased(key);
		break;
	default:
		break;
	}
}

// Private funcs

void Entityhandler::internalClear(){
	while (!mEntities.empty()){
		delete mEntities.back();
		mEntities.pop_back();
	}
}
