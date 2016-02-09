#include "Block0.h"

Block0::Block0(sf::Vector2f pos, char type){
	Block0::setTexture(type);
	mSprite.setTexture(mTexture);
	mSpriteOffset = sf::Vector2f(mSprite.getLocalBounds().width / 2, mSprite.getLocalBounds().height / 2);
	mSprite.setPosition(pos - mSpriteOffset);
}

Block0::~Block0(){
}

Terrain* Block0::createBlock0(sf::Vector2f pos, char type){
	return new Block0(pos, type);
}

void Block0::render(sf::RenderWindow &window){
	window.draw(mSprite);
}

void Block0::update(){

}

void Block0::setTexture(char type){
	float tileWidth(120);
	float tileHeight(120);
	int xIndex(0);
	int yIndex(0);

	switch (type){

	case 'a':
		break;

	case 'b':
		xIndex = 1;
		break;

	case 'c':
		xIndex = 2;
		break;

	case 'd':
		xIndex = 3;
		break;

	case 'e':
		yIndex = 1;
		break;

	case 'f':
		yIndex = 1;
		xIndex = 1;
		break;

	case 'g':
		yIndex = 1;
		xIndex = 2;
		break;

	case 'h':
		yIndex = 1;
		xIndex = 3;
		break;

	case 'i':
		yIndex = 2;
		break;

	case 'j':
		yIndex = 2;
		xIndex = 1;
		break;

	case 'k':
		yIndex = 2;
		xIndex = 2;
		break;

	case 'l':
		yIndex = 2;
		xIndex = 3;
		break;

	case 'm':
		yIndex = 3;
		break;

	case 'n':
		yIndex = 3;
		xIndex = 1;
		break;

	case 'o':
		yIndex = 3;
		xIndex = 2;
		break;

	case 'p':
		yIndex = 3;
		xIndex = 3;
		break;

	default:
		break;
	}
	mTexture.loadFromImage(Toolbox::getTexture(Toolbox::BLOCK0TEXTURE),
		sf::IntRect(tileWidth * xIndex, tileHeight * yIndex, tileWidth, tileHeight));
}
