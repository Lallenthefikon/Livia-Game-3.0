#include "EventBlock.h"


EventBlock::EventBlock(sf::Vector2f pos) :
	mTexthandler(Texthandler::getInstance()) {
	EventBlock::setTexture();
	mSprite.setTexture(mTexture);
	//mSprite.scale(0.4081632653061224, 0.4081632653061224);
	mSpriteOffset = sf::Vector2f(mSprite.getLocalBounds().width / 2, mSprite.getLocalBounds().height / 2);
	mSprite.setPosition(pos - mSpriteOffset);
}


EventBlock::~EventBlock() {
}


EventBlock* EventBlock::createDialogue(sf::Vector2f pos) {
	return new EventBlock(pos);
}

void EventBlock::render(sf::RenderWindow &window) {
	//if (mIsInDialogue) {
		window.draw(mSprite);
		sf::Vector2f pos = Toolbox::getPlayerPosition();
		pos.y -= Toolbox::getPlayerSprite().getLocalBounds().height;
		pos.x += Toolbox::getPlayerSprite().getLocalBounds().width;
		mTexthandler.renderText(window, "Hej");

	//}
}

void EventBlock::update() {

}

void EventBlock::setTexture() {
	mTexture.loadFromImage(Toolbox::getTexture(Toolbox::TEXTUREKEY::DIALOGUETEXTURE));
}

void EventBlock::setPos(sf::Vector2f newPos) {
	mSprite.setPosition(newPos);
}

void EventBlock::setIsInDialogue(bool f){
	mIsInDialogue = f;
}

