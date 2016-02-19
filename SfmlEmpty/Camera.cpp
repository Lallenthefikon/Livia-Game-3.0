#include "Camera.h"
#include <iostream>


Camera::Camera() :
mTileView(sf::FloatRect(0.f, 0.f, 1920, 1080)),
mSceneryView(sf::FloatRect(0.f, 0.f, 1920, 1080)),
mVelocity(0,0),
mAcceleration(0,0),
mTimesZoomed(0), 
mCollisionStripe(sf::Vector2f(10, 1920)) {
	// Default view
	mCollisionStripe.setFillColor(sf::Color::Blue);
	mTileView.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
	mSceneryView.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
}

Camera::~Camera(){
}

void Camera::moveCameraEDITOR(sf::Window &window, sf::Vector2f direction, float speed){
	mTileView.move(sf::Vector2f(direction.x * speed, direction.y * speed));
}

void Camera::updateCamGAME(sf::RenderWindow &window){
	
	float yCamOffset, xCamOffset;

	float speed = 0.09;
	yCamOffset = 100;
	xCamOffset = 500;

	sf::Vector2f playerCoordPos = window.mapPixelToCoords(sf::Vector2i(Toolbox::getPlayerSprite().getPosition()));
	sf::Vector2f viewCoordPos = window.mapPixelToCoords(sf::Vector2i(mTileView.getCenter()));


	if (playerCoordPos.x > viewCoordPos.x - xCamOffset){

		mVelocity.x = Toolbox::getPlayerVelocity().x;
		mTileView.move(sf::Vector2f(mVelocity.x, 0.f));
	}
	if (playerCoordPos.y < viewCoordPos.y){
		
		float deltaY = std::abs(playerCoordPos.y - viewCoordPos.y);
		mVelocity.y = deltaY * -speed;
		mTileView.move(sf::Vector2f(0.f, mVelocity.y));
	}
	if (playerCoordPos.y > viewCoordPos.y){

		float deltaY = std::abs(playerCoordPos.y - viewCoordPos.y);
		mVelocity.y = deltaY * speed;
		mTileView.move(sf::Vector2f(0.f, mVelocity.y));
	}

	// Camera is first centered on player then these offsets are applied

	//mTileView.setCenter(sf::Vector2f(Toolbox::getPlayerSprite().getPosition().x + xCamOffset, Toolbox::getPlayerSprite().getPosition().y + yCamOffset));

}

void Camera::updateCamEDITOR(sf::Window &window, std::string direction){
	if (direction == "Up"){
		moveCameraEDITOR(window, sf::Vector2f(0.f, -1.f), 40.0f);
	}
	else if (direction == "Down"){
		moveCameraEDITOR(window, sf::Vector2f(0.f, 1.f), 40.0f);
	}
	else if (direction == "Right"){
		moveCameraEDITOR(window, sf::Vector2f(1.f, 0.f), 40.0f);
	}
	else if (direction == "Left"){
		moveCameraEDITOR(window, sf::Vector2f(-1.f, 0.f), 40.0f);
	}
}

void Camera::centerOnPlayer(sf::RenderWindow &window){
//	sf::Vector2f playerCoordPos = window.mapPixelToCoords(sf::Vector2i(Toolbox::getPlayerSprite().getPosition()));
	int xCamOffset = 500;
	sf::Vector2f viewCoordPos = Toolbox::findCoordPos(sf::Vector2i(Toolbox::getPlayerSprite().getPosition().x + xCamOffset, Toolbox::getPlayerSprite().getPosition().y), window);
	//sf::Vector2f viewCoordPos = window.mapPixelToCoords(sf::Vector2i(mTileView.getCenter()));
	
	mTileView.setCenter(viewCoordPos);
}

void Camera::updateStomachCam(sf::RenderWindow &window, std::string cameraState){
	
	std::string currentCamState = cameraState;
	if (currentCamState == "Cutscene"){
		centerOnPlayer(window);
	}
	else if (currentCamState == "Standard"){
		setCollisionStripe("Left", window);
		updateCamGAME(window);
	}
	else if (currentCamState == "Shake"){

	}
	else if (currentCamState == "ZoomOut"){
		zoomOut(10.f, 1000);
	}
	else if (currentCamState == "ZoomedOut"){
		updateCamGAME(window);
	}
	else if (currentCamState == "SecondCutscene"){

	}
	else if (currentCamState == "Rising"){

	}
	else if (currentCamState == "FinalCutscene"){

	}
}

void Camera::zoomCameraEDITOR(sf::Event event){
	if (event.mouseWheel.delta > 0){
		mTileView.zoom(0.9f);
	}
	else if (event.mouseWheel.delta < 0){
		mTileView.zoom(1.1f);
	}
}

bool Camera::zoomOut(float totalSizeChange, int timesToZoom){
	if (mTimesZoomed < timesToZoom){
		float fractalZoom = totalSizeChange / timesToZoom;
		mTileView.zoom(1.f / fractalZoom);
		mTimesZoomed++;
		return false;
	}
	else{
		mTimesZoomed = 0;
		return true;
	}
}

void Camera::setCollisionStripe(std::string orientation, sf::RenderWindow &window){
	sf::Vector2f viewCoordPos = window.mapPixelToCoords(sf::Vector2i(mTileView.getCenter()));
	sf::Vector2f playerCoordPos = window.mapPixelToCoords(sf::Vector2i(Toolbox::getPlayerSprite().getPosition()));
	if (orientation == "Left"){

		mCollisionStripe.setSize(sf::Vector2f(10,1920));
		mCollisionStripe.setPosition(playerCoordPos.x, playerCoordPos.y);
		mCollisionStripe.setFillColor(sf::Color::Blue);
		//mCollisionStripe.setTextureRect(sf::IntRect(viewCoordPos.x, viewCoordPos.y - 1080 / 2, 10, 1920));
			//(T rectLeft, T rectTop, T rectWidth, T rectHeight)  - 1920 / 2 - 10
	}
	//if (orientation == "Left"){
	//	mCollisionStripe.setTextureRect(sf::IntRect(viewCoordPos.x - 1920 / 2 - 10, viewCoordPos.y - 1080 / 2, 10, 1920));
	//	//(T rectLeft, T rectTop, T rectWidth, T rectHeight)
	//}
}