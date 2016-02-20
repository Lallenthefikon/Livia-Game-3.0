#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include "EntityHandler.h"
#include "Camera.h"
#include "Texthandler.h"
#include "Animations.h"
#include "Toolbox.h"
#include "Entity.h"

class LayerHandler {
public:
	static LayerHandler& LayerHandler::getInstance();
	void moveBackground(sf::RenderWindow &window, Camera &cam, sf::Vector2f &middleCamCoordPosSceneView, sf::Vector2f &middleCamCoordPosTileView);
	void moveForeground(sf::Vector2f &velocity);
	
	void addForegroundObject(sf::Sprite &foregroundSprite);
	
	void renderBackground(sf::RenderWindow &window);
	void renderForeground(sf::RenderWindow &window);
	void renderHud(sf::RenderWindow &window);

	void addBackground(sf::Texture &backgroundTexture);
	void addLifeSprite(sf::Sprite &life);
	
	void updateHud(sf::Vector2f viewCamCoordPos, sf::Vector2f sceneCamCoordPos);

private:
	LayerHandler();
	~LayerHandler();

	Animations::Textures* mCurrentAnimation;
	int mAnimationIndex;
	float mTimer;
	void animate();

	void updateState();
	void updateANI();
	
	sf::Texture mLifeTexture;
	std::vector<sf::Sprite> mLives;
	std::vector<sf::Sprite> mForegroundObjects;
	Animations::Textures* mHeartAnimation;
	
	Camera mCamera;

	sf::Sprite mBackground1, mBackground2, mBackground3;
	sf::Vector2f mlocalPos1, mlocalPos2, mLocalPos3;
	std::vector<sf::Sprite> mBackgrounds;

	Entityhandler& mEntityHandler;
	Texthandler& mTextHandler;
};

