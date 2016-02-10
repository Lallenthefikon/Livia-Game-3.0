#include "Worm.h"

static const float ANIFramesPerFrame(0.5);

Worm::Worm(sf::Vector2f pos) :
mCurrentAnimation(Animations::getWormCrawlingLeftANI()),
mIsOnScreen(true),
mAcceleration(8),
mMaxSpeed(8),
mIsAlive(true){
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
			entity->getHit();
			break;
		}
	default:
		break;
	}
}

void Worm::terrainCollision(Terrain* terrain, char direction){
	float delta;
	switch (terrain->getType())	{
	case Terrain::BLOCK0:
		switch (direction){

		case 't':
			mCollisionT = true;
			delta = mSprite.getPosition().y - terrain->getPos().y;
			mSprite.move(sf::Vector2f(0, terrain->getHeight() - delta + 1));
			mCurrentCollisionT = terrain;
			break;
		case 'b':
			mCollisionB = true;
			delta = terrain->getPos().y - mSprite.getPosition().y;
			mSprite.move(sf::Vector2f(0, delta - this->getHeight() - 1));
			mCurrentCollisionB = terrain;
			break;
		case 'l':
			mCollisionL = true;
			delta = mSprite.getPosition().x - terrain->getPos().x;
			mSprite.move(sf::Vector2f(terrain->getWidth() - delta + 1, 0));
			mCurrentCollisionL = terrain;
			break;
		case 'r':
			mCollisionR = true;
			delta = terrain->getPos().x - mSprite.getPosition().x;
			mSprite.move(sf::Vector2f(delta - this->getWidth(), 0));
			mCurrentCollisionR = terrain;
			break;

		default:
			break;
		}
	default:
		break;
	}
}

void Worm::getHit(){
	mIsAlive = false;
}

// Privates

void Worm::lerp(){

	bool lerpedY(false);
	bool lerpedX(false);

	float delta = 0.016 *mAcceleration;
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
	if (mVelocity.x > 0){
		mState = Worm::CRAWLINGRIGHT;
		Worm::updateANI();
	}

	if (mVelocity.x < 0){
		mState = Worm::CRAWLINGLEFT;
		Worm::updateANI();
	}
}


void Worm::updateANI(){
	switch (mState){
	case Worm::CRAWLINGLEFT:
		mCurrentAnimation = Animations::getWormCrawlingLeftANI();
		break;
	case Worm::CRAWLINGRIGHT:
		mCurrentAnimation = Animations::getWormCrawlingRightANI();
		break;
	default:
		break;
	}
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
}

void Worm::animate(){
	mTimer += ANIFramesPerFrame;

	if (mTimer >= 1){
		mAnimationIndex += 1;
		mTimer = 0;
		if (mAnimationIndex >= mCurrentAnimation->size())
			mAnimationIndex = 0;
		if (mCurrentAnimation->size() > 0)
			mSprite.setTexture(*mCurrentAnimation->at(mAnimationIndex));
	}
}