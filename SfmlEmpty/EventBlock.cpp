#include "EventBlock.h"


EventBlock::EventBlock(sf::Vector2f pos, Level *level, char eventType) :
	mLevel(level),
	mEventType(eventType){
	//mSprite.scale(0.4081632653061224, 0.4081632653061224);
	mSprite.setTextureRect(sf::IntRect(0, 0, 100, 100));
	mSpriteOffset = sf::Vector2f(mSprite.getLocalBounds().width / 2, mSprite.getLocalBounds().height / 2);
	mSprite.setPosition(pos - mSpriteOffset);
}


EventBlock::~EventBlock() {
}


EventBlock* EventBlock::createEvent(sf::Vector2f pos, Level *level, char eventType) {
	return new EventBlock(pos, level, eventType);
}

void EventBlock::render(sf::RenderWindow &window) {
}

void EventBlock::update() {

}


void EventBlock::setPos(sf::Vector2f newPos) {
	mSprite.setPosition(newPos);
}

void EventBlock::trigger(){
	mLevel->triggerEvent(mEventType);
	mIsAlive = false;
}

