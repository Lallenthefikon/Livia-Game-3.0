#include "Texthandler.h"

Texthandler::Texthandler() :
mGameOverText("Game Over!", Toolbox::getFont(Toolbox::FONTKEY::GAMEOVER)){
	mGameOverText.setColor(sf::Color::Green);
	mGameOverText.setCharacterSize(90);
}

Texthandler::~Texthandler() {
}

Texthandler & Texthandler::getInstance() {
	static Texthandler textHandler;
	return textHandler;
}

void Texthandler::updateText(sf::Vector2f& centerScreenCoordPos) {
	mGameOverText.setPosition(centerScreenCoordPos.x - mGameOverText.getLocalBounds().width / 2, centerScreenCoordPos.y - mGameOverText.getLocalBounds().height / 2);
}

void Texthandler::renderText(sf::RenderWindow& window) {
	window.draw(mGameOverText);
}

void Texthandler::loadGameOverFont() {

}

void Texthandler::loadDialogueFont() {
}

