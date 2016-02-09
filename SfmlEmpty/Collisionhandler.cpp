#include "Collisionhandler.h"
#include <iostream>

Collisionhandler::Collisionhandler():
playerOutline(),
terrainOutline(),
terrainOutline1(),
line1(),
line2(){
}

Collisionhandler::~Collisionhandler(){
}

Collisionhandler& Collisionhandler::getInstance(){
	static Collisionhandler collisionhandler;
	return collisionhandler;
}

void Collisionhandler::checkCollision(Entities &entities, Terrains &terrains){
	collisionBetweenEntities(entities);
	collisionBetweenEntitiesAndTerrains(entities, terrains);
}

void Collisionhandler::collisionBetweenEntities(Entities &entities){
	for (Entities::size_type i = 0; i < entities.size(); i++){
		Entity *e0 = entities[i];
		for (Entities::size_type j = i + 1; j < entities.size(); j++){
			Entity *e1 = entities[j];
			if (e0->isOnScreen() && e1->isOnScreen()) {
				if (hasCollided(e0, e1)) {
					if (e0->getType() != e1->getType() && e0->getType() == Entity::PLAYER) {
						checkCollisionDirection(e0, e1);
						//checkCollisionDirection(e1, e0);
					}
				}
			}
		}
	}
}

void Collisionhandler::collisionBetweenEntitiesAndTerrains(Entities &entities, Terrains &terrains){
	for (Entities::size_type i = 0; i < entities.size(); i++){
		Entity *e0 = entities[i];
		for (Terrains::size_type j = 0; j < terrains.size(); j++){
			Terrain *e1 = terrains[j];
			if (e0->isOnScreen() && e1->isOnScreen()) {
				if (hasCollided(e0, e1)) {
					checkCollisionDirection(e0, e1);
				}
			}
		}
	}
}

bool Collisionhandler::hasCollided(Entity *e0, Entity *e1) {

	float e0Left = e0->getPos().x;
	float e0Right = e0->getPos().x + e0->getWidth();
	float e0Top = e0->getPos().y;
	float e0Bottom = e0->getPos().y + e0->getHeight();

	float e1Left = e1->getPos().x;
	float e1Right = e1->getPos().x + e1->getWidth();
	float e1Top = e1->getPos().y;
	float e1Bottom = e1->getPos().y + e1->getHeight();

	// Has collided if all conditions are met
	if (e0Left < e1Right &&
		e0Right > e1Left &&
		e0Top < e1Bottom &&
		e0Bottom > e1Top) {
		return true;
	}
	else {
		return false;
	}
}

bool Collisionhandler::hasCollided(Entity *e0, Terrain *e1) {

	float e0Left = e0->getPos().x;
	float e0Right = e0->getPos().x + e0->getWidth();
	float e0Top = e0->getPos().y;
	float e0Bottom = e0->getPos().y + e0->getHeight();

	float e1Left = e1->getPos().x;
	float e1Right = e1->getPos().x + e1->getWidth();
	float e1Top = e1->getPos().y;
	float e1Bottom = e1->getPos().y + e1->getHeight();


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

// Collision between entities
void Collisionhandler::checkCollisionDirection(Entity *e0, Entity *e1) {
	float e0Left = e0->getPos().x;
	float e0Right = e0->getPos().x + e0->getWidth();
	float e0Top = e0->getPos().y;
	float e0Bottom = e0->getPos().y + e0->getHeight();

	float e1Left = e1->getPos().x;
	float e1Right = e1->getPos().x + e1->getWidth();
	float e1Top = e1->getPos().y;
	float e1Bottom = e1->getPos().y + e1->getHeight();

	float deltaBottomCollision = e1Bottom - e0Top; // Distance between the enemy's bottom edge and the player's top edge
	float deltaTopCollision = e0Bottom - e1Top; // Distance between the player's bottom edge and the enemy's top edge
	float deltaLeftCollision = e0Right - e1Left;
	float deltaRightCollision = e1Right - e0Left;

	

	// Checks if deltaTopCollision is the smallest value, 
	if (deltaTopCollision < deltaBottomCollision && deltaTopCollision < deltaLeftCollision && deltaTopCollision < deltaRightCollision) {
		// Top collision, e0 collided with e1's top edge
		// lallen e0->move(sf::Vector2f(0, -1));
	}
	// Checks if deltaBottomCollision is the smallest value
	if (deltaBottomCollision < deltaTopCollision && deltaBottomCollision < deltaLeftCollision && deltaBottomCollision < deltaRightCollision) {
		// Bottom collision
		// lallen e0->move(sf::Vector2f(0, 1));
	}
	// Checks if deltaLeftCollision is the smallest value
	if (deltaLeftCollision < deltaRightCollision && deltaLeftCollision < deltaTopCollision && deltaLeftCollision < deltaBottomCollision) {
		// Left collision
		// lallen e0->move(sf::Vector2f(-1, 0));
	}
	// Checks if deltaRightCollision is the smallest value	
	if (deltaRightCollision < deltaLeftCollision && deltaRightCollision < deltaTopCollision && deltaRightCollision < deltaBottomCollision) {
		// Right collision
		// lallen e0->move(sf::Vector2f(1, 0));
		
	}
}

// Collision between an entity and a terrain
void Collisionhandler::checkCollisionDirection(Entity *e0, Terrain *e1) {
	/*terrainOutline.setSize(sf::Vector2f(e1->getWidth(), e1->getHeight()));
	terrainOutline.setPosition(e1->getPos());
	terrainOutline.setFillColor(sf::Color::Yellow);*/

	float e0Left = e0->getPos().x;
	float e0Right = e0->getPos().x + e0->getWidth();
	float e0Top = e0->getPos().y;
	float e0Bottom = e0->getPos().y + e0->getHeight();

	float e1Left = e1->getPos().x;
	float e1Right = e1->getPos().x + e1->getWidth();
	float e1Top = e1->getPos().y;
	float e1Bottom = e1->getPos().y + e1->getHeight();

	/*line1.setSize(sf::Vector2f(e0->getWidth(), 1));
	line1.setFillColor(sf::Color::Blue);
	line1.setPosition(e0Left, e0Bottom);

	line2.setSize(sf::Vector2f(e1->getWidth(), 1));
	line2.setFillColor(sf::Color::Magenta);
	line2.setPosition(e1Left, e1Top);*/

	float deltaBottomCollision = e1Bottom - e0Top; // Distance between the enemy's bottom edge and the player's top edge
	float deltaTopCollision = e0Bottom - e1Top; // Distance between the player's bottom edge and the enemy's top edge
	float deltaLeftCollision = e0Right - e1Left;
	float deltaRightCollision = e1Right - e0Left;

	//std::cout << "deltaTop: " << deltaTopCollision << " deltaBottom: " << deltaBottomCollision << " deltaLeft: " << deltaLeftCollision << " deltaRight: " << deltaRightCollision << std::endl;

	// Checks if deltaTopCollision is the smallest value
	if (deltaTopCollision < deltaBottomCollision && deltaTopCollision < deltaLeftCollision && deltaTopCollision < deltaRightCollision) {
		// Top collision, e0 collided with e1's top edge
		// lallen e0->move(sf::Vector2f(0, -1 * deltaTopCollision));
		e0->terrainCollision(e1, 'b');
	}
	// Checks if deltaBottomCollision is the smallest value
	if (deltaBottomCollision < deltaTopCollision && deltaBottomCollision < deltaLeftCollision && deltaBottomCollision < deltaRightCollision) {
		// Bottom collision
		// lallen e0->move(sf::Vector2f(0, 1 * deltaBottomCollision));
		e0->terrainCollision(e1, 't');
	}
	// Checks if deltaLeftCollision is the smallest value
	if (deltaLeftCollision < deltaRightCollision && deltaLeftCollision < deltaTopCollision && deltaLeftCollision < deltaBottomCollision) {
		// Left collision
		// lallen e0->move(sf::Vector2f(-1 * deltaLeftCollision, 0));
		e0->terrainCollision(e1, 'r');
	}
	// Checks if deltaRightCollision is the smallest value	
	if (deltaRightCollision < deltaLeftCollision && deltaRightCollision < deltaTopCollision && deltaRightCollision < deltaBottomCollision ) {
		// Right collision
		// lallen e0->move(sf::Vector2f(1 * deltaRightCollision, 0));
		e0->terrainCollision(e1, 'l');
	}
	/*playerOutline.setSize(sf::Vector2f(e0->getWidth(), e0->getHeight()));
	playerOutline.setPosition(e0->getPos());
	playerOutline.setFillColor(sf::Color::Red);*/
}

void Collisionhandler::renderCollision(sf::RenderWindow &window) {
	window.draw(terrainOutline);
	window.draw(playerOutline);
	window.draw(terrainOutline1);
	window.draw(line1);
	window.draw(line2);
}