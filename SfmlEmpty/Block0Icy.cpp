#include "Block0Icy.h"



Block0Icy::Block0Icy(sf::Vector2f pos, char type):
mTileType(type){
	Block0Icy::setTexture(type);
	mSprite.setTexture(mTexture);
	mSpriteOffset = sf::Vector2f(mSprite.getLocalBounds().width / 2, mSprite.getLocalBounds().height / 2);
	mSprite.setPosition(pos - mSpriteOffset);
}


Block0Icy::~Block0Icy(){
}

Terrain* Block0Icy::createBlock0Icy(sf::Vector2f pos, char type) {
	return new Block0Icy(pos, type);
}

void Block0Icy::render(sf::RenderWindow &window) {
	window.draw(mSprite);
}

void Block0Icy::update() {

}

void Block0Icy::setTexture(char type) {
	float tileWidth(100);
	float tileHeight(100);
	int xIndex(0);
	int yIndex(0);

	switch (type) {

	case 'a':
		break;

	case 'b':
		xIndex = 1;
		break;

	case 'c':
		xIndex = 2;
		break;

	case 'd':
		xIndex = 6;
		yIndex = 2;
		break;

	case 'e':
		xIndex = 6;
		yIndex = 1;
		break;

	case 'f':
		yIndex = 1;
		xIndex = 1;
		break;

	case 'g':
		yIndex = 2;
		xIndex = 7;
		break;

	case 'h':
		yIndex = 1;
		xIndex = 7;
		break;

	case 'i':
		yIndex = 2;
		xIndex = 5;
		break;

	case 'j':
		yIndex = 1;
		xIndex = 5;
		break;

	case 'k':
		xIndex = 6;
		break;

	case 'l':

		xIndex = 5;
		break;

	case 'm':
		yIndex = 2;
		xIndex = 4;
		break;

	case 'n':
		yIndex = 1;
		xIndex = 4;
		break;

	case 'o':
		yIndex = 0;
		xIndex = 4;
		break;

	case 'p':
		yIndex = 0;
		xIndex = 4;
		break;

	default:
		break;
	}
	mTexture.loadFromImage(Toolbox::getTexture(Toolbox::ACIDMONSTERHORIZONTALTEXTURE),
		sf::IntRect(tileWidth * xIndex, tileHeight * yIndex, tileWidth, tileHeight));
}

void Block0Icy::setPos(sf::Vector2f newPos) {
	mSprite.setPosition(newPos);
}