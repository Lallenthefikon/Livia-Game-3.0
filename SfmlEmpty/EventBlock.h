#pragma once

#include "Terrain.h"
#include "Toolbox.h"
#include "Level.h"

class EventBlock : public Terrain {
public:
	virtual ~EventBlock();
	virtual TERRAINTYPE getType() { return Terrain::EVENT; }
	static EventBlock* createEvent(sf::Vector2f pos, Level *level, char eventType);
	virtual void render(sf::RenderWindow &window);
	virtual void update();
	virtual sf::Vector2f getPos() { return mSprite.getPosition(); }
	virtual sf::Vector2f getOffset() { return mSpriteOffset; }
	virtual float getWidth() { return mSprite.getGlobalBounds().width; }
	virtual float getHeight() { return mSprite.getGlobalBounds().height; }
	virtual sf::Sprite getSprite() { return mSprite; }
	virtual bool isOnScreen() { return mIsOnScreen; }
	virtual void setPos(sf::Vector2f newPos);
	virtual void setScale(sf::Vector2f newScale) { mSprite.setScale(newScale); }
	virtual char getTileType() { return mEventType; }
	virtual void trigger();

	void setIsInDialogue(bool f);

	sf::FloatRect bounds;
	std::vector<std::string> pages;
	
private:
	EventBlock(sf::Vector2f pos, Level *level, char eventType);
	
	
	Level* mLevel;
	
	sf::Sprite mSprite;
	sf::Vector2f mSpriteOffset;
	sf::Texture mTexture;

	char mEventType;

	bool mIsOnScreen = true;
	bool mIsInDialogue;
};

