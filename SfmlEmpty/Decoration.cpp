#include "Decoration.h"

Decoration::Decoration(sf::Vector2f pos, char id, char layer, char rotation):
mAnimationIndex(0),
mRotation(rotation) {
	Decoration::setID(id);
	Decoration::setLayer(layer);
	mSprite.setTexture(*mCurrentAnimation->at(mAnimationIndex));
	Decoration::setRotation(mRotation);

	mSpriteOffset = sf::Vector2f(mSprite.getLocalBounds().width / 2, mSprite.getLocalBounds().height / 2 - 3);
	mSprite.setPosition(pos - mSpriteOffset);
}

Decoration::~Decoration() {
}

Decoration* Decoration::createDecoration(sf::Vector2f pos, char id, char layer, char rotation) {
	return new Decoration(pos, id, layer, rotation);
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
		mCurrentAnimation = Animations::getDecoration2ANI();
		break;
	case '3':
		mDecorationID = FIVE;
		mCurrentAnimation = Animations::getDecoration3ANI();
		break;
	case '4':
		mDecorationID = FOURTWENTYBLAZEITFAGGOT;
		mCurrentAnimation = Animations::getDecoration4ANI();
		break;
	case '5':
		mDecorationID = DANK;
		mCurrentAnimation = Animations::getDecoration5ANI();
		break;
	case '6':
		mDecorationID = SHREK;
		mCurrentAnimation = Animations::getDecoration6ANI();
		break;
	case '7':
		mDecorationID = TRUMP;
		mCurrentAnimation = Animations::getDecoration7ANI();
		break;
	case '8':
		mDecorationID = BERNIE;
		mCurrentAnimation = Animations::getDecoration8ANI();
		break;
	case '9':
		mDecorationID = LIVIA;
		mCurrentAnimation = Animations::getDecoration9ANI();
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

void Decoration::setRotation(char &rotation) {
	switch (rotation) {
	case 't':
		break;
	case 'l':
		mSprite.setOrigin(mSprite.getGlobalBounds().width, 0);
		mSprite.rotate(270);
		break;
	case 'b':
		mSprite.setOrigin(mSprite.getGlobalBounds().width, mSprite.getGlobalBounds().height);
		mSprite.rotate(180);
		break;
	case 'r':
		mSprite.setOrigin(0, mSprite.getGlobalBounds().height);
		mSprite.rotate(90);
		break;
	default:
		break;
	}
}