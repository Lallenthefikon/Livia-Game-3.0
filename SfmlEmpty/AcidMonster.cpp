#include "AcidMonster.h"

static const float ANIFramesPerFrame(0.5);

AcidMonster::AcidMonster(sf::Vector2f pos):
mCurrentAnimation(Animations::getAcidMonster()),
mIsOnScreen(true),
mIsAlive(true),
mAcceleration(8),
mMaxSpeed(4.5){
	mVelocityGoal.x = mMaxSpeed;
	mSprite.setTexture(*mCurrentAnimation->at(0));
	mSpriteOffset = sf::Vector2f(mSprite.getLocalBounds().width / 2, mSprite.getLocalBounds().height / 2);
	mSprite.setPosition(pos - mSpriteOffset);
}


AcidMonster::~AcidMonster()
{
}

Entity* AcidMonster::createAcidMonster(sf::Vector2f pos){
	return new AcidMonster(pos);
}

void AcidMonster::render(sf::RenderWindow &window){
	window.draw(mSprite);
}

void AcidMonster::update(){
	AcidMonster::addSpeed();
	AcidMonster::lerp();
	AcidMonster::updateState();
	AcidMonster::animate();

	if (Toolbox::getPlayerIsAlive()){
		mSprite.move(mVelocity);
	}
}

void AcidMonster::addVector(sf::Vector2f &vector){
	//mVelocity += vector;
}

void AcidMonster::entityCollision(Entity* entity, char direction){
}

void AcidMonster::terrainCollision(Terrain* terrain, char direction){
	/*float delta;
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
	}*/
}

void AcidMonster::blockterrainCollision(BlockTerrain * blockterrain, char direction){

}

// Privates

void AcidMonster::lerp(){

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

void AcidMonster::addSpeed(){
	/*if (mVelocityGoal.x < mMaxSpeed && mVelocityGoal.x > 0)
	mVelocity.x += mAcceleration;
	if (mVelocityGoal.x > -mMaxSpeed && mVelocityGoal.x <= 0)
	mVelocity.x -= mAcceleration;*/
}

void AcidMonster::updateState(){

}

void AcidMonster::updateANI(){
}

void AcidMonster::animate(){
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

void AcidMonster::getHit(){

}

void AcidMonster::setPos(sf::Vector2f newPos){
	mSprite.setPosition(newPos);
}