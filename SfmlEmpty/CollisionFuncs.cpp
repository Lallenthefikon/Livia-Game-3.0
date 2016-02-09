#include "CollisionFuncs.h"


bool CollisionFuncs::currentCollisionT(sf::Sprite& s0, sf::Sprite& s1){
	float e0Left = s0.getPosition().x;
	float e0Right = s0.getPosition().x + s0.getGlobalBounds().width;
	float e0Top = s0.getPosition().y;
	float e0Bottom = s0.getPosition().y + s0.getGlobalBounds().height;

	float e1Left = s1.getPosition().x;
	float e1Right = s1.getPosition().x + s1.getGlobalBounds().width;
	float e1Top = s1.getPosition().y - 1;
	float e1Bottom = s1.getPosition().y + s1.getGlobalBounds().height + 1;


	// Has collided if all conditions are met
	if (e0Left <= e1Right &&
		e0Right >= e1Left &&
		e0Top <= e1Bottom &&
		e0Bottom >= e1Top) {
		return true;
	}
	else {
		return false;
	}
}

bool CollisionFuncs::currentCollisionB(sf::Sprite& s0, sf::Sprite& s1){
	float e0Left = s0.getPosition().x;
	float e0Right = s0.getPosition().x + s0.getGlobalBounds().width;
	float e0Top = s0.getPosition().y;
	float e0Bottom = s0.getPosition().y + s0.getGlobalBounds().height;

	float e1Left = s1.getPosition().x;
	float e1Right = s1.getPosition().x + s1.getGlobalBounds().width;
	float e1Top = s1.getPosition().y - 1;
	float e1Bottom = s1.getPosition().y + s1.getGlobalBounds().height + 1;


	// Has collided if all conditions are met
	if (e0Left <= e1Right &&
		e0Right >= e1Left &&
		e0Top <= e1Bottom &&
		e0Bottom >= e1Top) {
		return true;
	}
	else {
		return false;
	}
}

bool CollisionFuncs::currentCollisionL(sf::Sprite& s0, sf::Sprite& s1){
	float e0Left = s0.getPosition().x;
	float e0Right = s0.getPosition().x + s0.getGlobalBounds().width;
	float e0Top = s0.getPosition().y;
	float e0Bottom = s0.getPosition().y + s0.getGlobalBounds().height;

	float e1Left = s1.getPosition().x - 1;
	float e1Right = s1.getPosition().x + s1.getGlobalBounds().width + 1;
	float e1Top = s1.getPosition().y;
	float e1Bottom = s1.getPosition().y + s1.getGlobalBounds().height;


	// Has collided if all conditions are met
	if (e0Left <= e1Right &&
		e0Right >= e1Left &&
		e0Top <= e1Bottom &&
		e0Bottom >= e1Top) {
		return true;
	}
	else {
		return false;
	}
}

bool CollisionFuncs::currentCollisionR(sf::Sprite& s0, sf::Sprite& s1){
	float e0Left = s0.getPosition().x;
	float e0Right = s0.getPosition().x + s0.getGlobalBounds().width;
	float e0Top = s0.getPosition().y;
	float e0Bottom = s0.getPosition().y + s0.getGlobalBounds().height;

	float e1Left = s1.getPosition().x - 1;
	float e1Right = s1.getPosition().x + s1.getGlobalBounds().width + 1;
	float e1Top = s1.getPosition().y;
	float e1Bottom = s1.getPosition().y + s1.getGlobalBounds().height ;


	// Has collided if all conditions are met
	if (e0Left <= e1Right &&
		e0Right >= e1Left &&
		e0Top <= e1Bottom &&
		e0Bottom >= e1Top) {
		return true;
	}
	else {
		return false;
	}
}