#include "Spikes.h"


static float ANIFramesPerFrame(0.4);

Spikes::Spikes(sf::Vector2f pos, char type):
mCurrentAnimation(Animations::getSpikesANI()),
mIsOnScreen(true),
mTileType(type),
mAnimationIndex(std::rand() % 16){
	mSprite.setTexture(*mCurrentAnimation->at(mAnimationIndex));
	//mCollisionBody.setTexture(*mCurrentAnimation->at(mAnimationIndex));
	
	mCollisionBody.setPosition(pos);
	mCollisionBody.setTextureRect(sf::IntRect(0, 0, mSprite.getTextureRect().width - 20, mSprite.getTextureRect().height - 10));
	Spikes::setRotation(type);
	mSpriteOffset = pos - mCollisionBody.getPosition();
	Spikes::updateTexturepos();
}


Spikes::~Spikes()
{
}

Terrain* Spikes::createSpikes(sf::Vector2f pos, char type){
	return new Spikes(pos, type);
}

void Spikes::render(sf::RenderWindow &window){
	window.draw(mSprite);
	//window.draw(mCollisionBody);
}

void Spikes::update(){
	ANIFramesPerFrame = 12.625 * Toolbox::getFrameTime();
	Spikes::animate();
}

void Spikes::setPos(sf::Vector2f newPos){
	mSprite.setPosition(newPos);
}

void Spikes::setRotation(char type){
	switch (type){
	case 't':
		mCollisionBody.move(-mCollisionBody.getGlobalBounds().width / 2, 50 - mCollisionBody.getGlobalBounds().height);
		break;
	case 'l':
		mCollisionBody.setOrigin(mCollisionBody.getGlobalBounds().width,0);
		mCollisionBody.rotate(270);
		mSprite.setOrigin(mSprite.getGlobalBounds().width, 0);
		mSprite.rotate(270);
		mCollisionBody.move(50 - mCollisionBody.getGlobalBounds().width, -mCollisionBody.getGlobalBounds().height / 2);
		break;
	case 'b':
		mCollisionBody.setOrigin(mCollisionBody.getGlobalBounds().width, mCollisionBody.getGlobalBounds().height);
		mCollisionBody.rotate(180);
		mSprite.setOrigin(mSprite.getGlobalBounds().width, mSprite.getGlobalBounds().height);
		mSprite.rotate(180);
		mCollisionBody.move(-mCollisionBody.getGlobalBounds().width / 2, -50);
		
		break;
	case 'r':
		mCollisionBody.setOrigin(0, mCollisionBody.getGlobalBounds().height);
		mCollisionBody.rotate(90);
		mSprite.setOrigin(0, mSprite.getGlobalBounds().height);
		mSprite.rotate(90);
		mCollisionBody.move(-50, -mCollisionBody.getGlobalBounds().height / 2);
		break;
	default:
		break;
	}
	mCollisionBody.setTextureRect(sf::IntRect(0, 0, mCollisionBody.getLocalBounds().width, mCollisionBody.getLocalBounds().height));
}

void Spikes::updateTexturepos() {
	sf::Vector2f temp(mCollisionBody.getPosition());
	switch (mTileType){
	case 't':
		temp.x += (mCollisionBody.getLocalBounds().width / 2);
		temp.y += (mCollisionBody.getLocalBounds().height);
		temp.x -= (mSprite.getLocalBounds().width / 2);
		temp.y -= (mSprite.getLocalBounds().height);
		break;
	case 'b':
		temp.x += (mCollisionBody.getLocalBounds().width / 2);
		temp.x -= (mSprite.getLocalBounds().width / 2);
		break;
	case 'l':
		temp.y += (mCollisionBody.getLocalBounds().width /2);
		temp.x += (mCollisionBody.getLocalBounds().height);
		temp.y -= (mSprite.getLocalBounds().width / 2);
		temp.x -= (mSprite.getLocalBounds().height);
		break;
	case 'r':
		temp.y += (mCollisionBody.getLocalBounds().width / 2);
		temp.y -= (mSprite.getLocalBounds().width / 2);
		break;
	default:
		break;
	}
	mSprite.setPosition(temp);
	//std::cout << "X: " << mCollisionBody.getPosition().x << std::endl;
	//std::cout << "Y: " << mCollisionBody.getPosition().y << std::endl;
}

void Spikes::animate(){
	mTimer += ANIFramesPerFrame;

	if (mTimer >= 1){
		mAnimationIndex += 1;
		mTimer = 0;
		if (mAnimationIndex >= mCurrentAnimation->size()){
				mAnimationIndex = 0;
		}

		if (mCurrentAnimation->size() > 0)
			mSprite.setTexture(*mCurrentAnimation->at(mAnimationIndex));
	}
}