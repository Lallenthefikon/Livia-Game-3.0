#include "Germ.h"


static float ANIFramesPerFrame(0.5);

Germ::Germ(sf::Vector2f pos) :
	mCurrentAnimation(Animations::getGermWalkingANI()),
	mIsOnScreen(true),
	mAcceleration(8),
	mCollisionBodyOffset(-10,-10),
	mMaxSpeed(4),
	mIsAlive(true),
	mLife(5),
	mState(IMWALKINGHERE),
	mCurrentAnimationRate(15.643),
	mSoundFX(SoundFactory::getWormSound()) {
	mVelocityGoal.x = -mMaxSpeed;
	mSprite.setTexture(*mCurrentAnimation->at(0));
	//mCollisionBody.setTexture(*mCurrentAnimation->at(0));
	mCollisionBody.setTextureRect(sf::IntRect(0, 0, mSprite.getTextureRect().width + mCollisionBodyOffset.x, mSprite.getTextureRect().height + mCollisionBodyOffset.y));
	mSpriteOffset = sf::Vector2f(mCollisionBody.getGlobalBounds().width / 2, mCollisionBody.getGlobalBounds().height / 2);
	mCollisionBody.setPosition(pos - mSpriteOffset);
	Germ::updateTexturepos();
}

Germ::~Germ() {
}

Entity* Germ::createGerm(sf::Vector2f pos) {
	return new Germ(pos);
}

void Germ::render(sf::RenderWindow &window) {
	Germ::updateTexturepos();
	window.draw(mSprite);
	//window.draw(mCollisionBody);
}

void Germ::update() {
	ANIFramesPerFrame = mCurrentAnimationRate * Toolbox::getFrameTime();

	Germ::addSpeed();
	Germ::lerp();
	Germ::updateCollision();
	Germ::updateState();
	Germ::animate();

	mCollisionBody.move(mVelocity);
}

void Germ::addVector(sf::Vector2f &vector) {
	mVelocity += vector;
}

void Germ::entityCollision(Entity* entity, char direction) {
	switch (entity->getType()) {
	case Entity::PLAYER:
		switch (direction) {
		case 't':
			break;
		default:
			entity->getHit();
			break;
		}
	default:
		break;
	}
}

void Germ::terrainCollision(Terrain* terrain, char direction) {

}

void Germ::blockterrainCollision(BlockTerrain * blockterrain, char direction) {
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


void Germ::getHit() {
	mLife--;
	Germ::playSound(DEATH);
}


// Privates

void Germ::updateTexturepos() {
	sf::Vector2f temp(mCollisionBody.getPosition() + mSpriteOffset);
	temp.x -= (mSprite.getLocalBounds().width / 2);
	temp.y -= (mSprite.getLocalBounds().height / 2);
	mSprite.setPosition(temp);
	//std::cout << "X: " << mCollisionBody.getPosition().x << std::endl;
	//std::cout << "Y: " << mCollisionBody.getPosition().y << std::endl;
}

void Germ::lerp() {

	bool lerpedY(false);
	bool lerpedX(false);

	float delta = Toolbox::getFrameTime() * mAcceleration;
	float differenceX = mVelocityGoal.x - mVelocity.x;
	float differenceY = mVelocityGoal.y - mVelocity.y;

	if (mVelocityGoal.y > 40) {
		mVelocityGoal.y = 40;
	}

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


void Germ::addSpeed(){
}

void Germ::updateSpeed(){
	if (mState == DAMAGED) {
		mVelocityGoal.x = 0;
	}
	if (mState == IMWALKINGHERE) {
		if (mTurned == TURNEDLEFT)
			mVelocityGoal.x = -mMaxSpeed;
		if (mTurned == TURNEDRIGHT)
			mVelocityGoal.x = mMaxSpeed;
	}
}

void Germ::updateState() {
	bool changed(false);

	if (mLife <= 0 && mState != DEATH) {
		mState = DEATH;
		changed = true;
	}

	

	if (mState != DEATH) {
		if (mLife < 5) {
			mLife = 5;
			mState = DAMAGED;
			changed = true;
		}
		if (mLife > 5) {
			mLife = 5;
			mState = IMWALKINGHERE;
			changed = true;
		}

		if (mVelocity.x != 0 && mVelocity.y == 0 && mState != DAMAGED && mState != IMWALKINGHERE) {
			mState = IMWALKINGHERE;
			changed = true;
		}

		if (mVelocity.x > 0 && mTurned != TURNEDRIGHT) {
			mTurned = Germ::TURNEDRIGHT;
			changed = true;
		}

		if (mVelocity.x < 0 && mTurned != TURNEDLEFT) {
			mTurned = Germ::TURNEDLEFT;
			changed = true;
		}
	}
	if (changed) {
		Germ::updateANI();
		Germ::updateSpeed();
	}
}


void Germ::updateANI() {
	//mCurrentAnimation = Animations::getWormCrawlingANI();
	switch (mState) {
	case Germ::IMWALKINGHERE:
		mCurrentAnimation = Animations::getGermWalkingANI();
		mSprite.setTextureRect(sf::IntRect(0, 0, 80, 130));
		mCurrentAnimationRate = 31.250;
		break;
	case Germ::DAMAGED:
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

void Germ::updateCollision() {
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
		else {
			mVelocityGoal.x = mMaxSpeed;
		}
	}
	if (mCollisionR) {
		if (!CollisionFuncs::currentCollisionR(mCollisionBody, mCurrentCollisionR->getSprite())) {
			mCollisionR = false;
		}
		else {
			mVelocityGoal.x = -mMaxSpeed;
		}
	}

	if (mCollisionT && mVelocity.y < 0)
		mVelocity.y = 0;
	if (mCollisionB && mVelocity.y > 0)
		mVelocity.y = 0;
	if (mCollisionL && mVelocity.x < 0)
		mVelocity.x = 0;
	if (mCollisionR && mVelocity.x > 0)
		mVelocity.x = 0;

	if (mCollisionB) {
		switch (mCurrentCollisionB->getTileType(mCollisionBody.getPosition(), mCollisionBody.getGlobalBounds().width, 'b')) {

		case 'p':
			if (this->getPos().x < mCurrentCollisionB->getPos().x) {
				mCollisionBody.setPosition(mCurrentCollisionB->getPos().x, this->getPos().y);
				mVelocity.x = 0;
				mVelocityGoal.x = mMaxSpeed;
			}
			else if (this->getPos().x + this->getWidth() > mCurrentCollisionB->getPos().x + mCurrentCollisionB->getWidth()) {
				mCollisionBody.setPosition(mCurrentCollisionB->getPos().x + mCurrentCollisionB->getWidth() - this->getWidth(), this->getPos().y);
				mVelocity.x = 0;
				mVelocityGoal.x = -mMaxSpeed;
			}
			break;

		case 'o':
			if (this->getPos().x < mCurrentCollisionB->getPos().x) {
				mCollisionBody.setPosition(mCurrentCollisionB->getPos().x, this->getPos().y);
				mVelocity.x = 0;
				mVelocityGoal.x = mMaxSpeed;
			}
			else if (this->getPos().x + this->getWidth() > mCurrentCollisionB->getPos().x + mCurrentCollisionB->getWidth()) {
				mCollisionBody.setPosition(mCurrentCollisionB->getPos().x + mCurrentCollisionB->getWidth() - this->getWidth(), this->getPos().y);
				mVelocity.x = 0;
				mVelocityGoal.x = -mMaxSpeed;
			}
			break;

		case 'm':
			if (this->getPos().x < mCurrentCollisionB->getPos().x) {
				mCollisionBody.setPosition(mCurrentCollisionB->getPos().x, this->getPos().y);
				mVelocity.x = 0;
				mVelocityGoal.x = mMaxSpeed;
			}
			break;

		case 'l':
			if (this->getPos().x + this->getWidth() > mCurrentCollisionB->getPos().x + mCurrentCollisionB->getWidth()) {
				mCollisionBody.setPosition(mCurrentCollisionB->getPos().x + mCurrentCollisionB->getWidth() - this->getWidth(), this->getPos().y);
				mVelocity.x = 0;
				mVelocityGoal.x = -mMaxSpeed;
			}
			break;

		case 'j':
			if (this->getPos().x < mCurrentCollisionB->getPos().x) {
				mCollisionBody.setPosition(mCurrentCollisionB->getPos().x, this->getPos().y);
				mVelocity.x = 0;
				mVelocityGoal.x = mMaxSpeed;
			}
			break;

		case 'i':
			if (this->getPos().x + this->getWidth() > mCurrentCollisionB->getPos().x + mCurrentCollisionB->getWidth()) {
				mCollisionBody.setPosition(mCurrentCollisionB->getPos().x + mCurrentCollisionB->getWidth() - this->getWidth(), this->getPos().y);
				mVelocity.x = 0;
				mVelocityGoal.x = -mMaxSpeed;
			}
			break;
		default:
			break;
		}
	}
}

void Germ::animate() {
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

			if (mState == DAMAGED)
				mLife++;
		}

		if (mCurrentAnimation->size() > 0)
			mSprite.setTexture(*mCurrentAnimation->at(mAnimationIndex));
	}
}

void Germ::playSound(GERMSTATE state) {
	switch (state) {
	case Germ::DEATH:
		mSoundFX.playSound(SoundFX::SOUNDTYPE::DEATH);
		break;
	default:
		break;
	}
}

void Germ::setPos(sf::Vector2f newPos) {
	mCollisionBody.setPosition(newPos);
}

void Germ::stopAllSound() {
	mSoundFX.stopAllSound();
}