#include "Texthandler.h"

Texthandler::Texthandler() :
mGameOverText("Game Over", Toolbox::getFont(Toolbox::FONTKEY::GAMEOVER)),
mWinText("You Win", Toolbox::getFont(Toolbox::FONTKEY::GAMEOVER)),
mText() {
	mGameOverText.setColor(sf::Color::Black);
	mGameOverText.setCharacterSize(600);
	mWinText.setColor(sf::Color::Yellow);
	mWinText.setCharacterSize(600);
	mText.setFont(Toolbox::getFont(Toolbox::FONTKEY::GAMEOVER));
	mText.setColor(sf::Color::Blue);
	mText.setCharacterSize(60);
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
	mWinText.setPosition(centerScreenCoordPos.x - mWinText.getGlobalBounds().width / 2, centerScreenCoordPos.y - 540 - mWinText.getGlobalBounds().height / 2);
	mText.setPosition(centerScreenCoordPos.x - mText.getGlobalBounds().width / 2, centerScreenCoordPos.y - 700 - mText.getGlobalBounds().height / 2);
}

void Texthandler::renderText(sf::RenderWindow& window, std::string text) {
	mText.setString(text);
	window.draw(mText);
	//window.draw(mGameOverText);
}

void Texthandler::loadGameOverFont() {

}

void Texthandler::loadDialogueFont() {
}

void Texthandler::renderGameOver(sf::RenderWindow& window) {
	window.draw(mGameOverText);
}

void Texthandler::renderWin(sf::RenderWindow& window) {
	window.draw(mWinText);
}
