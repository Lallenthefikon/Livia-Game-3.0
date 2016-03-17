#include "Octo_Pi.h"

static float ANIFramesPerFrame(0.5);

Octo_Pi::Octo_Pi(sf::Vector2f pos) :
	mCurrentAnimation(Animations::getGermWalkingANI()),
	mIsOnScreen(true),
	mAcceleration(8,70),
	mJumpspeed(30),
	mCollisionBodyOffset(-10, -10),
	mMaxSpeed(4),
	mIsAlive(true),
	mLife(1),
	mState(IMBOUNCINGHERE),
	mCurrentAnimationRate(15.643),
	mSoundFX(SoundFactory::getWormSound()) {
	mVelocityGoal.x = -mMaxSpeed;
	mSprite.setTexture(*mCurrentAnimation->at(0));
	//mCollisionBody.setTexture(*mCurrentAnimation->at(0));
	mCollisionBody.setTextureRect(sf::IntRect(0, 0, mSprite.getTextureRect().width + mCollisionBodyOffset.x, mSprite.getTextureRect().height + mCollisionBodyOffset.y));
	mSpriteOffset = sf::Vector2f(mCollisionBody.getGlobalBounds().width / 2, mCollisionBody.getGlobalBounds().height / 2);
	mCollisionBody.setPosition(pos - mSpriteOffset);
	Octo_Pi::updateTexturepos();
}

Octo_Pi::~Octo_Pi() {
}

Entity* Octo_Pi::createOcto_Pi(sf::Vector2f pos) {
	return new Octo_Pi(pos);
}

void Octo_Pi::render(sf::RenderWindow &window) {
	Octo_Pi::updateTexturepos();
	window.draw(mSprite);
	//window.draw(mCollisionBody);
}

void Octo_Pi::update() {
	ANIFramesPerFrame = mCurrentAnimationRate * Toolbox::getFrameTime();

	Octo_Pi::updateCollision();
	Octo_Pi::addSpeed();
	Octo_Pi::updateState();
	Octo_Pi::animate();
	Octo_Pi::lerp();

	mCollisionBody.move(mVelocity);
}



void Octo_Pi::addVector(sf::Vector2f &vector) {
	mVelocityGoal += vector;
}

void Octo_Pi::entityCollision(Entity* entity, char direction) {
	switch (entity->getType()) {
	case Entity::PLAYER:
		switch (direction) {
		case 't':
			break;
		default:
			if (mLife > 0)
			entity->getHit();
			break;
		}
		break;
	default:
		break;
	}
}

void Octo_Pi::terrainCollision(Terrain* terrain, char direction) {

}

void Octo_Pi::blockterrainCollision(BlockTerrain * blockterrain, char direction) {
	float delta;
	switch (blockterrain->getType()) {
	case Terrain::COLLISIONBLOCK:
		switch (direction) {

		case 't':
			mCollisionT = true;
			delta = mCollisionBody.getPosition().y - blockterrain->getPos().y;
			mCollisionBody.move(sf::Vector2f(0, blockterrain->getHeight() - delta + 1));
			mCurrentCollisionT = blockterrain;
			break;
		case 'b':
			mCollisionB = true;
			delta = blockterrain->getPos().y - mCollisionBody.getPosition().y;
			mCollisionBody.move(sf::Vector2f(0, delta - this->getHeight() - 1));
			mCurrentCollisionB = blockterrain;
			break;
		case 'l':
			mCollisionL = true;
			delta = mCollisionBody.getPosition().x - blockterrain->getPos().x;
			mCollisionBody.move(sf::Vector2f(blockterrain->getWidth() - delta + 1, 0));
			mCurrentCollisionL = blockterrain;
			break;
		case 'r':
			mCollisionR = true;
			delta = blockterrain->getPos().x - mCollisionBody.getPosition().x;
			mCollisionBody.move(sf::Vector2f(delta - this->getWidth(), 0));
			mCurrentCollisionR = blockterrain;
			break;

		default:
			break;
		}
	default:
		break;
	}
}


void Octo_Pi::getHit() {
	mLife--;
	Octo_Pi::playSound(DEATH);
}


// Privates

void Octo_Pi::updateTexturepos() {
	sf::Vector2f temp(mCollisionBody.getPosition() + mSpriteOffset);
	temp.x -= (mSprite.getLocalBounds().width / 2);
	temp.y -= (mSprite.getLocalBounds().height / 2);
	mSprite.setPosition(temp);
	//std::cout << "X: " << mCollisionBody.getPosition().x << std::endl;
	//std::cout << "Y: " << mCollisionBody.getPosition().y << std::endl;
}

void Octo_Pi::lerp() {

	bool lerpedY(false);
	bool lerpedX(false);

	sf::Vector2f delta(Toolbox::getFrameTime() * mAcceleration.x, Toolbox::getFrameTime() * mAcceleration.y);
	float differenceX = mVelocityGoal.x - mVelocity.x;
	float differenceY = mVelocityGoal.y - mVelocity.y;

	if (mVelocityGoal.y > 2500 * Toolbox::getFrameTime()) {
		mVelocityGoal.y = 2500 * Toolbox::getFrameTime();
	}

	// Interpolates the velocity up from stationary
	if (differenceX > delta.x) {
		mVelocity.x += delta.x;
		lerpedX = true;
	}
	// Interpolates the velocity up from stationary
	if (differenceY > delta.y) {
		mVelocity.y += delta.y;
		lerpedY = true;
	}
	// Interpolates the velocity down to stationary
	if (differenceX < -delta.x) {
		mVelocity.x += -delta.x;
		lerpedX = true;
	}
	// Interpolates the velocity down to stationary
	if (differenceY < -delta.y) {
		mVelocity.y += -delta.y;
		lerpedY = true;
	}

	// Max velocity

	if (!lerpedY)
		mVelocity.y = mVelocityGoal.y;
	if (!lerpedX)
		mVelocity.x = mVelocityGoal.x;
}




void Octo_Pi::addSpeed() {
	if (mCollisionT && mVelocity.y < 0)
		mVelocity.y = 0;
	if (mCollisionB && mVelocity.y > 0)
		mVelocity.y = -mJumpspeed;
	if (mCollisionL && mVelocity.x < 0)
		mVelocity.x *= -1;
	if (mCollisionR && mVelocity.x > 0)
		mVelocity.x *= -1;

}

void Octo_Pi::updateSpeed() {
	if (mState == DAMAGED) {
		mVelocityGoal.x = 0;
	}
	if (mState == IMBOUNCINGHERE) {
		if (mTurned == TURNEDLEFT)
			mVelocityGoal.x = -mMaxSpeed;
		if (mTurned == TURNEDRIGHT)
			mVelocityGoal.x = mMaxSpeed;
	}
}

void Octo_Pi::updateState() {
	bool changed(false);

	if (mLife <= 0 && mState != DEATH) {
		mState = DEATH;
		changed = true;
	}



	if (mState != DEATH) {
		if (mVelocity.x != 0 && mVelocity.y == 0 && mState != DAMAGED && mState != IMBOUNCINGHERE) {
			mState = IMBOUNCINGHERE;
			changed = true;
		}

		if (mVelocity.x > 0 && mTurned != TURNEDRIGHT) {
			mTurned = Octo_Pi::TURNEDRIGHT;
			changed = true;
		}

		if (mVelocity.x < 0 && mTurned != TURNEDLEFT) {
			mTurned = Octo_Pi::TURNEDLEFT;
			changed = true;
		}
	}
	if (changed) {
		Octo_Pi::updateANI();
		Octo_Pi::updateSpeed();
	}
}


void Octo_Pi::updateANI() {
	//mCurrentAnimation = Animations::getWormCrawlingANI();
	switch (mState) {
	case Octo_Pi::IMBOUNCINGHERE:
		mCurrentAnimation = Animations::getGermWalkingANI();
		mSprite.setTextureRect(sf::IntRect(0, 0, 80, 130));
		mCurrentAnimationRate = 31.250;
		break;
	case Octo_Pi::DEATH:
		mCurrentAnimation = Animations::getGermDamagedANI();
		mSprite.setTextureRect(sf::IntRect(0, 0, 65, 130));
		mCurrentAnimationRate = 15.625;
		break;
	default:
		break;
	}
	if (mTurned == TURNEDLEFT)
		mSprite.setTextureRect(sf::IntRect(0, 0, mSprite.getLocalBounds().width, mSprite.getLocalBounds().height));

	if (mTurned == TURNEDRIGHT)
		mSprite.setTextureRect(sf::IntRect(mSprite.getLocalBounds().width, 0, -mSprite.getLocalBounds().width, mSprite.getLocalBounds().height));

	mAnimationIndex = 0;
	mTimer = 0;
}

void Octo_Pi::updateCollision() {
	if (mCollisionT) {
		if (!CollisionFuncs::currentCollisionT(mCollisionBody, mCurrentCollisionT->getSprite())) {
			mCollisionT = false;
		}
	}
	if (mCollisionB) {
		if (!CollisionFuncs::currentCollisionB(mCollisionBody, mCurrentCollisionB->getSprite())) {
			mCollisionB = false;
		}
	}
	if (mCollisionL) {
		if (!CollisionFuncs::currentCollisionL(mCollisionBody, mCurrentCollisionL->getSprite())) {
			mCollisionL = false;
		}
	}
	if (mCollisionR) {
		if (!CollisionFuncs::currentCollisionR(mCollisionBody, mCurrentCollisionR->getSprite())) {
			mCollisionR = false;
		}
	}


}

void Octo_Pi::animate() {
	mTimer += ANIFramesPerFrame;

	if (mTimer >= 1) {
		mAnimationIndex += 1;
		mTimer = 0;
		if (mAnimationIndex >= mCurrentAnimation->size()) {
			if (mState == DEATH) {
				mAnimationIndex -= 1;
				mIsAlive = false;
			}
			else
				mAnimationIndex = 0;
		}

		if (mCurrentAnimation->size() > 0)
			mSprite.setTexture(*mCurrentAnimation->at(mAnimationIndex));
	}
}

void Octo_Pi::playSound(OCTOSTATE state) {
	switch (state) {
	case Octo_Pi::DEATH:
		mSoundFX.playSound(SoundFX::SOUNDTYPE::DEATH);
		break;
	default:
		break;
	}
}

void Octo_Pi::setPos(sf::Vector2f newPos) {
	mCollisionBody.setPosition(newPos);
}