#include "Decoration.h"

Decoration::Decoration(sf::Vector2f pos, char id):
mCurrentAnimation(Animations::getDecorationANI()),
mAnimationIndex(0){
	setID(id);
	mSprite.setTexture(*mCurrentAnimation->at(mAnimationIndex));

	mSpriteOffset = sf::Vector2f(mSprite.getLocalBounds().width / 2, mSprite.getLocalBounds().height / 2);
	mSprite.setPosition(pos - mSpriteOffset);
}

Decoration::~Decoration() {
}

Decoration* Decoration::createDecoration(sf::Vector2f pos, char id) {
	return new Decoration(pos, id);
}

void Decoration::render(sf::RenderWindow & window) {
	window.draw(mSprite);
}

void Decoration::update() {
}

void Decoration::setPos(sf::Vector2f newPos) {
	mSprite.setPosition(newPos);
}

void Decoration::setID(char &id) {
	switch (id) {
	case '0':
		mDecorationID = FLOWER;
		break;
	case '1':
		mDecorationID = SAYS;
		break;
	case '2':
		mDecorationID = HIGH;
		break;
	case '3':
		mDecorationID = FIVE;
		break;
	case '4':
		mDecorationID = FOURTWENTYBLAZEITFAGGOT;
		break;
	default:
		break;
	}
}