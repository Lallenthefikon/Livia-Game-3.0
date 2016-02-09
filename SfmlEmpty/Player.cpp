#include "Player.h"
#include <iostream>

static float FRIKTION(0.5);
static const float ANIFramesPerFrame(0.5);

Player::Player(sf::Vector2f pos) :
mVelocity(0, 0),
mIsOnScreen(true),
mState(IDLE),

// Animatin stuff
mAnimationIndex(0),
mCurrentAnimation(Animations::getPlayerRunningANI()),
mTimer(1),

// Stats
mJumpSpeed(-32),
mMaxSpeed(15),
mSpeed(70){

	mSprite.setTexture(*mCurrentAnimation->at(0));
	mSpriteOffset = sf::Vector2f(mSprite.getGlobalBounds().width / 2, mSprite.getGlobalBounds().height / 2);
	mSprite.setPosition(pos - mSpriteOffset);
	
}

Player::~Player(){
}

Entity* Player::createPlayer(sf::Vector2f pos){
	return new Player(pos);
}

void Player::render(sf::RenderWindow &window){
	window.draw(mSprite);
}

 void Player::update(){
	
	Player::playerInput();
	Player::lerp();
	Player::updateCollision();
	Player::updateState();
	Player::animate();

	mSprite.move(mVelocity);

	Toolbox::copyPlayerInfo(mSprite);
}

void Player::addVector(sf::Vector2f &vector){
	mVelocityGoal += vector;
}

void Player::entityCollision(Entity* entity, char direction){
	
}

void Player::terrainCollision(Terrain* terrain, char direction){
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
			mSprite.move(sf::Vector2f(0, delta - this->getHeight()- 1));
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

// Privates

void Player::playerInput(){

	// Jump
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		if (mState != JUMPING && mState != FALLING){
			mVelocity.y = mJumpSpeed;
		}
	}

	// Left and right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			mVelocityGoal.x = -mMaxSpeed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			mVelocityGoal.x = mMaxSpeed;
		}
	}
 else
	mVelocityGoal.x = 0;

}

void Player::lerp(){

	bool lerpedY(false);
	bool lerpedX(false);
	
	float delta = 0.016 *mSpeed ;
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
	
	
void Player::updateState(){

	if (mVelocity.x != 0 && mState != JUMPING && mState != RUNNING){
		mState = RUNNING;
		Player::updateANI();
	}

	if (mVelocity.x == 0 && mState != JUMPING && mState != IDLE){
		mState = IDLE;
		Player::updateANI();
	}

	if (mVelocity.y > 0 && mState != FALLING){
		mState = FALLING;
		Player::updateANI();
	}
	if (mVelocity.y < 0 && mState != JUMPING){
		mState = JUMPING;
		Player::updateANI();
	}
}

void Player::updateCollision(){
	if (mCollisionT){
		if (!CollisionFuncs::currentCollisionT(mSprite,mCurrentCollisionT->getSprite())){
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
	}
	if (mCollisionR){
		if (!CollisionFuncs::currentCollisionR(mSprite, mCurrentCollisionR->getSprite())){
			mCollisionR = false;
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

void Player::updateANI(){
	switch (mState){

	case JUMPING:
		mCurrentAnimation = Animations::getPlayerJumpingANI();
		break;

	case IDLE:
		mCurrentAnimation = Animations::getPlayerIdleANI();
		break;

	case RUNNING:
		mCurrentAnimation = Animations::getPlayerRunningANI();
		break;

	case FALLING:
		break;

	default:
		break;
	}
	mTimer = 0;
}

void Player::animate(){

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
