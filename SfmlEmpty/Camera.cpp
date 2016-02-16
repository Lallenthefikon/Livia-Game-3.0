#include "Camera.h"
#include <iostream>


Camera::Camera() :
mView(sf::FloatRect(0.f, 0.f, 1920, 1080)),
mVelocity(0,0),
mAcceleration(0,0),
mTimesZoomed(0), 
mCollisionStripe(sf::Vector2f(10, 1920)) {
	// Default view
	mCollisionStripe.setFillColor(sf::Color::Blue);
	mView.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
}

Camera::~Camera(){
}

void Camera::moveCameraEDITOR(sf::Window &window, sf::Vector2f direction, float speed){
	mView.move(sf::Vector2f(direction.x * speed, direction.y * speed));
}

void Camera::updateCamGAME(sf::RenderWindow &window){
	// Camera is first centered on player then these offsets are applied
	float yCamOffset, xCamOffset;
	/*float decay = 0.98f;
	float timeStep = 1 / 60;*/
	yCamOffset = 100;
	xCamOffset = 500;

	//sf::Vector2f playerCoordPos = window.mapPixelToCoords(sf::Vector2i(Toolbox::getPlayerSprite().getPosition()));
	//sf::Vector2f viewCoordPos = window.mapPixelToCoords(sf::Vector2i(mView.getCenter()));

	//if (playerCoordPos.x > viewCoordPos.x - xCamOffset){

	//	mView.move(sf::Vector2f(Toolbox::getPlayerVelocity().x, 0.f));

	//}
	//if (playerCoordPos.y < viewCoordPos.y){
	//	
	//	if (std::abs(playerCoordPos.y - viewCoordPos.y) <= 10){
	//		mVelocity.y = 0;
	//	}
	//	else{
	//		//mVelocity.y += Toolbox::getPlayerVelocity().y*0.4f;
	//		mAcceleration.y = 0.5f;
	//		mVelocity.y -= mAcceleration.y;
	//	}
	//	//mVelocity.y += (Toolbox::getPlayerVelocity().y /Toolbox::getPlayerVelocity().y)*0.99f;

	//	mView.move(sf::Vector2f(0.f, mVelocity.y));
	//	
	//}
	//if (playerCoordPos.y > viewCoordPos.y){
	//				//mVelocity.y += (Toolbox::getPlayerVelocity().y / Toolbox::getPlayerVelocity().y)*0.99f;
	//	if (std::abs(playerCoordPos.y - viewCoordPos.y) <= 50){
	//		mVelocity.y = 0;
	//	}
	//	else if (playerCoordPos.y > viewCoordPos.y + yCamOffset){
	//		mAcceleration.y = 4.0f;
	//		mVelocity.y += mAcceleration.y;
	//	}
	//	else{
	//		mAcceleration.y = 0.5f;
	//		mVelocity.y += mAcceleration.y;
	//		//mVelocity.y += Toolbox::getPlayerVelocity().y*0.4f;
	//	}

	//	mView.move(sf::Vector2f(0.f, mVelocity.y));
	//}

	//mVelocity *= decay;

	mView.setCenter(sf::Vector2f(Toolbox::getPlayerSprite().getPosition().x + xCamOffset, Toolbox::getPlayerSprite().getPosition().y + yCamOffset));
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

void Camera::updateIntestineCam(sf::RenderWindow &window, std::string cameraState){
	
	std::string currentCamState = cameraState;
	if (currentCamState == "Cutscene"){
		
	}
	else if (currentCamState == "Standard"){
		setCollisionStripe("Left", window);
		updateCamGAME(window);
	}
	else if (currentCamState == "Shake"){

	}
	else if (currentCamState == "Zoom out"){
		zoomOut(10.f, 1000);
	}
	else if (currentCamState == "ZoomedOutStandard"){
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
		mView.zoom(0.9f);
	}
	else if (event.mouseWheel.delta < 0){
		mView.zoom(1.1f);
	}
}

bool Camera::zoomOut(float totalSizeChange, int timesToZoom){
	if (mTimesZoomed < timesToZoom){
		float fractalZoom = totalSizeChange / timesToZoom;
		mView.zoom(1.f / fractalZoom);
		mTimesZoomed++;
		return false;
	}
	else{
		mTimesZoomed = 0;
		return true;
	}
}

void Camera::setCollisionStripe(std::string orientation, sf::RenderWindow &window){
	sf::Vector2f viewCoordPos = window.mapPixelToCoords(sf::Vector2i(mView.getCenter()));
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