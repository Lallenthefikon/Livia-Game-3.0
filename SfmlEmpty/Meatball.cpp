#include "Meatball.h"

static float ANIFramesPerFrame(0.25);

Meatball::Meatball(sf::Vector2f pos) :
mCurrentAnimation(Animations::getMeatballANI()),
mIsOnScreen(true),
mAcceleration(8),
mMaxSpeed(1250),
mIsAlive(true),
mLife(1),
mCollisionBodyOffset(-30,-30){
	mSprite.setTexture(*mCurrentAnimation->at(0));
	//mCollisionBody.setTexture(*mCurrentAnimation->at(0));
	mCollisionBody.setTextureRect(sf::IntRect(0, 0, mSprite.getTextureRect().width + mCollisionBodyOffset.x, mSprite.getTextureRect().height + mCollisionBodyOffset.y));
	mSpriteOffset = sf::Vector2f(mCollisionBody.getLocalBounds().width / 2, mCollisionBody.getLocalBounds().height / 2);
	mCollisionBody.setPosition(pos - mSpriteOffset);
}


Meatball::~Meatball() {
}


// Public
Entity * Meatball::createMeatball(sf::Vector2f pos) {
	return new Meatball(pos);
}

void Meatball::render(sf::RenderWindow & window) {
	Meatball::updateTexturepos();
	window.draw(mSprite);
//	window.draw(mCollisionBody);
}

void Meatball::update() {
	mVelocityGoal.y = mMaxSpeed;
	Meatball::lerp();

	Meatball::updateCollision();

	Meatball::animate();
	
	mCollisionBody.move(mVelocity);

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

void Meatball::updateTexturepos() {
	sf::Vector2f temp(mCollisionBody.getPosition() + mSpriteOffset);
	temp.x -= (mSprite.getLocalBounds().width / 2);
	temp.y -= (mSprite.getLocalBounds().height / 2);
	mSprite.setPosition(temp);
	//std::cout << "X: " << mCollisionBody.getPosition().x << std::endl;
	//std::cout << "Y: " << mCollisionBody.getPosition().y << std::endl;
}

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
