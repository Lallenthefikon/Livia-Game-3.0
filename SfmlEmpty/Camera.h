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
	void updateCamGAME(sf::Window &window);
	void updateCamEDITOR(sf::Window &window, std::string direction);
	/*bool getIsFullscreen(){ return mIsFullscreen; }*/
	sf::View getView(){ return mView; }
	void zoomCameraEDITOR(sf::Event event);
private:
	sf::View mView;
	//sf::FloatRect mMapBounds;
	//sf::Vector2f mEditorCamCenter;
	/*bool mIsFullscreen;*/

	void moveCameraEDITOR(sf::Window &window, sf::Vector2f direction, float speed);
};