#include "Spikes.h"


Spikes::Spikes(sf::Vector2f pos, char type):
mTileType(type){
	mTexture.loadFromImage(Toolbox::getTexture(Toolbox::BLOCK0TEXTURE), sf::IntRect(400,300,100,50));
	mSprite.setTexture(mTexture);
	
	
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