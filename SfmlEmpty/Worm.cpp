#include "Worm.h"

static float ANIFramesPerFrame(0.5);

Worm::Worm(sf::Vector2f pos) :
mCurrentAnimation(Animations::getWormCrawlingANI()),
mIsOnScreen(true),
mAcceleration(8),
mMaxSpeed(4),
mIsAlive(true),
mLife(1),
mSoundFX(SoundFactory::getWormSound()){
	mVelocityGoal.x = -mMaxSpeed;
	mSprite.setTexture(*mCurrentAnimation->at(0));
	mSpriteOffset = sf::Vector2f(mSprite.getLocalBounds().width / 2, mSprite.getLocalBounds().height / 2);
	mSprite.setPosition(pos - mSpriteOffset);
}

Worm::~Worm(){
}

Entity* Worm::createWorm(sf::Vector2f pos){
	return new Worm(pos);
}

void Worm::render(sf::RenderWindow &window){
	window.draw(mSprite);
}

void Worm::update(){
	ANIFramesPerFrame = 15.625 * Toolbox::getFrameTime();

	Worm::addSpeed();
	Worm::lerp();
	Worm::updateCollision();
	Worm::updateState();
	Worm::animate();

	mSprite.move(mVelocity);
}

void Worm::addVector(sf::Vector2f &vector){
	mVelocity += vector;
}

void Worm::entityCollision(Entity* entity, char direction){
	switch (entity->getType()){
	case Entity::PLAYER:
		switch (direction){
		case 't':
			break;
		default:
			if(mState != DEATH)
				entity->getHit();
			break;
		}
	default:
		break;
	}
}

void Worm::terrainCollision(Terrain* terrain, char direction){
	
}

void Worm::blockterrainCollision(BlockTerrain * blockterrain, char direction){
	float delta;
	switch (blockterrain->getType()) {
	case Terrain::COLLISIONBLOCK:
		switch (direction) {

		case 't':
			mCollisionT = true;
			delta = mSprite.getPosition().y - blockterrain->getPos().y;
			mSprite.move(sf::Vector2f(0, blockterrain->getHeight() - delta + 1));
			mCurrentCollisionT = blockterrain;
			break;
		case 'b':
			mCollisionB = true;
			delta = blockterrain->getPos().y - mSprite.getPosition().y;
			mSprite.move(sf::Vector2f(0, delta - this->getHeight() - 1));
			mCurrentCollisionB = blockterrain;
			break;
		case 'l':
			mCollisionL = true;
			delta = mSprite.getPosition().x - blockterrain->getPos().x;
			mSprite.move(sf::Vector2f(blockterrain->getWidth() - delta + 1, 0));
			mCurrentCollisionL = blockterrain;
			break;
		case 'r':
			mCollisionR = true;
			delta = blockterrain->getPos().x - mSprite.getPosition().x;
			mSprite.move(sf::Vector2f(delta - this->getWidth(), 0));
			mCurrentCollisionR = blockterrain;
			break;

		default:
			break;
		}
	default:
		break;
	}
}


void Worm::getHit(){
	mLife--;
	Worm::playSound(DEATH);
}

// Privates

void Worm::lerp(){

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


void Worm::addSpeed(){
	/*if (mVelocityGoal.x < mMaxSpeed && mVelocityGoal.x > 0)
		mVelocity.x += mAcceleration;
	if (mVelocityGoal.x > -mMaxSpeed && mVelocityGoal.x <= 0)
		mVelocity.x -= mAcceleration;*/
}

void Worm::updateState(){
	bool changed(false);

	if (mLife <= 0 && mState != DEATH){
		mState = DEATH;
		changed = true;
	}

	if (mState != DEATH){

		if (mVelocity.x > 0 && mState != CRAWLINGRIGHT){
			mState = Worm::CRAWLINGRIGHT;
			changed = true;
		}

		if (mVelocity.x < 0 && mState != CRAWLINGLEFT){
			mState = Worm::CRAWLINGLEFT;
			changed = true;
		}
	}
	if (changed)
		Worm::updateANI();
}


void Worm::updateANI(){
	//mCurrentAnimation = Animations::getWormCrawlingANI();
	switch (mState){
	case Worm::CRAWLINGLEFT:
		mSprite.setTextureRect(sf::IntRect(0, 0, int(this->getWidth()), int(this->getHeight())));
		break;
	case Worm::CRAWLINGRIGHT:
		
		//mSprite.setScale(-1.f, 1.f);
		mSprite.setTextureRect(sf::IntRect(int(this->getWidth()), 0, int(-this->getWidth()), int(this->getHeight())));
		break;
		
	case Worm::DEATH:
		mCurrentAnimation = Animations::getWormDyingANI();
		mSprite.setTextureRect(sf::IntRect(0, 0, 78, 35));
		break;

	default:
		break;
	}
	mAnimationIndex = 0;
	mTimer = 0;
}

void Worm::updateCollision(){
	if (mCollisionT){
		if (!CollisionFuncs::currentCollisionT(mSprite, mCurrentCollisionT->getSprite())){
			mCollisionT = false;
		}
	}
	if (mCollisionB){
		if (!CollisionFuncs::currentCollisionB(mSprite, mCurrentCollisionB->getSprite())){
			mCollisionB = false;
		}
	}
	if (mCollisionL){
		if (!CollisionFuncs::currentCollisionL(mSprite, mCurrentCollisionL->getSprite())){
			mCollisionL = false;
		}
		else{
			mVelocityGoal.x = mMaxSpeed;
		}
	}
	if (mCollisionR){
		if (!CollisionFuncs::currentCollisionR(mSprite, mCurrentCollisionR->getSprite())){
			mCollisionR = false;
		}
		else{
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

	if (mCollisionB){
		switch (mCurrentCollisionB->getTileType(mSprite.getPosition(), mSprite.getGlobalBounds().width, 't')){

		case 'p':
			if (this->getPos().x < mCurrentCollisionB->getPos().x){
				mSprite.setPosition(mCurrentCollisionB->getPos().x, this->getPos().y);
				mVelocity.x = 0;
				mVelocityGoal.x = mMaxSpeed;
			}
			else if (this->getPos().x + this->getWidth() > mCurrentCollisionB->getPos().x + mCurrentCollisionB->getWidth()){
				mSprite.setPosition(mCurrentCollisionB->getPos().x + mCurrentCollisionB->getWidth() - this->getWidth(), this->getPos().y);
				mVelocity.x = 0;
				mVelocityGoal.x = -mMaxSpeed;
			}
			break;

		case 'o':
			if (this->getPos().x < mCurrentCollisionB->getPos().x){
				mSprite.setPosition(mCurrentCollisionB->getPos().x, this->getPos().y);
				mVelocity.x = 0;
				mVelocityGoal.x = mMaxSpeed;
			}
			else if (this->getPos().x + this->getWidth() > mCurrentCollisionB->getPos().x + mCurrentCollisionB->getWidth()){
				mSprite.setPosition(mCurrentCollisionB->getPos().x + mCurrentCollisionB->getWidth()- this->getWidth(), this->getPos().y);
				mVelocity.x = 0;
				mVelocityGoal.x = -mMaxSpeed;
			}
			break;

		case 'm':
			if (this->getPos().x < mCurrentCollisionB->getPos().x){
				mSprite.setPosition(mCurrentCollisionB->getPos().x, this->getPos().y);
				mVelocity.x = 0;
				mVelocityGoal.x = mMaxSpeed;
			}
			break;

		case 'l':	
			if (this->getPos().x + this->getWidth() > mCurrentCollisionB->getPos().x + mCurrentCollisionB->getWidth()){
				mSprite.setPosition(mCurrentCollisionB->getPos().x + mCurrentCollisionB->getWidth() - this->getWidth(), this->getPos().y);
				mVelocity.x = 0;
				mVelocityGoal.x = -mMaxSpeed;
			}
			break;

		case 'j':
			if (this->getPos().x < mCurrentCollisionB->getPos().x){
				mSprite.setPosition(mCurrentCollisionB->getPos().x, this->getPos().y);
				mVelocity.x = 0;
				mVelocityGoal.x = mMaxSpeed;
			}
			break;

		case 'i':
			if (this->getPos().x + this->getWidth() > mCurrentCollisionB->getPos().x + mCurrentCollisionB->getWidth()){
				mSprite.setPosition(mCurrentCollisionB->getPos().x + mCurrentCollisionB->getWidth() - this->getWidth(), this->getPos().y);
				mVelocity.x = 0;
				mVelocityGoal.x = -mMaxSpeed;
			}
			break;
		default:
			break;
		}
	}
}

void Worm::animate(){
	mTimer += ANIFramesPerFrame;

	if (mTimer >= 1){
		mAnimationIndex += 1;
		mTimer = 0;
		if (mAnimationIndex >= mCurrentAnimation->size()){
			if (mState == DEATH){
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

void Worm::playSound(WORMSTATE state) {
	switch (state) {
	case Worm::CRAWLINGLEFT:
		break;
	case Worm::CRAWLINGRIGHT:
		break;
	case Worm::DEATH:
		mSoundFX.playSound(SoundFX::SOUNDTYPE::DEATH);
		break;
	default:
		break;
	}
}

void Worm::setPos(sf::Vector2f newPos){
	mSprite.setPosition(newPos);
}