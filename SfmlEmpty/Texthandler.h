#pragma once

#include "Toolbox.h"
#include <SFML\Graphics.hpp>

class Texthandler {
public:
	static Texthandler& getInstance();
	void updateText(sf::Vector2f& centerScreenCoordPos);
	void renderText(sf::RenderWindow& window);
	void renderGameOver(sf::RenderWindow& window);
	void renderWin(sf::RenderWindow& window);
	void loadGameOverFont();
	void loadDialogueFont();
	~Texthandler();
private:
	Texthandler();
	sf::Text mGameOverText;
	sf::Text mDialogueText;
	sf::Text mWinText;

};

