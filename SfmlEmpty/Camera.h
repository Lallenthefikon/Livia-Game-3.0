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
	void updateCamGAME(sf::RenderWindow &window);
	void updateCamEDITOR(sf::Window &window, std::string direction);

	void updateIntestineCam(sf::RenderWindow &window, std::string cameraState);
	/*bool getIsFullscreen(){ return mIsFullscreen; }*/
	sf::View getView(){ return mView; }
	void zoomCameraEDITOR(sf::Event event);
	bool zoomOut(float totalSizeChange, int timesToZoom);
private:
	sf::View mView;
	sf::Vector2f mVelocity;
	sf::Vector2f mAcceleration;
	int mTimesZoomed;
	//sf::FloatRect mMapBounds;
	//sf::Vector2f mEditorCamCenter;
	/*bool mIsFullscreen;*/

	void moveCameraEDITOR(sf::Window &window, sf::Vector2f direction, float speed);
};