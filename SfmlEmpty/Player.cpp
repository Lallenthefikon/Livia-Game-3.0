#include "Player.h"
#include <iostream>

static float ANIFramesPerFrame(0.5);

Player::Player(sf::Vector2f pos) :
	mVelocity(0, 0),
	mIsOnScreen(true),
	mState(IDLE),
	mTurned(TURNEDLEFT),
	mIsAlive(true),

	// Animation stuff
	mAnimationIndex(0),
	mCurrentAnimation(Animations::getPlayerIdleANI()),
	mTimerANI(1),
	mPlayerTransparency(255),
	mTimesBlinked(0),
	mBlinkOut(true),

	// Jump
	mJumpSpeedInitial(-1250),
	mJumpSpeedDouble(-1250),
	mJumpSpeedMax(-2000),
	mJumpStarted(false),
	mDoubleJumped(false),
	mJumpReleased(true),
	mLastBlockToched(Terrain::BLOCK0),


	// Stats
	mMaxSpeed(800),
	mIcyMaxSpeed(1500), //Design, 1500
mAcceleration(70, 70),
mIcyAcceleration(12,70), //Design, 12, 70
mLife(3),
mWallSlideSpeed(4),
mTimeInvulnerable(sf::seconds(3)),
mAirbornAcc(70),
mIcyAirborn(19), //Design, 19

// Sounds
mSoundFX(SoundFactory::getLiviaSound()),

// Text
mText("Game Over!", Toolbox::getFont(Toolbox::FONTKEY::GAMEOVER)),
mFallenOutsideBounds(false),
mAtRightBorder(false),
mAtLeftBorder(false),

mTextHandler(Texthandler::getInstance()){
	
	mText.setColor(sf::Color::Green);
	mText.setPosition(400, 400);
	
	mSprite.setTexture(*mCurrentAnimation->at(0));


	mCollisionBody.setTextureRect(sf::IntRect(0, 0, mSprite.getTextureRect().width - 20, mSprite.getTextureRect().height- 10));
	//mCollisionBody.setTexture(*mCurrentAnimation->back());
	mSpriteOffset = sf::Vector2f(mCollisionBody.getGlobalBounds().width / 2, mCollisionBody.getGlobalBounds().height / 2);
	mCollisionBody.setPosition(pos - mSpriteOffset);
	Player::updateTexturepos();

	Toolbox::copyPlayerSprite(mCollisionBody);
	Toolbox::copyPlayerVelocity(mVelocity);
}

Player::~Player(){
}

Entity* Player::createPlayer(sf::Vector2f pos){
	return new Player(pos);
}

void Player::render(sf::RenderWindow &window){
	Player::updateTexturepos();
	window.draw(mSprite);

	//window.draw(mCollisionBody);



	// FLYTTA TILL LAYER HANDLER, SKA INTE RITAS H�R F�R I HELVETE!!!
	if (!mIsAlive) {
		mTextHandler.renderGameOver(window);
	}
	if (mWin) {
		mTextHandler.renderWin(window);
	}

	if (mState == DEATH) {
		mTextHandler.renderGameOver(window);
	}
 	if (mWin) {
		mTextHandler.renderWin(window);
	}
}

 void Player::update(){


	//std::cout << "Player Velocity X: " << mVelocity.x << std::endl << "Player Velocity Y: " << mVelocity.y << std::endl;
	//std::cout << "mState: " << mState << std::endl;
	ANIFramesPerFrame = mCurrentAnimationRate * Toolbox::getFrameTime();
	
	Player::playerInput();
	
	Player::lerp();

	Player::updateCollision();
	Player::updateCollisionForce();
	
	Player::updateState();
	
	Player::addForces();

	Player::animate();

	mCollisionBody.move(mVelocity);
	

	
	
	Toolbox::copyPlayerSprite(mCollisionBody);
	Toolbox::copyPlayerVelocity(mVelocity);
	Toolbox::copyPlayerPosition(mCollisionBody.getPosition());
	Toolbox::copyPlayerIsAlive(mIsAlive);
	Toolbox::copyPlayerHealth(mLife);
	checkPlayerWithinBounds();
	invulnerableBlink();
}

void Player::addVector(sf::Vector2f &vector){
	mVelocityGoal += vector;
}

void Player::entityCollision(Entity* entity, char direction){
	float delta;
	switch (entity->getType()){
	case Entity::WORM:
	case Entity::GERM:
	case Entity::OCTO_PI:
		switch (direction){
		case 'b':
			if (mLife > 0 && entity->getLife() > 0){
				if (!mInvulnerable){
					delta = entity->getPos().y - mCollisionBody.getPosition().y;
					mCollisionBody.move(sf::Vector2f(0, delta - this->getHeight() - 1));
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
						mJumpStarted = true;
						mVelocity.y = mJumpSpeedInitial * Toolbox::getFrameTime();
					}
					else {
						mVelocity.y = mJumpSpeedInitial * Toolbox::getFrameTime();
					}
				}
				entity->getHit();
			}
			break;
		default:
			break;
		}
		break;
	case Entity::ACIDMONSTER:
		mLife = 0;
		break;
	case Entity::EXTRALIFE:
		mLife++;
		entity->getHit();
		break;
	default:
		break;
	}
}

void Player::terrainCollision(Terrain* terrain, char direction){
	
	switch (terrain->getType())	{
	case Terrain::SPIKES:
		mWin = false;
		/*switch (direction){
		case 't':
			mVelocity.y = -mJumpSpeedInitial;
			break;
		case 'b':
			mVelocity.y = mJumpSpeedInitial;
			break;
		case 'l':
			mVelocity.x = -mJumpSpeedInitial;
			break;
		case 'r':
			mVelocity.x = mJumpSpeedInitial;
			break;
		default:
			break;
		}*/
		this->getHit();
		break;

	case Terrain::BLOCKGOAL:
		mWin = true;
		break;

	case Terrain::EVENT:
		mSoundFX.stopAllSound();
		terrain->trigger();
		break;
		

	default:
		break;
	}
}

void Player::blockterrainCollision(BlockTerrain * blockterrain, char direction) {
	float delta;
	switch (blockterrain->getType()) {
	case BlockTerrain::COLLISIONBLOCK:
		mWin = false;
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
	}
}

void Player::getHit() {
	if (!mInvulnerable) {
		if (mLife > 0) {
			mLife--;
			mInvulnerable = true;
			mState = DAMAGED;
			Player::updateANI();
			if (mTurned == TURNEDLEFT) {
				mVelocity.x += 20;
			}
			else {
				mVelocity.x -= 20;
			}
			mInvulnerableTimer.restart().asMilliseconds();
			if (!mLife <= 0) {
				Player::playSound(Player::DAMAGED);
			}
		}
	}
}

// Privates

void Player::playerInput() {
	if (mState != DEATH && mState != FALLDEATH){
		jump();
		move();
	//	playSoundManually();
	}
	else{
		mVelocityGoal.x = 0;
	}
}

void Player::jump() {

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {

		// Apply min
         if (!mJumpStarted && mState != JUMPING && mState != FALLING && mJumpReleased) {
			mJumpStarted = true;
			mDoubleJumped = false;
			mJumpReleased = false;
			mVelocity.y = mJumpSpeedInitial * Toolbox::getFrameTime();
			if (mState == WALLSTUCK) {
				if (mTurned == TURNEDRIGHT)
					mVelocity.x = -mMaxSpeed * Toolbox::getFrameTime();
				if (mTurned == TURNEDLEFT)
					mVelocity.x = mMaxSpeed * Toolbox::getFrameTime();
			}
		}
		
		// Apply gradually to max
		if (mJumpStarted && (mState == JUMPING || mState == FALLING)) {
			if (mVelocity.y >= mJumpSpeedMax * Toolbox::getFrameTime()) {
				float jumpVelocityIncrease = 37.5f * Toolbox::getFrameTime();
				mVelocity.y -= jumpVelocityIncrease;
			} else {
				mJumpStarted = false;
			}
		}
		// Apply Double 
		if (!mJumpStarted && (mState == JUMPING || mState == FALLING) && !mDoubleJumped && mJumpReleased) {
			mDoubleJumped = true;
			mJumpReleased = false;
			mVelocity.y = mJumpSpeedDouble * Toolbox::getFrameTime();
			Player::stopSound(JUMPING);
			Player::playSound(JUMPING);
		}
	} 
	else {
		mJumpReleased = true;
		mJumpStarted = false;
	}
}

void Player::move() {
	bool changed(false);

		// Left and right
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			if (mLastBlockToched == Terrain::BLOCK0ICY)
				mVelocityGoal.x = -mIcyMaxSpeed * Toolbox::getFrameTime();
			else
				mVelocityGoal.x = -mMaxSpeed * Toolbox::getFrameTime();

			changed = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			if (mLastBlockToched == Terrain::BLOCK0ICY)
				mVelocityGoal.x = mIcyMaxSpeed * Toolbox::getFrameTime();
			else
				mVelocityGoal.x = mMaxSpeed * Toolbox::getFrameTime();

			changed = true;
		}
		if (!changed) {
		mVelocityGoal.x = 0;
}
}

void Player::playSoundManually() {
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	//	playSound(JUMPING);
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	//	playSound(DAMAGED);
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
	//	playSound(DEATH);
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
	//	playSound(RUNNING);
}

void Player::lerp(){

	bool lerpedY(false);
	bool lerpedX(false);
	
	sf::Vector2f delta;

	// Different delta depending on what block the player is standing on
	if (mCurrentCollisionB != 0 && mLastBlockToched == Terrain::BLOCK0ICY) {
		delta = sf::Vector2f(Toolbox::getFrameTime() * mIcyAcceleration.x, Toolbox::getFrameTime() * mIcyAcceleration.y);
	} else {
		delta = sf::Vector2f(mAcceleration.x * Toolbox::getFrameTime(), mAcceleration.y * Toolbox::getFrameTime());
	}

	float airBorneDelta;

	if (mCurrentCollisionB != 0 && mLastBlockToched == Terrain::BLOCK0ICY) {
		airBorneDelta = Toolbox::getFrameTime() * mIcyAirborn;
	}
	else {
		airBorneDelta = Toolbox::getFrameTime() * mAirbornAcc;
	}

	float differenceX = mVelocityGoal.x - mVelocity.x;
	float differenceY = mVelocityGoal.y - mVelocity.y;

	if (mVelocityGoal.y > 2500 * Toolbox::getFrameTime()) {
		mVelocityGoal.y = 2500 * Toolbox::getFrameTime();
	}

	// Interpolates the velocity up from stationary
	if (mState == JUMPING || mState == FALLING) {
		if (differenceX > airBorneDelta) {
			mVelocity.x += airBorneDelta;
			lerpedX = true;
		}
	} else {
		if (differenceX > delta.x) {
			mVelocity.x += delta.x;
			lerpedX = true;
		}
	}
	// Interpolates the velocity up from stationary
	if (differenceY > delta.y) {
		mVelocity.y += delta.y;
		lerpedY = true;
	}
	// Interpolates the velocity down to stationary
	if (mState == JUMPING || mState == FALLING) {
		if (differenceX < -airBorneDelta) {
			mVelocity.x += -airBorneDelta;
			lerpedX = true;
		}
	} else {
		if (differenceX < -delta.x) {
			mVelocity.x += -delta.x;
			lerpedX = true;
		}
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

	
void Player::updateState() {
	bool changed(false);

	// Player dies from damage
	if (mLife <= 0 && mState != DEATH && mState != FALLDEATH && mState != DROWN) {
		if (mState == FALLING || mState == JUMPING) {
			mState = DEATH;
			changed = true;
			Player::stopSound(RUNNING);
			Player::playSound(DEATH);
		}
		else {
			mState = DEATH;
			changed = true;
			Player::stopSound(RUNNING);
			Player::playSound(DEATH);
		}
	}
	// Player falls to death
	else if (mFallenOutsideBounds && mState != FALLDEATH && mState != DEATH){
		mLife = 0;
		if (Toolbox::getCurrentLevelName() == "Stomach") {
			mState = DROWN;
		} else
			mState = FALLDEATH;
		changed = true;
		Player::stopSound(RUNNING);
		Player::playSound(mState);
	}

	if (mState == WALLSTUCK) {
		if (mCollisionR) {
			mLastBlockToched = mCurrentCollisionR->getType(mCollisionBody.getPosition(), mCollisionBody.getGlobalBounds().width, 'l');
			if (mCurrentCollisionR->getType(mCollisionBody.getPosition(), mCollisionBody.getGlobalBounds().height, 'l') != Terrain::BLOCK0WALLJUMP || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				mState = FALLING;
				changed = true;
			}
		}
		if (mCollisionL) {
			mLastBlockToched = mCurrentCollisionL->getType(mCollisionBody.getPosition(), mCollisionBody.getGlobalBounds().width, 'r');
			if (mCurrentCollisionL->getType(mCollisionBody.getPosition(), mCollisionBody.getGlobalBounds().height, 'r') != Terrain::BLOCK0WALLJUMP || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				mState = FALLING;
				changed = true;
			}
		}
		if (!(mCollisionL || mCollisionR)) {
			mState = FALLING;
			changed = true;
		}
	}
	else
		Player::stopSound(WALLSTUCK);

	if (mCollisionB) {
		mLastBlockToched = mCurrentCollisionB->getType(mSprite.getPosition(), mSprite.getGlobalBounds().width, 'b');
	}


	if (mState != DEATH && mState != FALLDEATH) {
		if (mState == FALLING && mVelocity.y == 0) {
			mState = LANDED;
			Player::playSound(LANDED);
		}

		// Player runs in a direction
		if (mVelocity.x != 0 && mVelocity.y == 0 && mState != JUMPING && mState != RUNNING && mState != DAMAGED) {
			mState = RUNNING;
			changed = true;
			if (!mVelocity.y > 0) {
				Player::playSound(RUNNING);
			}
		}


		if (mVelocity.x == 0 && mVelocity.y == 0 && mState != JUMPING && mState != IDLE && mState != WALLSTUCK && mState != DAMAGED) {
			mState = IDLE;
			changed = true;
			Player::stopSound(RUNNING);
		}

		if (mVelocity.y > 2 && mState != FALLING && mState != WALLSTUCK) {
			mState = FALLING;
			changed = true;
			Player::stopSound(RUNNING);
		}

		// Player is jumping
		if (mVelocity.y < 0 && mState != JUMPING) {
			mState = JUMPING;
			changed = true;
			Player::stopSound(RUNNING);
			Player::stopSound(JUMPING);
			Player::playSound(JUMPING);
		}

		// Player collides with sticky block to the right
		if (mCollisionR) {
			if (mCurrentCollisionR->getType(mCollisionBody.getPosition(), mCollisionBody.getGlobalBounds().height, 'r') == Terrain::BLOCK0WALLJUMP  && mState != WALLSTUCK) {
				mState = WALLSTUCK;
				mJumpStarted = false;
				changed = true;
				Player::playSound(WALLSTUCK);
			}
		}

		// Player collides with sticky block to the left
		if (mCollisionL) {
			if (mCurrentCollisionL->getType(mCollisionBody.getPosition(), mCollisionBody.getGlobalBounds().height, 'l') == Terrain::BLOCK0WALLJUMP  && mState != WALLSTUCK) {
				mState = WALLSTUCK;
				mJumpStarted = false;
				changed = true;
				Player::playSound(WALLSTUCK);
			}
		}

		// Player invulnerability timer
		if (mInvulnerableTimer.getElapsedTime().asMilliseconds() > 1000) {
			mInvulnerable = false;
		}

		// Player direction right
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && mTurned != TURNEDRIGHT && mState != DAMAGED) {
			mTurned = TURNEDRIGHT;
			changed = true;
		}
		// Player direction left
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && mTurned != TURNEDLEFT && mState != DAMAGED) {
			mTurned = TURNEDLEFT;
			changed = true;
		}
	}
	if (mInvulnerableTimer.getElapsedTime().asMilliseconds() > 1000) {
		mInvulnerable = false;
	}

	// Updates animation if player's state has changed
	if (changed)
		Player::updateANI();
}

void Player::updateCollisionForce(){
	if (mCollisionT && mVelocity.y < 0)
		mVelocity.y = 0;
	if (mCollisionB && mVelocity.y > 0)
		mVelocity.y = 0;
	if (mCollisionL && mVelocity.x < 0)
		mVelocity.x = 0;
	if (mCollisionR && mVelocity.x > 0)
		mVelocity.x = 0;
}

void Player::updateCollision() {
	sf::Sprite tempSprite(mCollisionBody);

	tempSprite.move(mVelocity);

	if (mCollisionT) {
		if (!CollisionFuncs::currentCollisionT(tempSprite, mCurrentCollisionT->getSprite())) {
			mCollisionT = false;
		}
	}
	if (mCollisionB) {
		if (!CollisionFuncs::currentCollisionB(tempSprite, mCurrentCollisionB->getSprite())) {
			mCollisionB = false;
		}
	}
	if (mCollisionL) {
		if (!CollisionFuncs::currentCollisionL(tempSprite, mCurrentCollisionL->getSprite())) {
			mCollisionL = false;
		}
	}
	if (mCollisionR) {
		if (!CollisionFuncs::currentCollisionR(tempSprite, mCurrentCollisionR->getSprite())) {
			mCollisionR = false;
		}
	}
}


void Player::updateANI(){
	float spriteWidth;
	switch (mState){
	case DAMAGED:
		mCurrentAnimationRate = 31.75;
		mSprite.setTextureRect(sf::IntRect(0, 0, 100, 140));
		mCurrentAnimation = Animations::getPlayerHurtANI();
		break;

	case JUMPING:
		mCurrentAnimationRate = 31.25;
		mSprite.setTextureRect(sf::IntRect(0, 0, 100, 160));
		mCurrentAnimation = Animations::getPlayerJumpingANI();
		break;

	case IDLE:
		mCurrentAnimationRate = 15.625;
		mSprite.setTextureRect(sf::IntRect(0, 0, 70, 140));
		mCurrentAnimation = Animations::getPlayerIdleANI();
		break;

	case RUNNING:
		mCurrentAnimationRate = 31.25;
		mCurrentAnimation = Animations::getPlayerRunningANI();
		mSprite.setTextureRect(sf::IntRect(0, 0, 100, 140));
		break;

	case FALLING:
		mCurrentAnimationRate = 31.25;
		mCurrentAnimation = Animations::getPlayerFallingANI();
		mSprite.setTextureRect(sf::IntRect(0, 0, 100, 160));
		break;

	case WALLSTUCK:
		mCurrentAnimationRate = 31.25;
		mCurrentAnimation = Animations::getPlayerSlideANI();
		mSprite.setTextureRect(sf::IntRect(0, 0, 67, 140));
		break;

	case DEATH:
		mCurrentAnimationRate = 15.625;
		mCurrentAnimation = Animations::getPlayerDyingANI();
		mSprite.setTextureRect(sf::IntRect(0, 0, 188, 140));
		break;
		
	case FALLDEATH:
		mCurrentAnimationRate = 7.625;
		mCurrentAnimation = Animations::getPlayerFallDyingANI();
		mSprite.setTextureRect(sf::IntRect(0, 0, 100, 160));
		break;

	default:
		break;
	}
	if (mTurned == TURNEDLEFT)
		mSprite.setTextureRect(sf::IntRect(0, 0, mSprite.getLocalBounds().width, mSprite.getLocalBounds().height));

	if (mTurned == TURNEDRIGHT)
		mSprite.setTextureRect(sf::IntRect(mSprite.getLocalBounds().width, 0, -mSprite.getLocalBounds().width, mSprite.getLocalBounds().height));

	mAnimationIndex = 0;
	mTimerANI = 1;
}

void Player::addForces(){
	if (mState == WALLSTUCK){
		mVelocity.y = mWallSlideSpeed;
	}
}


void Player::animate(){

	mTimerANI += ANIFramesPerFrame;
	
	if (mTimerANI >= 1){
		mAnimationIndex += 1;
		mTimerANI = 0;
		if (mAnimationIndex >= mCurrentAnimation->size()){
			if (mState == DEATH || mState == FALLDEATH){
				mIsAlive = false;
				mAnimationIndex -= 1;
			}
			else if (mState == DAMAGED) {
				mState = IDLE;
				Player::updateState();
				Player::updateANI();
				mAnimationIndex = 0;
			}
			else
			mAnimationIndex = 0;
		}
		
		if (mCurrentAnimation->size() > 0)
			mSprite.setTexture(*mCurrentAnimation->at(mAnimationIndex));
	}
}

void Player::updateTexturepos(){
	sf::Vector2f temp(mCollisionBody.getPosition() + mSpriteOffset);
	temp.x -= (mSprite.getLocalBounds().width / 2 );
	temp.y -= (mSprite.getLocalBounds().height /2);
	mSprite.setPosition(temp);
	//std::cout << "X: " << mCollisionBody.getPosition().x << std::endl;
	//std::cout << "Y: " << mCollisionBody.getPosition().y << std::endl;
}

void Player::playSound(PLAYERSTATE state) {
	int randomValue = std::rand() % 3;
	switch (state) {
	case Player::JUMPING:
		// Randomize jump sound
		if (randomValue == 0) {
			mSoundFX.playSound(SoundFX::SOUNDTYPE::JUMPING1);
		} else if (randomValue == 1) {
			mSoundFX.playSound(SoundFX::SOUNDTYPE::JUMPING2);
		} else if (randomValue == 2) {
			mSoundFX.playSound(SoundFX::SOUNDTYPE::JUMPING3);
		}
		break;
	case Player::IDLE:
		mSoundFX.playSound(SoundFX::SOUNDTYPE::IDLE);
		break;
	case Player::RUNNING:
		mSoundFX.playSound(SoundFX::SOUNDTYPE::RUNNING);
		break;
	case Player::FALLING:
		break;
	case Player::DAMAGED:
		mSoundFX.playSound(SoundFX::SOUNDTYPE::DAMAGED);
		break;
	case Player::DEATH:
		mSoundFX.playSound(SoundFX::SOUNDTYPE::DEATH);
		break;
	case Player::FALLDEATH:
		mSoundFX.playSound(SoundFX::SOUNDTYPE::FALLDEATH);
		break;
	case Player::DROWN:
		mSoundFX.playSound(SoundFX::SOUNDTYPE::DROWN);
		break;
	case Player::WALLSTUCK:
		mSoundFX.playSound(SoundFX::SOUNDTYPE::WALLSLIDE);
		break;
	case Player::LANDED:
		mSoundFX.playSound(SoundFX::SOUNDTYPE::LANDING);
		break;
	default:
		break;
	}
}

void Player::stopSound(PLAYERSTATE state) {
	switch (state) {
	case Player::JUMPING:
		mSoundFX.stopSound(SoundFX::SOUNDTYPE::JUMPING1);
		mSoundFX.stopSound(SoundFX::SOUNDTYPE::JUMPING2);
		mSoundFX.stopSound(SoundFX::SOUNDTYPE::JUMPING3);
		break;
	case Player::IDLE:
		mSoundFX.stopSound(SoundFX::SOUNDTYPE::IDLE);
		break;
	case Player::RUNNING:
		mSoundFX.stopSound(SoundFX::SOUNDTYPE::RUNNING);
		break;
	case Player::FALLING:
		break;
	case Player::DAMAGED:
		mSoundFX.stopSound(SoundFX::SOUNDTYPE::DAMAGED);
		break;
	case Player::DEATH:
		mSoundFX.stopSound(SoundFX::SOUNDTYPE::DEATH);
		break;
	case Player::FALLDEATH:
		mSoundFX.stopSound(SoundFX::SOUNDTYPE::FALLDEATH);
		break;
	case Player::WALLSTUCK:
		mSoundFX.stopSound(SoundFX::SOUNDTYPE::WALLSLIDE);
		break;
	case Player::LANDED:
		mSoundFX.stopSound(SoundFX::SOUNDTYPE::LANDING);
		break;
	default:
		break;
	}
}

void Player::setPos(sf::Vector2f newPos){
	mCollisionBody.setPosition(newPos);
}

void Player::invulnerableBlink(){
	
	if (mInvulnerable && (mLife > 0)){
		
		float blinkOutSpeed = 12.f;


		if (mPlayerTransparency >= 255){
			mBlinkOut = true;
		}
		else if (mPlayerTransparency <= 0){
			mBlinkOut = false;
		}
		
		if (mBlinkOut){
			mPlayerTransparency -= blinkOutSpeed;
		}
		else if (!mBlinkOut){
			mPlayerTransparency = 255;
		}
		mSprite.setColor(sf::Color(255, 255, 255, mPlayerTransparency));
	}
	else{
		if (mPlayerTransparency < 255){
			mPlayerTransparency = 255;
			mSprite.setColor(sf::Color(255, 255, 255, mPlayerTransparency));
		}
	}
}

void Player::checkPlayerWithinBounds(){
	if (mSprite.getPosition().y >= Toolbox::getLevelBounds().height){
		mFallenOutsideBounds = true;
	}

	/*if (mPlayerCoordPos.y >= Toolbox::getLevelBounds().height){
		mLife = 0;
	}*/
}

void Player::stopAllSound() {
	mSoundFX.stopAllSound();
}