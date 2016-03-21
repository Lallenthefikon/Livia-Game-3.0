#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include "EntityHandler.h"
#include "Dialoguehandler.h"
#include "Camera.h"
#include "Texthandler.h"
#include "Animations.h"
#include "Toolbox.h"
#include "Entity.h"

class LayerHandler {
public:
	static LayerHandler& LayerHandler::getInstance();
	void moveBackgroundHorizontal(sf::RenderWindow &window, Camera &cam, sf::Vector2f &middleCamCoordPosSceneView, sf::Vector2f &middleCamCoordPosTileView);
	void moveBackgroundVertical(sf::RenderWindow &window, Camera &cam, sf::Vector2f &middleCamCoordPosSceneView, sf::Vector2f &middleCamCoordPosTileView);
	void moveMiddleground(sf::RenderWindow &window, Camera &cam, sf::Vector2f &middleCamCoordPosSceneView, sf::Vector2f &middleCamCoordPosTileView, std::string orientation);
	void moveForeground(sf::Vector2f &velocity);
	// Unused
	void moveStationaryBackground(sf::RenderWindow &window, Camera &cam, sf::Vector2f &middleCamCoordPosSceneView, sf::Vector2f &middleCamCoordPosTileView);
	void moveStationaryForeground(sf::RenderWindow &window, Camera &cam, sf::Vector2f &middleCamCoordPosSceneView, sf::Vector2f &middleCamCoordPosTileView);
	
	void renderBackground(sf::RenderWindow &window);
	void renderMiddleground(sf::RenderWindow &window);
	void renderForeground(sf::RenderWindow &window);
	void renderHud(sf::RenderWindow &window);
	void renderVertGradiant(sf::RenderWindow &window);

	void addVerticalBackground(sf::Texture &backgroundTexture);
	void addHorizontalBackground(sf::Texture &backgroundTexture);
	void addMiddleground(sf::Texture &backgroundTexture, std::string orientation, sf::IntRect middlegroundBounds);
	void addForegroundObject(sf::Texture &foregroundTexture);

	void addLifeSprite(sf::Sprite &life);
	
	void addAcid(sf::Texture &acidTexture);
	void addAcidGradiantVertical(sf::Texture &vertGrad);
	void addAcidGradiantHoriz(sf::Texture &vertGrad);
	void updateHud(sf::Vector2f viewCamCoordPos, sf::Vector2f sceneCamCoordPos);

	void updateLife();

	void updateVertGlowAlpha(int alpha);

	void clearLife();

	~LayerHandler();
private:
	LayerHandler();

	Animations::Textures* mCurrentAnimation;
	int mAnimationIndex;
	float mTimer;

	void animate();

	void updateState();
	void updateANI();

	void internalClear();

	sf::Texture mLifeTexture;
	//std::vector<sf::Sprite> mDialogues;
	sf::Sprite mLifeSprite;
	std::vector<sf::Sprite> mLives;
	std::vector<sf::Sprite> mForegroundObjects;
	Animations::Textures* mHeartAnimation;
	
	Camera mCamera;

	sf::Sprite mBackground, mMiddleground, mForeground, mAcidGlowVert;
	sf::Vector2f mlocalPos1, mlocalPos2, mLocalPos3;
	std::vector<sf::Sprite> mBackgrounds, mMiddlegrounds;

	Entityhandler* mEntityHandler;
	Texthandler& mTextHandler;
	Dialoguehandler& mDialogueHandler;

	int mPreviousLife;
	int mMaxLife;
};

