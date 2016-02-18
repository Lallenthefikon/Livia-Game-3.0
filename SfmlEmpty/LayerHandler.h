#pragma once
#include <SFML\Graphics.hpp>
#include "EntityHandler.h"
#include "Camera.h"

class LayerHandler {
public:
	static LayerHandler& getInstance();
	void moveBackground(sf::RenderWindow &window, Camera &cam, sf::Vector2f &middleCamCoordPosSceneView, sf::Vector2f &middleCamCoordPosTileView);
	void moveForeground(sf::Vector2f &velocity);
	void addForegroundObject(sf::Sprite &foregroundSprite);
	void render(sf::RenderWindow &window);
	void renderLayer(sf::RenderWindow &window);
	void addBackground(sf::Texture &backgroundTexture);
private:
	LayerHandler();
	~LayerHandler();
	std::vector<sf::Sprite> mForegroundObjects;
	Camera mCamera;
	sf::Sprite mBackground1, mBackground2, mBackground3;
	sf::Vector2f mlocalPos1, mlocalPos2, mLocalPos3;
	std::vector<sf::Sprite> mBackgrounds;

};

