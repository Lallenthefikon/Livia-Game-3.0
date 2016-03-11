#include "ExtraLife.h"

static float ANIFramesPerFrame(31.25);

ExtraLife::ExtraLife(sf::Vector2f pos) :
	mCurrentAnimation(Animations::getHeartANI()),
	mIsAlive(true) {
	mSprite.setTexture(*mCurrentAnimation->at(0));
	mSpriteOffset = sf::Vector2f(mSprite.getLocalBounds().width / 2, mSprite.getLocalBounds().height / 2);
	mSprite.setPosition(pos - mSpriteOffset);
}


Entity* ExtraLife::createExtraLife(sf::Vector2f pos) {
	return new ExtraLife(pos);
}

ExtraLife::~ExtraLife() {
}

void ExtraLife::render(sf::RenderWindow &window) {
	window.draw(mSprite);
}

void ExtraLife::update() {
	ANIFramesPerFrame = 31.25 * Toolbox::getFrameTime();
	ExtraLife::animate();
}

void ExtraLife::addVector(sf::Vector2f &vector) {
}

void ExtraLife::entityCollision(Entity* entity, char direction) {
}

void ExtraLife::terrainCollision(Terrain* terrain, char direction) {
}

void ExtraLife::blockterrainCollision(BlockTerrain* blockterrain, char direction) {
}

void ExtraLife::getHit() {
	mIsAlive = false;
}

void ExtraLife::setPos(sf::Vector2f newPos) {
	mSprite.setPosition(newPos);
}

void ExtraLife::animate() {
	mTimer += ANIFramesPerFrame;

	if (mTimer >= 2) {
		mAnimationIndex += 1;
		mTimer = 0;
		if (mAnimationIndex >= mCurrentAnimation->size())
			mAnimationIndex = 0;
		if (mCurrentAnimation->size() > 0) {
			mSprite.setTexture(*mCurrentAnimation->at(mAnimationIndex));
		}
	}
}