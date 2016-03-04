#pragma once

#include <SFML\Graphics.hpp>
#include "Animations.h"
#include "Dialogue.h"

class Dialogue0 : public Dialogue
{
public:
	Dialogue0();
	virtual ~Dialogue0();


	static Dialogue0* createDialogue0(sf::Vector2f pos);

	virtual void render(sf::RenderWindow &window);
	virtual void update();
	virtual void setPos(sf::Vector2f newPos);

	virtual sf::Vector2f getPos() { return mSprite.getPosition(); }
	virtual sf::Vector2f getOffset() { return mSpriteOffset; }
	virtual float getWidth() { return mSprite.getGlobalBounds().width; }
	virtual float getHeight() { return mSprite.getGlobalBounds().height; }
	virtual sf::Sprite getSprite() { return mSprite; }

	virtual bool getIsDone() { return mIsDone; }
	virtual bool isOnScreen() { return mIsOnScreen; }
	virtual void setScale(sf::Vector2f newScale) { mSprite.setScale(newScale); }

private:
	Dialogue0(sf::Vector2f pos);
	sf::Sprite mSprite;
	sf::Vector2f mSpriteOffset;

	sf::Texture mTexture;

	Animations::Textures* mCurrentAnimation;
	int mAnimationIndex;
	float mTimer;

	bool mIsDone;
	bool mIsOnScreen = true;

};

