#pragma once
#include <SFML\Graphics.hpp>
#include "EntityHandler.h"

class LayerHandler
{
public:
	static LayerHandler& getInstance();
	void moveBackground(sf::Vector2i &pixelPos, sf::Vector2f &coordPos);
	void moveForeground(sf::Vector2f &velocity);
	void addForegroundObject(sf::Sprite &foregroundSprite);
	void render(sf::RenderWindow &window);
	void addBackground(sf::Sprite &background);
private:
	LayerHandler();
	~LayerHandler();
	std::vector<sf::Sprite> mForegroundObjects;
	std::vector<sf::Sprite> mBackgrounds;

};

