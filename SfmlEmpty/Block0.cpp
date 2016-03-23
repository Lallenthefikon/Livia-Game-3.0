#include "Block0.h"

Block0::Block0(sf::Vector2f pos, char type, char type1):
mTileType(type){
	Block0::setTexture(type);
	
	mSprite.setTexture(mTexture);
	mSpriteOffset = sf::Vector2f(mSprite.getLocalBounds().width / 2, mSprite.getLocalBounds().height / 2);
	mSprite.setPosition(pos - mSpriteOffset);
	Block0::createDecorations(type1);
}

Block0::~Block0(){
}

Terrain* Block0::createBlock0(sf::Vector2f pos, char type, char type1){
	return new Block0(pos, type, type1);
}

void Block0::render(sf::RenderWindow &window){
	window.draw(mSprite);
	for (int i = 0; i < mTileDecorations.size(); i++) {
		window.draw(*mTileDecorations[i]);
	}
}

void Block0::update(){

}

void Block0::setTexture(char type) {
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

	if (Toolbox::getCurrentLevelName() == "Hub") {
		xIndex += 8;
		yIndex += 4;
	}
	else if (Toolbox::getCurrentLevelName() == "Intestine") {
		xIndex += 8;
	}
	else if (Toolbox::getCurrentLevelName() == "Mouth") {
		xIndex += 4;
		yIndex += 4;
	}


	mTexture.loadFromImage(Toolbox::getTexture(Toolbox::BLOCK0TEXTURE),
		sf::IntRect(tileWidth * xIndex, tileHeight * yIndex, tileWidth, tileHeight));

}

void Block0::createDecorations(char type1){
	int Index(0);

	if (Toolbox::getCurrentLevelName() == "Hub") {
		Index += 4;
	}
	else if (Toolbox::getCurrentLevelName() == "Stomach"|| Toolbox::getCurrentLevelName() == "Throat") {
		Index += 2;
	}

	switch (type1) {
	case 'a':
		mTileDecorations.push_back(new sf::Sprite);
		mTileDecorations.back()->setTexture(*Animations::getTileDecTextures()->at(Index + 12));
		mTileDecorations.back()->setPosition(mSprite.getPosition());
		mTileDecorations.push_back(new sf::Sprite);
		mTileDecorations.back()->setTexture(*Animations::getTileDecTextures()->at(Index + 13));
		mTileDecorations.back()->setPosition(mSprite.getPosition());
		break;
	case 'b':
		mTileDecorations.push_back(new sf::Sprite);
		mTileDecorations.back()->setTexture(*Animations::getTileDecTextures()->at(Index + 13));
		mTileDecorations.back()->setPosition(mSprite.getPosition());
		break;
	case 'c':
		mTileDecorations.push_back(new sf::Sprite);
		mTileDecorations.back()->setTexture(*Animations::getTileDecTextures()->at(Index + 18));
		mTileDecorations.back()->setPosition(mSprite.getPosition());
		break;
	case 'd':
		mTileDecorations.push_back(new sf::Sprite);
		mTileDecorations.back()->setTexture(*Animations::getTileDecTextures()->at(Index + 19));
		mTileDecorations.back()->setPosition(mSprite.getPosition());
		break;
	case 'e':
		mTileDecorations.push_back(new sf::Sprite);
		mTileDecorations.back()->setTexture(*Animations::getTileDecTextures()->at(Index + 12));
		mTileDecorations.back()->setPosition(mSprite.getPosition());
		break;
	case 'f':
		mTileDecorations.push_back(new sf::Sprite);
		mTileDecorations.back()->setTexture(*Animations::getTileDecTextures()->at(Index + 0));
		mTileDecorations.back()->setPosition(mSprite.getPosition());
		break;
	case 'g':
		mTileDecorations.push_back(new sf::Sprite);
		mTileDecorations.back()->setTexture(*Animations::getTileDecTextures()->at(Index + 6));
		mTileDecorations.back()->setPosition(mSprite.getPosition());
		break;
	case 'h':
		mTileDecorations.push_back(new sf::Sprite);
		mTileDecorations.back()->setTexture(*Animations::getTileDecTextures()->at(Index + 7));
		mTileDecorations.back()->setPosition(mSprite.getPosition());
		break;
	case 'i':
		mTileDecorations.push_back(new sf::Sprite);
		mTileDecorations.back()->setTexture(*Animations::getTileDecTextures()->at(Index + 1));
		mTileDecorations.back()->setPosition(mSprite.getPosition());
		break;
	case 'j':
		mTileDecorations.push_back(new sf::Sprite);
		mTileDecorations.back()->setTexture(*Animations::getTileDecTextures()->at(Index + 13));
		mTileDecorations.back()->setPosition(mSprite.getPosition());
		mTileDecorations.push_back(new sf::Sprite);
		mTileDecorations.back()->setTexture(*Animations::getTileDecTextures()->at(Index + 6));
		mTileDecorations.back()->setPosition(mSprite.getPosition());
		break;
	case 'k':
		mTileDecorations.push_back(new sf::Sprite);
		mTileDecorations.back()->setTexture(*Animations::getTileDecTextures()->at(Index + 18));
		mTileDecorations.back()->setPosition(mSprite.getPosition());
		mTileDecorations.push_back(new sf::Sprite);
		mTileDecorations.back()->setTexture(*Animations::getTileDecTextures()->at(Index + 7));
		mTileDecorations.back()->setPosition(mSprite.getPosition());
		break;
	case 'l':
		mTileDecorations.push_back(new sf::Sprite);
		mTileDecorations.back()->setTexture(*Animations::getTileDecTextures()->at(Index + 18));
		mTileDecorations.back()->setPosition(mSprite.getPosition());
		mTileDecorations.push_back(new sf::Sprite);
		mTileDecorations.back()->setTexture(*Animations::getTileDecTextures()->at(Index + 6));
		mTileDecorations.back()->setPosition(mSprite.getPosition());
		break;
	case 'm':
		mTileDecorations.push_back(new sf::Sprite);
		mTileDecorations.back()->setTexture(*Animations::getTileDecTextures()->at(Index + 12));
		mTileDecorations.back()->setPosition(mSprite.getPosition());
		mTileDecorations.push_back(new sf::Sprite);
		mTileDecorations.back()->setTexture(*Animations::getTileDecTextures()->at(Index + 7));
		mTileDecorations.back()->setPosition(mSprite.getPosition());
		break;
	default:
		break;
	}

}

void Block0::setPos(sf::Vector2f newPos){
	mSprite.setPosition(newPos);
}