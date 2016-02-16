#include "Player.h"
#include <iostream>

static const float ANIFramesPerFrame(0.5);

Player::Player(sf::Vector2f pos) :
mVelocity(0, 0),
mIsOnScreen(true),
mState(IDLE),
mIsAlive(true),

// Animatin stuff
mAnimationIndex(0),
mCurrentAnimation(Animations::getPlayerRunningANI()),
mTimerANI(1),

// Jump
mJumpSpeedInitial(-20),
mJumpSpeedDouble(-20),
mJumpSpeedMax(-30),
mJumpStarted(false),
mDoubleJumped(false),

// Stats
mMaxSpeed(15),
mAcceleration(70),
mLife(3),
mWallSlideSpeed(4),


// Sounds
mSoundFX(SoundFactory::getLiviaSound()){

	mSprite.setTexture(*mCurrentAnimation->at(0));
	mSpriteOffset = sf::Vector2f(mSprite.getGlobalBounds().width / 2, mSprite.getGlobalBounds().height / 2);
	mSprite.setPosition(pos - mSpriteOffset);
	Toolbox::copyPlayerSprite(mSprite);
	Toolbox::copyPlayerVelocity(mVelocity);
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
	 Toolbox::copyPlayerSprite(mSprite);
	// std::cout << "Player Velocity X: " << mVelocity.x << std::endl << "Player Velocity Y: " << mVelocity.y << std::endl;
	Player::playerInput();
	Player::lerp();
	Player::updateCollision();
	Player::updateState();
	Player::animate();

	mSprite.move(mVelocity);

	Toolbox::copyPlayerSprite(mSprite);
	Toolbox::copyPlayerVelocity(mVelocity);
}

void Player::addVector(sf::Vector2f &vector){
	mVelocityGoal += vector;
}

void Player::entityCollision(Entity* entity, char direction){
	float delta;
	switch (entity->getType()){
	case Entity::WORM:
		switch (direction){
		case 'b':
			if (!mInvulnerable){
				delta = entity->getPos().y - mSprite.getPosition().y;
				mSprite.move(sf::Vector2f(0, delta - this->getHeight() - 1));
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
					mJumpStarted = true;
					mVelocity.y = mJumpSpeedInitial;
				}
				else{
					mVelocity.y = mJumpSpeedInitial;
				}

				entity->getHit();
			}
			break;
		default:
			break;
		}

	default:
		break;
	}
}

void Player::terrainCollision(Terrain* terrain, char direction){
	float delta;
	switch (terrain->getType())	{
	case Terrain::BLOCK0:
	case Terrain::BLOCK0WALLJUMP:
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

void Player::getHit(){
	if (!mInvulnerable){
		if (mLife > 0){
			mLife--;
			mInvulnerable = true;
			mInvulnerableTime.restart().asMilliseconds();
			Player::playSound(Player::DAMAGED);
		}
		else
			mIsAlive = false;
	}
}

// Privates

void Player::playerInput() {

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){

		// Apply min
		if (!mJumpStarted && mState != JUMPING && mState != FALLING){
			mJumpStarted = true;
			mDoubleJumped = false;
			mVelocity.y = mJumpSpeedInitial;
			if (mState == WALLSTUCKRIGHT)
				mVelocity.x = -mMaxSpeed;
			if (mState == WALLSTUCKLEFT)
				mVelocity.x = mMaxSpeed;
		}
		
		// Apply gradually to max
		if (mJumpStarted && (mState == JUMPING || mState == FALLING)){
 			if (mVelocity.y >= mJumpSpeedMax){
				float jumpVelocityIncrease = .6f;
				mVelocity.y -= jumpVelocityIncrease;
			}
			else{
				mJumpStarted = false;
			}
		}
		// Apply Double 
		if (!mJumpStarted && (mState == JUMPING || mState == FALLING) && !mDoubleJumped){
			mDoubleJumped = true;
			mVelocity.y = mJumpSpeedDouble;
		}



		//if (mJumpTimer < 0.5 && mState != JUMPING && mState != FALLING) {
		//mVelocity.y = mJumpSpeedFirst;
		//mJumpTimer = 0;
		//Player::playSound(JUMPING);
		//}
		//else if (mState != JUMPING && mState != FALLING) {

		//mVelocity.y = mJumpSpeedSecond;
		//	mJumpTimer = 0;
		//mSoundFX.playSound(SoundFX::JUMPING);
		//Player::playSound(JUMPING);
		//	}
		//std::cout << mJumpTimer << std::endl;
	}
	else{
		mJumpStarted = false;
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
	else {
		mVelocityGoal.x = 0;
	}
}

void Player::lerp(){

	bool lerpedY(false);
	bool lerpedX(false);
	
	float delta = 0.016 * mAcceleration ;
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

	if (mVelocity.x < 0 && mState != JUMPING && mState != RUNNINGLEFT){
		mState = RUNNINGLEFT;
		Player::playSound(mState);
		Player::updateANI();
	}

	if (mVelocity.x > 0 && mState != JUMPING && mState != RUNNINGRIGHT){
		mState = RUNNINGRIGHT;
		Player::playSound(mState);
		Player::updateANI();
	}

	if (mVelocity.x == 0 && mState != JUMPING && mState != IDLE && mState){
		mState = IDLE;
		Player::playSound(mState);
		Player::updateANI();
	}

	if (mVelocity.y > 0 && mState != FALLING){
		mState = FALLING;
		Player::updateANI();
	}

	if (mVelocity.y < 0 && mState != JUMPING){
		mState = JUMPING;
		Player::playSound(mState);
		Player::updateANI();
	}
	if (mCollisionR){
		if (mCurrentCollisionR->getType() == Terrain::BLOCK0WALLJUMP && sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
			mState = WALLSTUCKRIGHT;
			mVelocity.y = mWallSlideSpeed;
			mJumpStarted = false;
		}
	}
	if (mCollisionL){
		if (mCurrentCollisionL->getType() == Terrain::BLOCK0WALLJUMP && sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
			mState = WALLSTUCKLEFT;
			mVelocity.y = mWallSlideSpeed;
			mJumpStarted = false;
		}
	}
	if (mInvulnerableTime.getElapsedTime().asMilliseconds() > 1000){
		mInvulnerable = false;
	}

	//if (mJumpClockTimer.getElapsedTime().asMilliseconds() > 1000){
	//	mJumpClock = false;
	//}

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

//void Player::checkTerrainTypes(){
//	if (mCollisionR){
//		if (mCurrentCollisionR->getType() == Terrain::BLOCK0WALLJUMP && sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
//			mState = WALLSTUCKRIGHT;
//			mVelocity.y = mWallSlideSpeed;
//			mJumpStarted = false;
//		}
//	}
//	if (mCollisionL){
//		if (mCurrentCollisionL->getType() == Terrain::BLOCK0WALLJUMP && sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
//			mState = WALLSTUCKLEFT;
//			mVelocity.y = mWallSlideSpeed;
//			mJumpStarted = false;
//		}
//	}
//}

void Player::updateANI(){
	float spriteWidth;
	switch (mState){

	case JUMPING:
		mCurrentAnimation = Animations::getPlayerJumpingANI();
		break;

	case IDLE:
		mCurrentAnimation = Animations::getPlayerIdleANI();
		break;

	case RUNNINGLEFT:
		mCurrentAnimation = Animations::getPlayerRunningANI();
		//mSprite.setScale(1.f, 1.f);
		mSprite.setTextureRect(sf::IntRect(0, 0, mSprite.getLocalBounds().width, mSprite.getLocalBounds().height));

		//// flip X
		//sprite.setTextureRect(sf::IntRect(width, 0, -width, height));

		//// unflip X
		//sprite.setTextureRect(sf::IntRect(0, 0, width, height));
	//	mSprite.setPosition(sf::Vector2f(spriteWidth,mSprite.getPosition().y));
		break;

	case RUNNINGRIGHT:
		mCurrentAnimation = Animations::getPlayerRunningANI();
		mSprite.setTextureRect(sf::IntRect(mSprite.getLocalBounds().width, 0, -mSprite.getLocalBounds().width, mSprite.getLocalBounds().height));

		//mSprite.setScale(-1.f, 1.f);
		//mSprite.setPosition(sf::Vector2f(spriteWidth, mSprite.getPosition().y));
		break;

	case FALLING:
		break;

	default:
		break;
	}
	mTimerANI = 0;
}

void Player::animate(){

	mTimerANI += ANIFramesPerFrame;
	
	if (mTimerANI >= 1){
		mAnimationIndex += 1;
		mTimerANI = 0;
		if (mAnimationIndex >= mCurrentAnimation->size())
			mAnimationIndex = 0;
		if (mCurrentAnimation->size() > 0)
			mSprite.setTexture(*mCurrentAnimation->at(mAnimationIndex));
	}
}


void Player::playSound(PLAYERSTATE state) {
	//switch (state) {
	//case Player::JUMPING:
	//	mSoundFX.playSound(SoundFX::SOUNDTYPE::JUMPING);
	//	break;
	//case Player::IDLE:
	//	mSoundFX.playSound(SoundFX::SOUNDTYPE::IDLE);
	//	break;
	//case Player::RUNNINGLEFT:
	//	//mSoundFX.playSound(SoundFX::SOUNDTYPE::RUNNING);
	//	break;
	//case Player::RUNNINGRIGHT:
	//	//mSoundFX.playSound(SoundFX::SOUNDTYPE::RUNNING);
	//	break;
	//case Player::FALLING:
	//	break;
	//case Player::DAMAGED:
	//	mSoundFX.playSound(SoundFX::SOUNDTYPE::DAMAGED);
	//default:
	//	break;
	//}
}

void Player::setPos(sf::Vector2f newPos){
	mSprite.setPosition(newPos);
}