#include "Texthandler.h"

Texthandler::Texthandler() :
mGameOverText("Game Over", Toolbox::getFont(Toolbox::FONTKEY::GAMEOVER)),
mWinText("You Win", Toolbox::getFont(Toolbox::FONTKEY::GAMEOVER)),
mText(), 
mLayerText() {
}

Texthandler::~Texthandler() {
}

Texthandler & Texthandler::getInstance() {
	static Texthandler textHandler;
	return textHandler;
}

void Texthandler::updateText(sf::Vector2f& centerScreenCoordPos) {
	mCenter = centerScreenCoordPos;
	mLayerText.setPosition(mCenter.x - mText.getGlobalBounds().width / 2, mCenter.y - 700 - mText.getGlobalBounds().height / 2);
	

	//mGameOverText.setPosition(centerScreenCoordPos.x - mGameOverText.getGlobalBounds().width / 2, centerScreenCoordPos.y - 540 - mGameOverText.getGlobalBounds().height / 2);
	//mWinText.setPosition(centerScreenCoordPos.x - mWinText.getGlobalBounds().width / 2, centerScreenCoordPos.y - 540 - mWinText.getGlobalBounds().height / 2);
	//mText.setPosition(centerScreenCoordPos.x - mText.getGlobalBounds().width / 2, centerScreenCoordPos.y - 700 - mText.getGlobalBounds().height / 2);
	//
}

void Texthandler::renderText(sf::RenderWindow& window, std::string text) {
	mText.setString(text);
	window.draw(mText);
	//window.draw(mGameOverText);
}

void Texthandler::renderCurrentLayer(sf::RenderWindow& window, std::string text) {

	mText.setString(text);
	
	window.draw(mText);
	//window.draw(mGameOverText);
}

void Texthandler::setDialougeText(std::string &text0, std::string &text1, std::string &text2){
	mDialogueText0.setString(text0);
	mDialogueText1.setString(text1);
	mDialogueText2.setString(text2);
}


void Texthandler::renderGameOver(sf::RenderWindow& window) {
	window.draw(mGameOverText);
}

void Texthandler::renderWin(sf::RenderWindow& window) {
	window.draw(mWinText);
}

void Texthandler::renderDialougeText(sf::RenderWindow& window){
	
	window.draw(mDialogueText0);
	window.draw(mDialogueText1);
	window.draw(mDialogueText2);
}

void Texthandler::loadTexts() {
	Texthandler::loadDialogueFont();
	mGameOverText.setColor(sf::Color::Black);
	mGameOverText.setCharacterSize(600);
	mWinText.setColor(sf::Color::Yellow);
	mWinText.setCharacterSize(600);
	mText.setFont(Toolbox::getFont(Toolbox::FONTKEY::GAMEOVER));
	mText.setColor(sf::Color::Blue);
	mText.setCharacterSize(60);
	mLayerText.setFont(Toolbox::getFont(Toolbox::FONTKEY::GAMEOVER));
	mLayerText.setColor(sf::Color::Blue);
	mLayerText.setCharacterSize(60);
	//mGameOverText.scale(0.5, 0.5);

}

void Texthandler::loadGameOverFont() {

}

void Texthandler::loadDialogueFont() {
	float xPos(500);
	float yPos(1000);
	mDialogueText0.setFont(Toolbox::getFont(Toolbox::DIALOGUE));
	mDialogueText1.setFont(Toolbox::getFont(Toolbox::DIALOGUE));
	mDialogueText2.setFont(Toolbox::getFont(Toolbox::DIALOGUE));
	mDialogueText0.setPosition(sf::Vector2f(xPos, yPos - 200));
	mDialogueText1.setPosition(sf::Vector2f(xPos, yPos - 150));
	mDialogueText2.setPosition(sf::Vector2f(xPos, yPos - 100));

}
