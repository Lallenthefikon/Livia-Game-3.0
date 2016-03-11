#include "EditorEventBlock.h"



EditorEventBlock::EditorEventBlock(sf::Vector2f pos, char type):
mTileType(type) {
	mTexture.loadFromImage(Toolbox::getTexture(Toolbox::DIALOGUEMAPEDITORTEXTURE));
	mSprite.setTexture(mTexture);
	mSprite.setTextureRect(sf::IntRect(0,0,100,100));
	mSpriteOffset = sf::Vector2f(mSprite.getLocalBounds().width / 2, mSprite.getLocalBounds().height / 2);
	mSprite.setPosition(pos - mSpriteOffset);
	mTextType.setFont(Toolbox::getFont(Toolbox::GAMEOVER));
	mTextType.setString(type);
	mTextType.setPosition(pos);
	mTextType.setColor(sf::Color(0, 0, 0, 250));

}


EditorEventBlock::~EditorEventBlock(){
}

Terrain* EditorEventBlock::createEventblock(sf::Vector2f pos, char type) {
	return new EditorEventBlock(pos, type);
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