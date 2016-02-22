#include "Spikes.h"


static float ANIFramesPerFrame(0.4);

Spikes::Spikes(sf::Vector2f pos, char type):
mCurrentAnimation(Animations::getSpikesANI()),
mIsOnScreen(true),
mTileType(type),
mAnimationIndex(std::rand() % 16){
	mSprite.setTexture(*mCurrentAnimation->at(mAnimationIndex));

	
	mSprite.setPosition(pos);
	Spikes::setRotation(type);
	mSpriteOffset = pos - mSprite.getPosition();
}


Spikes::~Spikes()
{
}

Terrain* Spikes::createSpikes(sf::Vector2f pos, char type){
	return new Spikes(pos, type);
}

void Spikes::render(sf::RenderWindow &window){
	window.draw(mSprite);
}

void Spikes::update(){
	Spikes::animate();
}

void Spikes::setPos(sf::Vector2f newPos){
	mSprite.setPosition(newPos);
}

void Spikes::setRotation(char type){
	switch (type){
	case 't':
		mSprite.move(-mSprite.getGlobalBounds().width / 2, 0);
		break;
	case 'l':
		mSprite.setOrigin(mSprite.getGlobalBounds().width,0);
		mSprite.rotate(270);
		mSprite.move(0, -mSprite.getGlobalBounds().height / 2);


		break;
	case 'b':
		mSprite.setOrigin(mSprite.getGlobalBounds().width, mSprite.getGlobalBounds().height);
		mSprite.rotate(180);
		mSprite.move(-mSprite.getGlobalBounds().width / 2, -mSprite.getGlobalBounds().width / 2);
		
		break;
	case 'r':
		mSprite.setOrigin(0, mSprite.getGlobalBounds().height);
		mSprite.rotate(90);	
		mSprite.move(-mSprite.getGlobalBounds().height / 2, -mSprite.getGlobalBounds().height / 2);
		break;
	default:
		break;
	}
	mSprite.setTextureRect(sf::IntRect(0, 0, mSprite.getLocalBounds().width, mSprite.getLocalBounds().height));
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