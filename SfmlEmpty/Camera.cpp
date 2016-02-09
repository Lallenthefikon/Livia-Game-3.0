#include "Camera.h"
#include <iostream>


Camera::Camera() :
mView(sf::FloatRect(0.f, 0.f, 1920, 1080)){
	// Default view
	mView.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
}

Camera::~Camera(){
}

void Camera::moveCameraEDITOR(sf::Window &window, sf::Vector2f direction, float speed){
	mView.move(sf::Vector2f(direction.x * speed, direction.y * speed));
}

void Camera::updateCamGAME(sf::Window &window){
	// Camera is first centered on player then these offsets are applied
	float yCamOffset, xCamOffset;
	yCamOffset = 100;
	xCamOffset = 500;

	mView.setCenter(sf::Vector2f(Toolbox::getPlayerSprite().getPosition().x + xCamOffset, Toolbox::getPlayerSprite().getPosition().y + yCamOffset));
}

void Camera::updateCamEDITOR(sf::Window &window, std::string direction){
	if (direction == "Up")
		moveCameraEDITOR(window, sf::Vector2f(0.f, -1.f), 10.0f);
	else if (direction == "Down"){
		moveCameraEDITOR(window, sf::Vector2f(0.f, 1.f), 10.0f);
	}
	else if (direction == "Right"){
		moveCameraEDITOR(window, sf::Vector2f(1.f, 0.f), 10.0f);
	}
	else if (direction == "Left"){
		moveCameraEDITOR(window, sf::Vector2f(-1.f, 0.f), 10.0f);
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