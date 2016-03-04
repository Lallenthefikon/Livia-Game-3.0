#include "Dialogue.h"


Dialogue::Dialogue(sf::Vector2f pos) :
	mTexthandler(Texthandler::getInstance()) {
	Dialogue::setTexture();
	mSprite.setTexture(mTexture);
	//mSprite.scale(0.4081632653061224, 0.4081632653061224);
	mSpriteOffset = sf::Vector2f(mSprite.getLocalBounds().width / 2, mSprite.getLocalBounds().height / 2);
	mSprite.setPosition(pos - mSpriteOffset);
}


Dialogue::~Dialogue() {
}


Dialogue* Dialogue::createDialogue(sf::Vector2f pos) {
	return new Dialogue(pos);
}

void Dialogue::render(sf::RenderWindow &window) {
	//if (mIsInDialogue) {
		window.draw(mSprite);
		sf::Vector2f pos = Toolbox::getPlayerPosition();
		pos.y -= Toolbox::getPlayerSprite().getLocalBounds().height;
		pos.x += Toolbox::getPlayerSprite().getLocalBounds().width;
		mTexthandler.renderText(window, "Hej", pos);

	//}
}

void Dialogue::update() {

}

void Dialogue::setTexture() {
	mTexture.loadFromImage(Toolbox::getTexture(Toolbox::TEXTUREKEY::DIALOGUETEXTURE));
}

void Dialogue::setPos(sf::Vector2f newPos) {
	mSprite.setPosition(newPos);
}

void Dialogue::setIsInDialogue(bool f){
	mIsInDialogue = f;
}

