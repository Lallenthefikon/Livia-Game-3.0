#pragma once

#include <SFML\Graphics.hpp>

class Level{
public:
	Level();
	~Level();
	virtual void update(sf::RenderWindow &window) = 0;
	virtual void render(sf::RenderWindow &window) = 0;
	virtual void loadLevel() = 0;
	virtual void unloadLevel() = 0;
	virtual std::string getLevelName() = 0;
	virtual std::string getLevelDirectory() = 0;
	virtual void triggerEvent(char type) = 0;
};