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
	case 'a':
		mDecorationID = TEN;
		mCurrentAnimation = Animations::getDecoration10ANI();
		break;
	case 'b':
		mDecorationID = ELEVEN;
		mCurrentAnimation = Animations::getDecoration11ANI();
		break;
	case 'c':
		mDecorationID = TWELVE;
		mCurrentAnimation = Animations::getDecoration12ANI();
		break;
	case 'd':
		mDecorationID = THIRTEEN;
		mCurrentAnimation = Animations::getDecoration13ANI();
		break;
	case 'e':
		mDecorationID = FOURTEEN;
		mCurrentAnimation = Animations::getDecoration14ANI();
		break;
	case 'f':
		mDecorationID = FIFTEEN;
		mCurrentAnimation = Animations::getDecoration15ANI();
		break;
	case 'g':
		mDecorationID = SIXTEEN;
		mCurrentAnimation = Animations::getDecoration16ANI();
		break;
	case 'h':
		mDecorationID = SEVENTEEN;
		mCurrentAnimation = Animations::getDecoration17ANI();
		break;
	case 'i':
		mDecorationID = EIGHTEEN;
		mCurrentAnimation = Animations::getDecoration18ANI();
		break;
	case 'j':
		mDecorationID = NINETEEN;
		mCurrentAnimation = Animations::getDecoration19ANI();
		break;
	case 'k':
		mDecorationID = TWENTY;
		mCurrentAnimation = Animations::getDecoration20ANI();
		break;
	case 'l':
		mDecorationID = TWENTYONE;
		mCurrentAnimation = Animations::getDecoration21ANI();
		break;
	case 'm':
		mDecorationID = TWENTYTWO;
		mCurrentAnimation = Animations::getDecoration22ANI();
		break;
	case 'n':
		mDecorationID = TWENTYTHREE;
		mCurrentAnimation = Animations::getDecoration23ANI();
		break;
	case 'o':
		mDecorationID = TWENTYFOUR;
		mCurrentAnimation = Animations::getDecoration24ANI();
		break;
	case 'p':
		mDecorationID = TWENTYFIVE;
		mCurrentAnimation = Animations::getDecoration25ANI();
		break;
	case 'q':
		mDecorationID = TWENTYSIX;
		mCurrentAnimation = Animations::getDecoration26ANI();
		break;
	case 'r':
		mDecorationID = TWENTYSEVEN;
		mCurrentAnimation = Animations::getDecoration27ANI();
		break;
	case 's':
		mDecorationID = TWENTYEIGHT;
		mCurrentAnimation = Animations::getDecoration28ANI();
		break;
	case 't':
		mDecorationID = TWENTYNINE;
		mCurrentAnimation = Animations::getDecoration29ANI();
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