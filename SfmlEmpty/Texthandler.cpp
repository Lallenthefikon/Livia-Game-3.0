#include "Texthandler.h"

Texthandler::Texthandler() :
mGameOverText("Game Over!", Toolbox::getFont(Toolbox::FONTKEY::GAMEOVER)){
	mGameOverText.setColor(sf::Color::Green);
	mGameOverText.setCharacterSize(60);
}

Texthandler::~Texthandler() {
}

Texthandler & Texthandler::getInstance() {
	static Texthandler textHandler;
	return textHandler;
}

void Texthandler::updateText(sf::RenderWindow& window) {
	mGameOverText.setPosition(
		window.getSize().x / 2 - mGameOverText.getLocalBounds().width / 2, 
		window.getSize().y / 2 - mGameOverText.getLocalBounds().height / 2);
}

void Texthandler::renderText(sf::RenderWindow& window) {
	window.draw(mGameOverText);
}

void Texthandler::loadGameOverFont() {

}

void Texthandler::loadDialogueFont() {
}

