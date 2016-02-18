#include "Texthandler.h"

Texthandler::Texthandler() :
mGameOverText("Game Over", Toolbox::getFont(Toolbox::FONTKEY::GAMEOVER)){
	mGameOverText.setColor(sf::Color::Black);
	mGameOverText.setCharacterSize(600);
	//mGameOverText.scale(0.5, 0.5);
}

Texthandler::~Texthandler() {
}

Texthandler & Texthandler::getInstance() {
	static Texthandler textHandler;
	return textHandler;
}

void Texthandler::updateText(sf::Vector2f& centerScreenCoordPos) {
	mGameOverText.setPosition(centerScreenCoordPos.x - mGameOverText.getGlobalBounds().width / 2, centerScreenCoordPos.y - 540 - mGameOverText.getGlobalBounds().height / 2);
}

void Texthandler::renderText(sf::RenderWindow& window) {
	window.draw(mGameOverText);
}

void Texthandler::loadGameOverFont() {

}

void Texthandler::loadDialogueFont() {
}

