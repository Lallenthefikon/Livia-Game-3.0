#include "EditorEventBlock.h"



EditorEventBlock::EditorEventBlock(sf::Vector2f pos, char type, sf::Vector2f size):
mTileType(type) {

	mTexture.loadFromImage(Toolbox::getTexture(Toolbox::DIALOGUEMAPEDITORTEXTURE));
	mTexture.loadFromImage(Toolbox::getTexture(Toolbox::DIALOGUEBOXSHEET));
	mSprite.setTexture(mTexture);
	mSprite.setTextureRect(sf::IntRect(0,0,size.x,size.y));
	mSpriteOffset = sf::Vector2f(mSprite.getLocalBounds().width / 2, mSprite.getLocalBounds().height / 2);
	mSprite.setPosition(pos - mSpriteOffset);
	mTextType.setFont(Toolbox::getFont(Toolbox::GAMEOVER));
	mTextType.setString(type);
	mTextType.setPosition(pos);
	mTextType.setColor(sf::Color(0, 0, 0, 250));
}


EditorEventBlock::~EditorEventBlock(){
}

Terrain* EditorEventBlock::createEventblock(sf::Vector2f pos, char type, sf::Vector2f size) {
	return new EditorEventBlock(pos, type,size);
}

void EditorEventBlock::render(sf::RenderWindow &window) {
	window.draw(mSprite);
	window.draw(mTextType);
}

void EditorEventBlock::update() {

}

void EditorEventBlock::setPos(sf::Vector2f newPos) {
	mSprite.setPosition(newPos);
	mTextType.setPosition(newPos);
}