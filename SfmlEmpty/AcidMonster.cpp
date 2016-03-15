#include "AcidMonster.h"
#include <iostream>

static float ANIFramesPerFrame(0.25);

AcidMonster::AcidMonster(sf::Vector2f pos):
mSoundFX(SoundFactory::getTummySound()),
mIsOnScreen(true),
mIsAlive(true),
mAcceleration(4.3),
mMaxSpeed(-4.3), // 4.3 // 258
mCollisionBodyOffset(-60,-60){
	if (Toolbox::getCurrentLevelName() == "Stomach") {
		//mCurrentAnimation(Animations::getAcidMonsterVertical()),
		mCurrentAnimation = Animations::getAcidMonsterHorizontal();
		mSprite.setScale(sf::Vector2f(2.f, 2.f));
		mCollisionBody.setScale(sf::Vector2f(2.f, 2.f));
		mSprite.setTexture(*mCurrentAnimation->at(0));
		mCollisionBody.setTextureRect(sf::IntRect(0, 0, mSprite.getTextureRect().width + mCollisionBodyOffset.x, mSprite.getTextureRect().height + mCollisionBodyOffset.y));
	}
	if (Toolbox::getCurrentLevelName() == "Throat") {
		mCurrentAnimation = Animations::getAcidMonsterVertical();
		mSprite.setScale(sf::Vector2f(2.f, 2.f));
		mCollisionBody.setScale(sf::Vector2f(2.f, 2.f));
		mSprite.setTexture(*mCurrentAnimation->at(0));
		mCollisionBody.setTextureRect(sf::IntRect(0, 0, mSprite.getTextureRect().width, mSprite.getTextureRect().height + mCollisionBodyOffset.y));
		
	}

	mSpriteOffset = sf::Vector2f(mCollisionBody.getLocalBounds().width / 2, mCollisionBody.getLocalBounds().height / 2);
	mCollisionBody.setPosition(pos - mSpriteOffset);
}

AcidMonster::~AcidMonster(){
}

Entity* AcidMonster::createAcidMonster(sf::Vector2f pos){
	return new AcidMonster(pos);
}

void AcidMonster::render(sf::RenderWindow &window) {
	AcidMonster::updateTexturepos();
	window.draw(mSprite);
}

void AcidMonster::update(){
	ANIFramesPerFrame = 7.8 * Toolbox::getFrameTime();

	if (Toolbox::getCurrentLevelName() == "Stomach") {
		mVelocityGoal.y = 0.f;
		mVelocity.y = 0.f;
		mMaxSpeed = -10.f;
		mCurrentAnimation = Animations::getAcidMonsterHorizontal();
		//mSprite.setTexture(*mCurrentAnimation->at(0));
		mCollisionBody.setTextureRect(sf::IntRect(0, 0, mSprite.getTextureRect().width + mCollisionBodyOffset.x, mSprite.getTextureRect().height + mCollisionBodyOffset.y));
		mSpriteOffset = sf::Vector2f(mCollisionBody.getLocalBounds().width / 2, mCollisionBody.getLocalBounds().height / 2);
		mVelocityGoal.x = -mMaxSpeed;
	}
	else if (Toolbox::getCurrentLevelName() == "Throat") {
		mVelocityGoal.x = 0.f;
		mVelocity.x = 0.f;
		mMaxSpeed = -4.3f;
		mCurrentAnimation = Animations::getAcidMonsterVertical();
		//mSprite.setTexture(*mCurrentAnimation->at(0));
		mCollisionBody.setTextureRect(sf::IntRect(0, 0, mSprite.getTextureRect().width + mCollisionBodyOffset.x, mSprite.getTextureRect().height + mCollisionBodyOffset.y));
		mSpriteOffset = sf::Vector2f(mCollisionBody.getLocalBounds().width / 2, mCollisionBody.getLocalBounds().height / 2);
		mVelocityGoal.y = mMaxSpeed;
	}



	AcidMonster::lerp();

	AcidMonster::updateState();

	AcidMonster::animate();

	if (Toolbox::getPlayerIsAlive()){
		mCollisionBody.move(mVelocity);
	}

	AcidMonster::updateSound();

	AcidMonster::playSound(mState);
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

void AcidMonster::updateTexturepos() {
	sf::Vector2f temp(mCollisionBody.getPosition() + mSpriteOffset);
	temp.x -= (mSprite.getLocalBounds().width / 2);
	temp.y -= (mSprite.getLocalBounds().height / 2);
	mSprite.setPosition(temp);
	//std::cout << "X: " << mCollisionBody.getPosition().x << std::endl;
	//std::cout << "Y: " << mCollisionBody.getPosition().y << std::endl;
}

void AcidMonster::lerp(){

	bool lerpedY(false);
	bool lerpedX(false);

	//if (Toolbox::getFrameTime() > 0) {
		if (mVelocityGoal.y > mMaxSpeed) {
			mVelocityGoal.y = mMaxSpeed;
		}
	//}
	
	float delta = mAcceleration * 0.016;
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

void AcidMonster::addSpeed(){
	if (mVelocityGoal.x < mMaxSpeed && mVelocityGoal.x > 0)
	mVelocity.x += mAcceleration;
	if (mVelocityGoal.x > -mMaxSpeed && mVelocityGoal.x <= 0)
	mVelocity.x -= mAcceleration;
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

void AcidMonster::playSound(ACIDMONSTERSTATE state) {
	switch (state) {
	case AcidMonster::MOVINGRIGHT:
		mSoundFX.playSound(SoundFX::RUNNING);
		break;
	case AcidMonster::MOVINGUP:
		mSoundFX.playSound(SoundFX::RUNNING);
		break;
	default:
		break;
	}
}

void AcidMonster::stopSound(ACIDMONSTERSTATE state) {
	switch (state) {
	case AcidMonster::MOVINGRIGHT:
		mSoundFX.stopSound(SoundFX::RUNNING);
		break;
	case AcidMonster::MOVINGUP:
		mSoundFX.stopSound(SoundFX::RUNNING);
		break;
	default:
		break;
	}
}

void AcidMonster::updateSound() {
	sf::Vector2f playerPos = Toolbox::getPlayerPosition();
	sf::Vector2f tummyPos = this->getPos();
	float volume = calculateVolume(playerPos, tummyPos);
	mSoundFX.updateSound(SoundFX::RUNNING, volume);
}

float AcidMonster::calculateVolume(sf::Vector2f &pos1, sf::Vector2f &pos2) {
	float distanceBetween;
	if (mState == MOVINGUP) {
		distanceBetween = abs(pos1.y / pos2.y);
	} else if (mState == MOVINGRIGHT) {
		distanceBetween = abs(pos1.x / pos2.x);
	}
	float exp = pow(0.1f, distanceBetween);
	float invertedVolume = abs(exp * 1000 - 100) * 10;
	float volume = 100 - invertedVolume;

	return volume;
}

void AcidMonster::getHit(){

}

void AcidMonster::setPos(sf::Vector2f newPos){
	mCollisionBody.setPosition(newPos);
}

void AcidMonster::setAnimation() {
	switch (mState) {
	case AcidMonster::MOVINGRIGHT:
		mCurrentAnimation = Animations::getAcidMonsterHorizontal();
		break;
	case AcidMonster::MOVINGUP:
		mCurrentAnimation = Animations::getAcidMonsterVertical();
		break;
	default:
		break;
	}
}