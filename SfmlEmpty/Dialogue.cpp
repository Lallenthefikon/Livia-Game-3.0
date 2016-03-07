#include "Dialogue.h"

Dialogue::Dialogue(sf::Vector2f pos){
	
	mSpriteOffset = sf::Vector2f(mSprite.getLocalBounds().width / 2, mSprite.getLocalBounds().height / 2);
	mSprite.setPosition(pos - mSpriteOffset);
}

Dialogue::~Dialogue() {
}

Dialogue* Dialogue::createDialogue(sf::Vector2f pos) {
	return new Dialogue(pos);
}

void Dialogue::render(sf::RenderWindow &window) {
	window.draw(mSprite);
}

void Dialogue::update() {
}

void Dialogue::setPos(sf::Vector2f newPos) {
	mSprite.setPosition(newPos);
}
