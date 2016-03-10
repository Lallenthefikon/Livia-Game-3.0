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

Entityhandler* Entityhandler::getInstance(){
	static Entityhandler entityhandler;
	return &entityhandler;
}

void Entityhandler::add(sf::Vector2f pos, char id, char type, char layer) {

	switch (id) {
	case '0':
		mEntities.push_back(Factory::createPlayer(pos));
		break;
	case '1':
		mEntities.push_back(Factory::createWorm(pos));
		break;
	case '2':
		mEntities.push_back(Factory::createAcidMonster(pos));
		break;
	case '3':
		mEntities.push_back(Factory::createMeatball(pos));
		break;
	case '4':
		mEntities.push_back(Factory::createExtraLife(pos));
		break;
	case '5':
		mEntities.push_back(Factory::createGerm(pos));
		break;
	default:
		break;
	}
}

void Entityhandler::bringOutTheDead() {
	for (Entities::size_type i = 0; i < mEntities.size(); i++) {
		if (!mEntities[i]->getIsAlive()) {
			if (mEntities[i]->getType() == Entity::PLAYER) {
				//Entityhandler::gameOver();
			} else {
				delete mEntities[i];
				mEntities.erase(mEntities.begin() + i);
			}
}
}
}

int Entityhandler::getPlayerLife() {
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

void Entityhandler::render(sf::RenderWindow& window) {
	for (auto i : mEntities)
		i->render(window);
}

void Entityhandler::update() {
	addVector();
	sortEntities();
	for (auto i : mEntities)
		i->update();
}

//void Entityhandler::renderEntities(sf::RenderWindow &window){
//	for (Entities::size_type i = 0; i < mEntities.size(); i++){
//		mEntities[i]->render(window);
//	}
//}
//
//void Entityhandler::updateEntities(){
//	// Adds gravity to all entities
//	addVector();
//
//	for (Entities::size_type i = 0; i < mEntities.size(); i++){
//		mEntities[i]->update();
//	}
//}
//
//void Entityhandler::bringOutTheDead(){
//	for (Entities::size_type i = 0; i < mEntities.size(); i++){
//		if (!mEntities[i]->getIsAlive()){
//			if (mEntities[i]->getType() == Entity::PLAYER){
//				Entityhandler::gameOver();
//			}
//			else{
//				delete mEntities[i];
//				mEntities.erase(mEntities.begin() + i);
//			}
//		}
//	}
//}
//
//void Entityhandler::addEntity(Entity* entity){
//	mEntities.push_back(entity);
//}
//
//void Entityhandler::addVector(){
//	for (Entities::size_type i = 0; i < mEntities.size(); i++){
//		mEntities[i]->addVector(Toolbox::getGravity() * Toolbox::getFrameTime());
//	}
//	//std::cout << "'EnHa' Gravity: " << Toolbox::getGravity().y * Toolbox::getFrameTime() << " Frame time: " << Toolbox::getFrameTime() << " FPS: " << 1.f / Toolbox::getFrameTime() << std::endl;
//}
//
//void Entityhandler::gameOver(){
//	
//}
//
//int Entityhandler::getPlayerLife(){
//	return mEntities[0]->getLife();
//}
//
//bool Entityhandler::isPlayerAlive() {
//	if (mEntities[0]->getType() == Entity::PLAYER) {
//		if (mEntities[0]->getLife() == 0) {
//			return false;
//		} else
//			return true;
//	} else
//		return false;
//}


void Entityhandler::clear(){
	Entityhandler::internalClear();
}

// Private funcs

void Entityhandler::addVector() {
	for (auto i : mEntities)
		i->addVector(Toolbox::getGravity() * Toolbox::getFrameTime());
}

void Entityhandler::internalClear(){
	while (!mEntities.empty()){
		delete mEntities.back();
		mEntities.pop_back();
	}
}

void Entityhandler::sortEntities() {
	if (mEntities.back()->getType() != Entity::ACIDMONSTER) {
		Entity* temp;
		for (Entities::size_type i = 0; i < mEntities.size(); i++) {
			if (mEntities[i]->getType() == Entity::ACIDMONSTER) {
				temp = mEntities[i];
				mEntities.erase(mEntities.begin() + i);
				mEntities.push_back(temp);
			}
		}
	}
}
