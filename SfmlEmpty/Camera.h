#pragma once
#include <SFML\Graphics.hpp>
#include "ToolBox.h"
// Ludvig
class Camera
{
public:
	Camera();
	~Camera();
	void resetCamera(float xStart, float yStart, float xStop, float yStop);
	//void render(sf::RenderWindow & window);
	void updateGameCam(sf::RenderWindow &window
	, bool followingLeft, bool followingRight, bool followingDown, bool followingUp);
	
	void updateCamEDITOR(sf::Window &window, std::string direction);

	void centerOnPlayer(sf::RenderWindow &window, int offsetX, int offsetY);

	void updateHubCam(sf::RenderWindow &window, std::string cameraState);
	void updateStomachCam(sf::RenderWindow &window, std::string cameraState);
	void updateThroatCam(sf::RenderWindow &window, std::string cameraState);

	/*bool getIsFullscreen(){ return mIsFullscreen; }*/
	sf::View getTileView(){ return mTileView; }
	sf::View getSceneryView(){ return mSceneryView; }
	void zoomCameraEDITOR(sf::Event event);
	bool zoomOut(float totalSizeChange, int timesToZoom);
	void setCollisionStripe(std::string orientation, sf::RenderWindow &window);
	sf::Vector2f getVelocity(){ return mVelocity; }
	void setLevelBounds(sf::FloatRect levelBounds);

private:
	sf::View mTileView;
	sf::View mSceneryView;
	sf::Vector2f mVelocity;
	sf::Vector2f mAcceleration;
	sf::FloatRect mLevelBounds;
	// Used to keep player from moving backwards
	sf::RectangleShape mCollisionStripe;
	//sf::Sprite mCollisionStripe;
	int mTimesZoomed;
	//sf::FloatRect mMapBounds;
	//sf::Vector2f mEditorCamCenter;
	/*bool mIsFullscreen;*/

	void moveCameraEDITOR(sf::Window &window, sf::Vector2f direction, float speed);
};