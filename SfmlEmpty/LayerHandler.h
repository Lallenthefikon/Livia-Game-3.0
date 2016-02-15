#pragma once
#include <SFML\Graphics.hpp>
#include "EntityHandler.h"

class LayerHandler
{
public:
	
	static LayerHandler& LayerHandler::getInstance();
	void moveBackground(sf::Vector2f &velocity);
	void moveForeground(sf::Vector2f &velocity);
	void addForegroundObject(sf::Sprite &foregroundSprite);
	void render(sf::RenderWindow &window);
	void setBackground(sf::Sprite &background);
private:
	LayerHandler();
	~LayerHandler();
	sf::Sprite mBackground;
	

	std::vector<sf::Sprite*> mForegroundObjects;

};

