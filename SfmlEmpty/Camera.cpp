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

void Camera::updateGameCam(sf::RenderWindow &window, bool followingLeft, bool followingRight, bool followingDown, bool followingUp){
	
	float yCamOffset, xCamOffset;

	float speed = 0.09;
	yCamOffset = 100;
	xCamOffset = 500;

	sf::Vector2f playerCoordPos = window.mapPixelToCoords(sf::Vector2i(Toolbox::getPlayerSprite().getPosition()));
	sf::Vector2f viewCoordPos = window.mapPixelToCoords(sf::Vector2i(mTileView.getCenter()));

	// Camera following right
	if (followingRight && (playerCoordPos.x > viewCoordPos.x - xCamOffset)){

		mVelocity.x = Toolbox::getPlayerVelocity().x;
		mTileView.move(sf::Vector2f(mVelocity.x, 0.f));
	}
	// Camera following left
	// Not For standard use
	if (followingLeft &&(playerCoordPos.x < viewCoordPos.x - xCamOffset)){

		mVelocity.x = Toolbox::getPlayerVelocity().x;
		mTileView.move(sf::Vector2f(mVelocity.x, 0.f));
	}
	// Camera following Up
	if (followingUp && (playerCoordPos.y < viewCoordPos.y)){
		
		float deltaY = std::abs(playerCoordPos.y - viewCoordPos.y);
		mVelocity.y = deltaY * -speed;
		mTileView.move(sf::Vector2f(0.f, mVelocity.y));
	}
	// Camera following down
	if (followingDown && (playerCoordPos.y > viewCoordPos.y)){

		float deltaY = std::abs(playerCoordPos.y - viewCoordPos.y);
		mVelocity.y = deltaY * speed;
		mTileView.move(sf::Vector2f(0.f, mVelocity.y));
	}

	// Old static camera
	// Camera is first centered on player then these offsets are applied
	//mTileView.setCenter(sf::Vector2f(Toolbox::getPlayerSprite().getPosition().x + xCamOffset, Toolbox::getPlayerSprite().getPosition().y + yCamOffset));

}

void Camera::updateCamEDITOR(sf::Window &window, std::string direction){
	float speed = 40;
	if (direction == "Up"){
		mTileView.move(sf::Vector2f(0.f * speed, -1.f * speed));
	}
	else if (direction == "Down"){
		mTileView.move(sf::Vector2f(0.f * speed, 1.f * speed));
	}
	else if (direction == "Right"){
		mTileView.move(sf::Vector2f(1.f * speed, 0.f * speed));
		moveCameraEDITOR(window, sf::Vector2f(1.f, 0.f), 40.0f);
	}
	else if (direction == "Left"){
		mTileView.move(sf::Vector2f(-1.f * speed, 0.f * speed));
	}

}

void Camera::centerOnPlayer(sf::RenderWindow &window, int offsetX, int offsetY){
	mTileView.setCenter(Toolbox::getPlayerSprite().getPosition().x + offsetX, Toolbox::getPlayerSprite().getPosition().y + offsetY);
}

void Camera::updateStomachCam(sf::RenderWindow &window, std::string cameraState){
	// Get current screen bounds for reference in other classes
	window.setView(mTileView);
	sf::Vector2f camGlobalCenter = Toolbox::findCoordPos(sf::Vector2i(mTileView.getCenter()), window);
	Toolbox::copyCameraInfo(camGlobalCenter,sf::Vector2f(mTileView.getCenter()));
	
	// Camera updated differently on parts of the level
	std::string currentCamState = cameraState;
	if (currentCamState == "Cutscene"){
		centerOnPlayer(window, 500, 100);
	}
	else if (currentCamState == "Standard"){
		setCollisionStripe("Left", window);
		updateGameCam(window,false,true,true,true);
	}
	else if (currentCamState == "Shake"){

	}
	else if (currentCamState == "ZoomOut"){
		zoomOut(0.5f, 1);
	//	centerOnPlayer(window);
	}
	else if (currentCamState == "ZoomedOut"){
		// Designers
		// Följer åt vänster, följer åt höger, följer neråt, följer uppåt

		updateGameCam(window, false, true, false, false);

		//updateCamGAME(window);
	}
	else if (currentCamState == "SecondCutscene"){

	}
	else if (currentCamState == "Rising"){
		//updateStomachStandardCam(window, sf::Vector2f(0.f, 1.f));
	}
	else if (currentCamState == "FinalCutscene"){

	}
	Toolbox::setGlobalCameraBounds(window);
}

void Camera::updateThroatCam(sf::RenderWindow & window, std::string cameraState){
	// Get current screen bounds for reference in other classes
	window.setView(mTileView);
	sf::Vector2f camGlobalCenter = Toolbox::findCoordPos(sf::Vector2i(mTileView.getCenter()), window);
	Toolbox::copyCameraInfo(camGlobalCenter, sf::Vector2f(mTileView.getCenter()));

	// Camera updated differently on parts of the level
	std::string currentCamState = cameraState;
	if (currentCamState == "Cutscene") {
		centerOnPlayer(window, 150, 0);
	}
	else if (currentCamState == "Standard") {
		setCollisionStripe("Left", window);
		updateGameCam(window, false, false, true, true);
	}
	else if (currentCamState == "Shake") {

	}
	else if (currentCamState == "ZoomOut") {
		zoomOut(0.5f, 1);
		//	centerOnPlayer(window);
	}
	else if (currentCamState == "ZoomedOut") {
		// Designers
		// Följer åt vänster, följer åt höger, följer neråt, följer uppåt

		updateGameCam(window, false, false, true, true);

		//updateCamGAME(window);
	}
	else if (currentCamState == "SecondCutscene") {

	}
	else if (currentCamState == "Rising") {
		//updateStomachStandardCam(window, sf::Vector2f(0.f, 1.f));
	}
	else if (currentCamState == "FinalCutscene") {

	}
}

void Camera::updateHubCam(sf::RenderWindow &window, std::string cameraState) {
	// Get current screen bounds for reference in other classes
	window.setView(mTileView);
	sf::Vector2f camGlobalCenter = Toolbox::findCoordPos(sf::Vector2i(mTileView.getCenter()), window);
	Toolbox::copyCameraInfo(camGlobalCenter, sf::Vector2f(mTileView.getCenter()));

	// Camera updated differently on parts of the level
	std::string currentCamState = cameraState;
	if (currentCamState == "Center") {
		centerOnPlayer(window, 0,-100);
	}
	else if (currentCamState == "Standard") {
		//setCollisionStripe("Left", window);
		updateGameCam(window, true, true, true, true);
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

void Camera::setLevelBounds(sf::FloatRect levelBounds){
	mLevelBounds = levelBounds;
}