#include "Decoration.h"

Decoration::Decoration(sf::Vector2f pos, char id, char layer):
mAnimationIndex(0){
	setID(id);
	setLayer(layer);

	mSprite.setTexture(*mCurrentAnimation->at(mAnimationIndex));

	mSpriteOffset = sf::Vector2f(mSprite.getLocalBounds().width / 2, mSprite.getLocalBounds().height / 2);
	mSprite.setPosition(pos - mSpriteOffset);
}

Decoration::~Decoration() {
}

Decoration* Decoration::createDecoration(sf::Vector2f pos, char id, char layer) {
	return new Decoration(pos, id, layer);
}

void Decoration::render(sf::RenderWindow &window) {
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
		mCurrentAnimation = Animations::getDecoration0ANI();
		break;
	case '1':
		mDecorationID = SAYS;
		mCurrentAnimation = Animations::getDecoration1ANI();
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

void Decoration::setLayer(char &layer) {
	switch (layer) {
	case 'f':
		mDecorationLayer = FRONT;
		break;
	case 'b':
		mDecorationLayer = BACK;
		break;
	default:
		break;
	}
}