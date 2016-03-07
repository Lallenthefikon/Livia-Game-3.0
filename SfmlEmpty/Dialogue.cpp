#include "Dialogue.h"

Dialogue::Dialogue(sf::Vector2f pos){
	sf::Texture texture;
	texture.loadFromImage(Toolbox::getTexture(Toolbox::DIALOGUETEXTURE));
	mSprite.setTexture(texture);
	mSpriteOffset = sf::Vector2f(mSprite.getLocalBounds().width / 2, mSprite.getLocalBounds().height / 2);
	mSprite.setPosition(pos - mSpriteOffset);
}

Dialogue::~Dialogue() {
}

Terrain* Dialogue::createDialogue(sf::Vector2f pos) {
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
