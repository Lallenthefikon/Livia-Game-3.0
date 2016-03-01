#pragma once

#include <SFML\Graphics.hpp>
#include "Animations.h"

class Decoration {
public:
	enum DECORATIONID { FLOWER, SAYS, HIGH, FIVE, FOURTWENTYBLAZEITFAGGOT };
	static Decoration* createDecoration(sf::Vector2f pos, char id);
	~Decoration();

	void render(sf::RenderWindow &window);
	void update();
	void setPos(sf::Vector2f newPos);
	
	sf::Vector2f getPos() { return mSprite.getPosition(); }
	sf::Vector2f getOffset() { return mSpriteOffset; }
	float getWidth() { return mSprite.getGlobalBounds().width; }
	float getHeight() { return mSprite.getGlobalBounds().height; }
	sf::Sprite getSprite() { return mSprite; }
	
	bool isOnScreen() { return mIsOnScreen; }
	void setScale(sf::Vector2f newScale) { mSprite.setScale(newScale); }
	
	DECORATIONID getDecorationID() { return mDecorationID; }

private:
	Decoration(sf::Vector2f pos, char id);
	void setID(char &id);
	sf::Sprite mSprite;
	sf::Vector2f mSpriteOffset;

	sf::Texture mTexture;

	Animations::Textures* mCurrentAnimation;
	int mAnimationIndex;
	float mTimer;

	DECORATIONID mDecorationID;

	bool mIsOnScreen = true;

};

