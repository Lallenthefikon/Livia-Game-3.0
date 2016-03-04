#include "Dialogue0.h"

Dialogue0::Dialogue0(sf::Vector2f pos) {

	mSpriteOffset = sf::Vector2f(mSprite.getLocalBounds().width / 2, mSprite.getLocalBounds().height / 2);
	mSprite.setPosition(pos - mSpriteOffset);
}

Dialogue0::~Dialogue0() {
}

Dialogue0* Dialogue0::createDialogue0(sf::Vector2f pos) {
	return new Dialogue0(pos);
}

void Dialogue0::render(sf::RenderWindow &window) {
	window.draw(mSprite);
}

void Dialogue0::update() {
}

void Dialogue0::setPos(sf::Vector2f newPos) {
	mSprite.setPosition(newPos);
}
