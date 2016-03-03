#include "MeatballSpawner.h"
#include <iostream>


MeatballSpawner::MeatballSpawner(sf::Vector2f pos) :
mSpawnRate(0.01f),
mClock(),
mEntityHandler(Entityhandler::getInstance()){
	MeatballSpawner::setTexture();
	mSprite.setTexture(mTexture);
	mSpriteOffset = sf::Vector2f(mSprite.getLocalBounds().width / 2, mSprite.getLocalBounds().height / 2);
	mSprite.setPosition(pos - mSpriteOffset);
}


MeatballSpawner::~MeatballSpawner() {
}


Terrain* MeatballSpawner::createMeatballSpawner(sf::Vector2f pos) {
	return new MeatballSpawner(pos);
}

void MeatballSpawner::setTexture() {
	mTexture.loadFromImage(Toolbox::getTexture(Toolbox::TEXTUREKEY::MEATBALLSPAWNERTEXTURE));
}

void MeatballSpawner::render(sf::RenderWindow &window) {
	window.draw(mSprite);
}

void MeatballSpawner::update() {
	MeatballSpawner::spawnMeatball();
}

void MeatballSpawner::spawnMeatball() {
	float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	if (r < mSpawnRate && mClock.getElapsedTime().asSeconds() > 2.0f) {
		sf::Vector2f meatballPos = this->getPos();
		mEntityHandler.add(Meatball::createMeatball(meatballPos));

		meatballPos.y += mEntityHandler.getEntities().back()->getHeight() + 10;

		mEntityHandler.getEntities().back()->setPos(meatballPos);
		mClock.restart();
	}
}

void MeatballSpawner::setPos(sf::Vector2f newPos) {
	mSprite.setPosition(newPos);
}

