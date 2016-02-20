#include "BlockGoal.h"


BlockGoal::BlockGoal(sf::Vector2f pos) {
	BlockGoal::setTexture();
	mSprite.setTexture(mTexture);
	//mSprite.scale(0.4081632653061224, 0.4081632653061224);
	mSpriteOffset = sf::Vector2f(mSprite.getLocalBounds().width / 2, mSprite.getLocalBounds().height / 2);
	mSprite.setPosition(pos - mSpriteOffset);
}


BlockGoal::~BlockGoal() {
}


Terrain* BlockGoal::createGoal(sf::Vector2f pos) {
	return new BlockGoal(pos);
}

void BlockGoal::render(sf::RenderWindow &window) {
	window.draw(mSprite);
}

void BlockGoal::update() {

}

void BlockGoal::setTexture() {
	mTexture.loadFromImage(Toolbox::getTexture(Toolbox::TEXTUREKEY::GOALTEXTURE));
}

void BlockGoal::setPos(sf::Vector2f newPos) {
	mSprite.setPosition(newPos);
}