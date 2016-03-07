#include "Meatball.h"

static float ANIFramesPerFrame(0.25);

Meatball::Meatball(sf::Vector2f pos) :
mCurrentAnimation(Animations::getMeatballANI()),
mIsOnScreen(true),
mAcceleration(8),
mMaxSpeed(1250),
mIsAlive(true),
mLife(1) {
	mVelocityGoal.y = mMaxSpeed;
	mSprite.setTexture(*mCurrentAnimation->at(0));
	mSpriteOffset = sf::Vector2f(mSprite.getLocalBounds().width / 2, mSprite.getLocalBounds().height / 2);
	mSprite.setPosition(pos - mSpriteOffset);

	// Needs a texture to get bounds from
	randDirection();
}

Meatball::~Meatball() {
}


// Public
Entity * Meatball::createMeatball(sf::Vector2f pos) {
	return new Meatball(pos);
}

void Meatball::render(sf::RenderWindow & window) {
	window.draw(mSprite);
}

void Meatball::update() {
	Meatball::lerp();

	Meatball::updateCollision();

	Meatball::animate();
	
	mSprite.move(mVelocity);

	checkOutOfBounds();

}

void Meatball::addVector(sf::Vector2f & vector) {
	//mVelocityGoal += vector;
}

void Meatball::entityCollision(Entity * entity, char direction) {
	switch (entity->getType()) {
	case Entity::PLAYER:
		entity->getHit();
		break;
	default:
		break;
	}
}

void Meatball::terrainCollision(Terrain * terrain, char direction) {
	switch (terrain->getType()) {
	case Terrain::MEATBALLSPAWNER:
		//Meatball::kill();
		break;
	default:
		break;
	}
}

void Meatball::blockterrainCollision(BlockTerrain * blockterrain, char direction) {
}

void Meatball::getHit() {
}

void Meatball::setPos(sf::Vector2f newPos) {
	mSprite.setPosition(newPos);
}

// Private

void Meatball::lerp() {
	bool lerpedY(false);
	bool lerpedX(false);

	if (Toolbox::getFrameTime() > 0) {
		if (mVelocityGoal.y > mMaxSpeed * Toolbox::getFrameTime()) {
			mVelocityGoal.y = mMaxSpeed * Toolbox::getFrameTime();
		}
	}
	
	float delta = mAcceleration * Toolbox::getFrameTime();
	float differenceX = mVelocityGoal.x - mVelocity.x;
	float differenceY = mVelocityGoal.y - mVelocity.y;


	// Interpolates the velocity up from stationary
	if (differenceX > delta) {
		mVelocity.x += delta;
		lerpedX = true;
	}
	// Interpolates the velocity up from stationary
	if (differenceY > delta) {
		mVelocity.y += delta;
		lerpedY = true;
	}
	// Interpolates the velocity down to stationary
	if (differenceX < -delta) {
		mVelocity.x += -delta;
		lerpedX = true;
	}
	// Interpolates the velocity down to stationary
	if (differenceY < -delta) {
		mVelocity.y += -delta;
		lerpedY = true;
	}

	// Max velocity
	if (!lerpedY)
		mVelocity.y = mVelocityGoal.y;
	if (!lerpedX)
		mVelocity.x = mVelocityGoal.x;
}

void Meatball::updateState() {
}

void Meatball::updateANI() {
	ANIFramesPerFrame = 31.25 * Toolbox::getFrameTime();
}

void Meatball::updateCollision() {
}

void Meatball::animate() {
	mTimer += ANIFramesPerFrame;

	if (mTimer >= 1) {
		mAnimationIndex += 1;
		mTimer = 0;
		if (mAnimationIndex >= mCurrentAnimation->size()) {
			mAnimationIndex = 0;
		}

		if (mCurrentAnimation->size() > 0)
			mSprite.setTexture(*mCurrentAnimation->at(mAnimationIndex));
	}
}

void Meatball::randDirection() {
	float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	if (r < 0.5) {
		mSprite.setTextureRect(sf::IntRect(0, 0, mSprite.getLocalBounds().width, mSprite.getLocalBounds().height));
	} else {
		mSprite.setTextureRect(sf::IntRect(mSprite.getLocalBounds().width, 0, -mSprite.getLocalBounds().width, mSprite.getLocalBounds().height));
	}
	mSprite.setTexture(*mCurrentAnimation->at(0));
}

void Meatball::checkOutOfBounds() {
	if (this->getPos().y > Toolbox::getLevelBounds().top + Toolbox::getLevelBounds().height + this->getHeight()) {
		Meatball::kill();
	}
}

void Meatball::kill() {
	mIsAlive = false;
}
