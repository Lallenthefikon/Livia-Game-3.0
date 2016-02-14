#pragma once
#include <SFML\Graphics.hpp>

class LayerHandler
{
public:
	
	LayerHandler& LayerHandler::getInstance(sf::Sprite &background);
	void moveBackground(sf::Vector2f &velocity);
	void moveForeground(sf::Vector2f &velocity);
	void addForegroundObject(sf::Sprite &foregroundSprite);
	void render(sf::Window &window);
private:
	LayerHandler(sf::Sprite &background);
	~LayerHandler();
	sf::Sprite mBackground;
	std::vector<sf::Sprite*> mForegroundObjects;
};

