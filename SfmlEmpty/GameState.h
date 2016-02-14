#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

class GameState{
public:
	GameState();
	~GameState();
	virtual void update(sf::RenderWindow &window) = 0;
	virtual void render(sf::RenderWindow &window) = 0;
	virtual void loadLevel() = 0;
	virtual void setCurrentLevel(std::string &levelDirectory, std::string &levelName) = 0;
};

