#pragma once
#include "Entity.h"
class Overlay 
{

public:
	Overlay();
	~Overlay();
	int getLife();
	void createOverlay(sf::Vector2f)
private:
	std::vector<sf::overlay*> };

