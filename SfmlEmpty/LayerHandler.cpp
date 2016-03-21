#include "LayerHandler.h"
#include <iostream>

float BACKGROUNDSPEED = 0.2f; // 10.07f
float MIDDLEGROUNDSPEED = BACKGROUNDSPEED * 2;
float FOREGROUNDSPEED;

static float ANIFramesPerFrame(0.25);

LayerHandler::LayerHandler() :
mEntityHandler(Entityhandler::getInstance()),
mTextHandler(Texthandler::getInstance()),
mDialogueHandler(Dialoguehandler::getInstance()),
mHeartAnimation(Animations::getHeartANI()),
mMiddlegrounds(3),
mBackgrounds(3),
mPreviousLife(-1),
mMaxLife(20) {
	//mForegroundObjects.push_back(background);
}

LayerHandler::~LayerHandler(){
	LayerHandler::internalClear();
}

LayerHandler& LayerHandler::getInstance(){
	static LayerHandler layerHandler;
	return layerHandler;
}

void LayerHandler::moveBackgroundHorizontal(sf::RenderWindow &window, Camera &cam, sf::Vector2f &middleCamCoordPosSceneView, sf::Vector2f &middleCamCoordPosTileView){

	sf::Sprite* furthestRightBG;
	sf::Sprite* furthestLeftBG;
	sf::Sprite* middleBG;

	sf::Vector2f bg0CoordPos = Toolbox::findCoordPos(sf::Vector2i(mBackgrounds[0].getPosition().x, mBackgrounds[0].getPosition().y), window);
	sf::Vector2f bg1CoordPos = Toolbox::findCoordPos(sf::Vector2i(mBackgrounds[1].getPosition().x, mBackgrounds[1].getPosition().y), window);
	sf::Vector2f bg2CoordPos = Toolbox::findCoordPos(sf::Vector2i(mBackgrounds[2].getPosition().x, mBackgrounds[2].getPosition().y), window);
	
	// Find the background furthest to the right
	if ((bg0CoordPos.x > bg1CoordPos.x)
		&& (bg0CoordPos.x > bg2CoordPos.x)){
		furthestRightBG = &mBackgrounds[0];
		//std::cout << "Right 0" << std::endl;
	}
	else if ((bg1CoordPos.x > bg0CoordPos.x)
		&& (bg1CoordPos.x > bg2CoordPos.x)){
		furthestRightBG = &mBackgrounds[1];
		//std::cout << "Right 1" << std::endl;
	}
	else{
		furthestRightBG = &mBackgrounds[2];
		//std::cout << "Right 2" << std::endl;
	}
	// Find the background furthest to the left
	if ((bg0CoordPos.x < bg1CoordPos.x)
		&& (bg0CoordPos.x < bg2CoordPos.x)){
		furthestLeftBG = &mBackgrounds[0];
		//std::cout << "Left 0" << std::endl;
	}
	else if ((bg1CoordPos.x < bg0CoordPos.x)
		&& (bg1CoordPos.x < bg2CoordPos.x)){
		furthestLeftBG = &mBackgrounds[1];
		//std::cout << "Left 1" << std::endl;
	}
	else{
		furthestLeftBG = &mBackgrounds[2];
		//std::cout << "Left 2" << std::endl;
	}
	// Find the background in the middle
	if ((furthestLeftBG == &mBackgrounds[0] && furthestRightBG == &mBackgrounds[1])
		|| (furthestLeftBG == &mBackgrounds[1] && furthestRightBG == &mBackgrounds[0])){
		middleBG = &mBackgrounds[2];
		//std::cout << "Middle 2" << std::endl;
	}
	else if ((furthestLeftBG == &mBackgrounds[0] && furthestRightBG == &mBackgrounds[2])
		|| (furthestLeftBG == &mBackgrounds[2] && furthestRightBG == &mBackgrounds[0])){
		middleBG = &mBackgrounds[1];
		//std::cout << "Middle 1" << std::endl;
	}
	else{
		middleBG = &mBackgrounds[0];
		//std::cout << "Middle 0" << std::endl;
	}

	sf::Vector2f middleBgCoordPos = Toolbox::findCoordPos(sf::Vector2i(middleBG->getPosition().x, middleBG->getPosition().y), window);
	sf::Vector2f leftBgCoordPos = Toolbox::findCoordPos(sf::Vector2i(furthestLeftBG->getPosition().x, furthestLeftBG->getPosition().y), window);
	sf::Vector2f rightBgCoordPos = Toolbox::findCoordPos(sf::Vector2i(furthestRightBG->getPosition().x, furthestRightBG->getPosition().y), window);
	
	// Resets furthest left when moving right 
	if (furthestLeftBG->getPosition().x < -furthestLeftBG->getLocalBounds().width){
		furthestLeftBG->setPosition(furthestRightBG->getPosition().x + furthestLeftBG->getLocalBounds().width, 0);
	}
	// Resets furthest right when moving left 
	else if ((furthestRightBG->getPosition().x > 1920) && (cam.getVelocity().x < 0)) {
		furthestRightBG->setPosition(furthestLeftBG->getPosition().x - furthestLeftBG->getLocalBounds().width, 0);
	}

	// Moves backgrounds at same speed
	float camVelX = cam.getVelocity().x;

	furthestRightBG->move(-camVelX * BACKGROUNDSPEED, 0.f);
	middleBG->move(-camVelX * BACKGROUNDSPEED, 0.f);
	furthestLeftBG->move(-camVelX * BACKGROUNDSPEED, 0.f);
}

void LayerHandler::moveBackgroundVertical(sf::RenderWindow &window, Camera &cam, sf::Vector2f &middleCamCoordPosSceneView, sf::Vector2f &middleCamCoordPosTileView) {

	sf::Sprite* furthestUpBG;
	sf::Sprite* furthestDownBG;
	sf::Sprite* middleBG;

	sf::Vector2f bg0CoordPos = Toolbox::findCoordPos(sf::Vector2i(mBackgrounds[0].getPosition().x, mBackgrounds[0].getPosition().y), window);
	sf::Vector2f bg1CoordPos = Toolbox::findCoordPos(sf::Vector2i(mBackgrounds[1].getPosition().x, mBackgrounds[1].getPosition().y), window);
	sf::Vector2f bg2CoordPos = Toolbox::findCoordPos(sf::Vector2i(mBackgrounds[2].getPosition().x, mBackgrounds[2].getPosition().y), window);

	// Find the background highest up
	if ((bg0CoordPos.y < bg1CoordPos.y)
		&& (bg0CoordPos.y < bg2CoordPos.y)) {
		furthestUpBG = &mBackgrounds[0];
		//std::cout << "Right 0" << std::endl;
	}
	else if ((bg1CoordPos.y < bg0CoordPos.y)
		&& (bg1CoordPos.y < bg2CoordPos.y)) {
		furthestUpBG = &mBackgrounds[1];
		//std::cout << "Right 1" << std::endl;
	}
	else {
		furthestUpBG = &mBackgrounds[2];
		//std::cout << "Right 2" << std::endl;
	}
	// Find the background lowest down
	if ((bg0CoordPos.y > bg1CoordPos.y)
		&& (bg0CoordPos.y > bg2CoordPos.y)) {
		furthestDownBG = &mBackgrounds[0];
		//std::cout << "Left 0" << std::endl;
	}
	else if ((bg1CoordPos.y > bg0CoordPos.y)
		&& (bg1CoordPos.y > bg2CoordPos.y)) {
		furthestDownBG = &mBackgrounds[1];
		//std::cout << "Left 1" << std::endl;
	}
	else {
		furthestDownBG = &mBackgrounds[2];
		//std::cout << "Left 2" << std::endl;
	}
	// Find the background in the middle
	if ((furthestDownBG == &mBackgrounds[0] && furthestUpBG == &mBackgrounds[1])
		|| (furthestDownBG == &mBackgrounds[1] && furthestUpBG == &mBackgrounds[0])) {
		middleBG = &mBackgrounds[2];
		//std::cout << "Middle 2" << std::endl;
	}
	else if ((furthestDownBG == &mBackgrounds[0] && furthestUpBG == &mBackgrounds[2])
		|| (furthestDownBG == &mBackgrounds[2] && furthestUpBG == &mBackgrounds[0])) {
		middleBG = &mBackgrounds[1];
		//std::cout << "Middle 1" << std::endl;
	}
	else {
		middleBG = &mBackgrounds[0];
		//std::cout << "Middle 0" << std::endl;
	}

	//std::cout << "Top: " << furthestUpBG->getPosition().y << "Middle: " << middleBG->getPosition().y << "Btm: " << furthestDownBG->getPosition().y << std::endl;

	sf::Vector2f middleBgCoordPos = Toolbox::findCoordPos(sf::Vector2i(middleBG->getPosition().x, middleBG->getPosition().y), window);
	sf::Vector2f leftBgCoordPos = Toolbox::findCoordPos(sf::Vector2i(furthestDownBG->getPosition().x, furthestDownBG->getPosition().y), window);
	sf::Vector2f rightBgCoordPos = Toolbox::findCoordPos(sf::Vector2i(furthestUpBG->getPosition().x, furthestUpBG->getPosition().y), window);

	// Resets furthest left when moving right 
	if (furthestDownBG->getPosition().y < furthestDownBG->getLocalBounds().height) {
		furthestDownBG->setPosition(0, furthestUpBG->getPosition().y + furthestDownBG->getLocalBounds().height);
	}
	// Resets furthest right when moving left 
	/*else if ((furthestUpBG->getPosition().y > 1080) && (cam.getVelocity().y < 0)) {
		furthestUpBG->setPosition(0, furthestUpBG->getPosition().y + furthestDownBG->getLocalBounds().height);
	}*/

	// Moves backgrounds at same speed
	float camVelY = cam.getVelocity().y;

	furthestUpBG->move(0, -camVelY * BACKGROUNDSPEED);
	middleBG->setPosition(furthestUpBG->getPosition().x, furthestUpBG->getPosition().y);
	furthestDownBG->setPosition(middleBG->getPosition().x, middleBG->getPosition().y);
	//middleBG->move(0, -camVelY * BACKGROUNDSPEED);
	//furthestDownBG->move(0, -camVelY * BACKGROUNDSPEED);
}

void LayerHandler::moveMiddleground(sf::RenderWindow & window, Camera & cam, sf::Vector2f & middleCamCoordPosSceneView, sf::Vector2f & middleCamCoordPosTileView){
	sf::Sprite* furthestRightMG;
	sf::Sprite* furthestLeftMG;
	sf::Sprite* middleMG;

	sf::Vector2f mg0CoordPos = Toolbox::findCoordPos(sf::Vector2i(mMiddlegrounds[0].getPosition().x, mMiddlegrounds[0].getPosition().y), window);
	sf::Vector2f mg1CoordPos = Toolbox::findCoordPos(sf::Vector2i(mMiddlegrounds[1].getPosition().x, mMiddlegrounds[1].getPosition().y), window);
	sf::Vector2f mg2CoordPos = Toolbox::findCoordPos(sf::Vector2i(mMiddlegrounds[2].getPosition().x, mMiddlegrounds[2].getPosition().y), window);

	// Find the background furthest to the right
	if ((mg0CoordPos.x > mg1CoordPos.x)
		&& (mg0CoordPos.x > mg2CoordPos.x)) {
		furthestRightMG = &mMiddlegrounds[0];
		//std::cout << "Right 0" << std::endl;
	}
	else if ((mg1CoordPos.x > mg0CoordPos.x)
		&& (mg1CoordPos.x > mg2CoordPos.x)) {
		furthestRightMG = &mMiddlegrounds[1];
		//std::cout << "Right 1" << std::endl;
	}
	else {
		furthestRightMG = &mMiddlegrounds[2];
		//std::cout << "Right 2" << std::endl;
	}
	// Find the background furthest to the left
	if ((mg0CoordPos.x < mg1CoordPos.x)
		&& (mg0CoordPos.x < mg2CoordPos.x)) {
		furthestLeftMG = &mMiddlegrounds[0];
		//std::cout << "Left 0" << std::endl;
	}
	else if ((mg1CoordPos.x < mg0CoordPos.x)
		&& (mg1CoordPos.x < mg2CoordPos.x)) {
		furthestLeftMG = &mMiddlegrounds[1];
		//std::cout << "Left 1" << std::endl;
	}
	else {
		furthestLeftMG = &mMiddlegrounds[2];
		//std::cout << "Left 2" << std::endl;
	}
	// Find the background in the middle
	if ((furthestLeftMG == &mBackgrounds[0] && furthestRightMG == &mMiddlegrounds[1])
		|| (furthestLeftMG == &mMiddlegrounds[1] && furthestRightMG == &mMiddlegrounds[0])) {
		middleMG = &mMiddlegrounds[2];
		//std::cout << "Middle 2" << std::endl;
	}
	else if ((furthestLeftMG == &mMiddlegrounds[0] && furthestRightMG == &mMiddlegrounds[2])
		|| (furthestLeftMG == &mMiddlegrounds[2] && furthestRightMG == &mMiddlegrounds[0])) {
		middleMG = &mMiddlegrounds[1];
		//std::cout << "Middle 1" << std::endl;
	}
	else {
		middleMG = &mMiddlegrounds[0];
		//std::cout << "Middle 0" << std::endl;
	}

	sf::Vector2f middleMgCoordPos = Toolbox::findCoordPos(sf::Vector2i(middleMG->getPosition().x, middleMG->getPosition().y), window);
	sf::Vector2f leftMgCoordPos = Toolbox::findCoordPos(sf::Vector2i(furthestLeftMG->getPosition().x, furthestLeftMG->getPosition().y), window);
	sf::Vector2f rightMgCoordPos = Toolbox::findCoordPos(sf::Vector2i(furthestRightMG->getPosition().x, furthestRightMG->getPosition().y), window);

	// Resets furthest left when moving right 
	if (furthestLeftMG->getPosition().x < -furthestLeftMG->getLocalBounds().width) {
		furthestLeftMG->setPosition(furthestRightMG->getPosition().x + furthestLeftMG->getLocalBounds().width, 0);
	}
	// Resets furthest right when moving left 
	else if ((furthestRightMG->getPosition().x > 1920) && (cam.getVelocity().x < 0)) {
		furthestRightMG->setPosition(furthestLeftMG->getPosition().x - furthestLeftMG->getLocalBounds().width, 0);
	}

	// Moves backgrounds at same speed
	float camVelX = cam.getVelocity().x;

	furthestRightMG->move(-camVelX * MIDDLEGROUNDSPEED, 0.f);
	middleMG->move(-camVelX * MIDDLEGROUNDSPEED, 0.f);
	furthestLeftMG->move(-camVelX * MIDDLEGROUNDSPEED, 0.f);
}

void LayerHandler::moveStationaryBackground(sf::RenderWindow &window, Camera &cam, sf::Vector2f &middleCamCoordPosSceneView, sf::Vector2f &middleCamCoordPosTileView){

	sf::Sprite* furthestRightBG;
	sf::Sprite* furthestLeftBG;
	sf::Sprite* middleBG;

	sf::Vector2f bg0CoordPos = Toolbox::findCoordPos(sf::Vector2i(mBackgrounds[0].getPosition().x, mBackgrounds[0].getPosition().y), window);
	sf::Vector2f bg1CoordPos = Toolbox::findCoordPos(sf::Vector2i(mBackgrounds[1].getPosition().x, mBackgrounds[1].getPosition().y), window);
	sf::Vector2f bg2CoordPos = Toolbox::findCoordPos(sf::Vector2i(mBackgrounds[2].getPosition().x, mBackgrounds[2].getPosition().y), window);

	// Find the background furthest to the right
	if ((bg0CoordPos.x > bg1CoordPos.x)
		&& (bg0CoordPos.x > bg2CoordPos.x)){
		furthestRightBG = &mBackgrounds[0];
	}
	else if ((bg1CoordPos.x > bg0CoordPos.x)
		&& (bg1CoordPos.x > bg2CoordPos.x)){
		furthestRightBG = &mBackgrounds[1];
	}
	else{
		furthestRightBG = &mBackgrounds[2];
	}
	// Find the background furthest to the left
	if ((bg0CoordPos.x < bg1CoordPos.x)
		&& (bg0CoordPos.x < bg2CoordPos.x)){
		furthestLeftBG = &mBackgrounds[0];
	}
	else if ((bg1CoordPos.x < bg0CoordPos.x)
		&& (bg1CoordPos.x < bg2CoordPos.x)){
		furthestLeftBG = &mBackgrounds[1];
	}
	else{
		furthestLeftBG = &mBackgrounds[2];
	}
	// Find the background in the middle
	if ((furthestLeftBG == &mBackgrounds[0] && furthestRightBG == &mBackgrounds[1])
		|| (furthestLeftBG == &mBackgrounds[1] && furthestRightBG == &mBackgrounds[0])){
		middleBG = &mBackgrounds[2];
	}
	else 	if ((furthestLeftBG == &mBackgrounds[0] && furthestRightBG == &mBackgrounds[2])
		|| (furthestLeftBG == &mBackgrounds[2] && furthestRightBG == &mBackgrounds[0])){
		middleBG = &mBackgrounds[1];
	}
	else{
		middleBG = &mBackgrounds[0];
	}

	furthestRightBG->setPosition(cam.getSceneryView().getCenter().x, cam.getSceneryView().getCenter().y - furthestRightBG->getLocalBounds().height/2);
	middleBG->setPosition(cam.getSceneryView().getCenter().x - middleBG->getLocalBounds().width, cam.getSceneryView().getCenter().y - furthestRightBG->getLocalBounds().height / 2);

}

void LayerHandler::moveStationaryForeground(sf::RenderWindow &window, Camera &cam, sf::Vector2f &middleCamCoordPosSceneView, sf::Vector2f &middleCamCoordPosTileView) {
	mForegroundObjects[0].setPosition(cam.getTileView().getCenter().x - 1920, cam.getTileView().getCenter().y + 800);
}

void LayerHandler::moveForeground(sf::Vector2f &velocity){

}

void LayerHandler::renderBackground(sf::RenderWindow &window){
	for (size_t i = 0; i < mBackgrounds.size(); i++){
		window.draw(mBackgrounds[i]);
	}
}

void LayerHandler::renderVertGradiant(sf::RenderWindow &window) {
	window.draw(mAcidGlowVert);
}

void LayerHandler::renderMiddleground(sf::RenderWindow & window){
	for (size_t i = 0; i < mMiddlegrounds.size(); i++) {
		window.draw(mMiddlegrounds[i]);
	}
}

void LayerHandler::renderForeground(sf::RenderWindow &window){
	/*for (size_t i = 0; i < mForegroundObjects.size(); i++) {
		window.draw(mForegroundObjects[i]);
	}*/ //Design, kommenteras bort på alla banor förutom magsäck/strupe
}

void LayerHandler::renderHud(sf::RenderWindow &window){
	for (int i = 0; i < mEntityHandler->getPlayerLife(); i++) {
		window.draw(mLives[i]);
	}
	}

void LayerHandler::updateHud(sf::Vector2f viewCamCoordPos, sf::Vector2f tileCamCoordPos){
	LayerHandler::animate();
	LayerHandler::updateLife();

		
	for (int i = 0; i < mLives.size(); i++){
		mLives[i].setPosition(viewCamCoordPos.x - 1800 + (i * 180), tileCamCoordPos.y + 50);
	}

	// Updates Game Over text
	mTextHandler.updateText(viewCamCoordPos);
}

void LayerHandler::addHorizontalBackground(sf::Texture &backgroundTexture){
	mBackground.setTextureRect(sf::IntRect(0, 0, 1080, 1080));
	mBackground.setTexture(backgroundTexture);

	mBackgrounds[0] = mBackground;
	mBackgrounds[0].setPosition(sf::Vector2f(0.f, 0.f));

	mBackgrounds[1] = mBackground;
	mBackgrounds[1].setPosition(sf::Vector2f(mBackgrounds[0].getPosition().x + mBackgrounds[1].getLocalBounds().width, 0.f));

	mBackgrounds[2] = mBackground;
	mBackgrounds[2].setPosition(sf::Vector2f(mBackgrounds[1].getPosition().x + mBackgrounds[2].getLocalBounds().width, 0.f));
}

void LayerHandler::addVerticalBackground(sf::Texture &backgroundTexture) {
	mBackground.setTextureRect(sf::IntRect(0, 0, 1920, 1080));
	mBackground.setTexture(backgroundTexture);

	mBackgrounds[0] = mBackground;
	mBackgrounds[0].setPosition(sf::Vector2f(0.f, 0.f));

	mBackgrounds[1] = mBackground;
	mBackgrounds[1].setPosition(sf::Vector2f(0.f, mBackgrounds[0].getPosition().y - mBackgrounds[1].getLocalBounds().height));

	mBackgrounds[2] = mBackground;
	mBackgrounds[2].setPosition(sf::Vector2f(0.f, mBackgrounds[1].getPosition().y - mBackgrounds[2].getLocalBounds().height));
}

void LayerHandler::addMiddleground(sf::Texture & middlegroundTexture, std::string orientation){
	mMiddleground.setTexture(middlegroundTexture);
	if (orientation == "Top") {
		mMiddlegrounds[0] = mMiddleground;
		mMiddlegrounds[0].setPosition(sf::Vector2f(0.f, 0.f));

		mMiddlegrounds[1] = mMiddleground;
		mMiddlegrounds[1].setPosition(sf::Vector2f(mMiddlegrounds[0].getPosition().x + mMiddlegrounds[1].getLocalBounds().width, 0.f));

		mMiddlegrounds[2] = mMiddleground;
		mMiddlegrounds[2].setPosition(sf::Vector2f(mMiddlegrounds[1].getPosition().x + mMiddlegrounds[2].getLocalBounds().width, 0.f));
	}
	else if (orientation == "Bottom"){
		mMiddlegrounds[0] = mMiddleground;
		mMiddlegrounds[0].setPosition(sf::Vector2f(0.f, 1080.f - mMiddlegrounds[0].getLocalBounds().height));

		mMiddlegrounds[1] = mMiddleground;
		mMiddlegrounds[1].setPosition(sf::Vector2f(mMiddlegrounds[0].getPosition().x + mMiddlegrounds[1].getLocalBounds().width, 1080.f - mMiddlegrounds[0].getLocalBounds().height));

		mMiddlegrounds[2] = mMiddleground;
		mMiddlegrounds[2].setPosition(sf::Vector2f(mMiddlegrounds[1].getPosition().x + mMiddlegrounds[2].getLocalBounds().width, 1080.f - mMiddlegrounds[0].getLocalBounds().height));
	}

}

void LayerHandler::addForegroundObject(sf::Texture &foregroundTexture) {
	mForeground.setTexture(foregroundTexture);
	mForeground.setScale(4, 1);
	mForegroundObjects.push_back(mForeground);
	mForegroundObjects[0].setPosition(sf::Vector2f(0.f, 10.f));
}

void LayerHandler::addLifeSprite(sf::Sprite &life){
	mLifeSprite = sf::Sprite(life);
	for (int i = 0; i < mMaxLife; i++) {
		mLives.push_back(sf::Sprite(mLifeSprite));
	}
	/*for (int i = 0; i < mLives.size(); i++){
		mLives[i].setTexture(*mHeartAnimation->at(0));
	}*/
}

void LayerHandler::addAcid(sf::Texture &acidTexture) {
	mForeground.setTexture(acidTexture);
	mForeground.setScale(4, 1);
	mForegroundObjects.push_back(mForeground);
	mForegroundObjects[0].setPosition(sf::Vector2f(0.f, 10.f));

}

void LayerHandler::addAcidGradiantVertical(sf::Texture &vertGrad){
	mAcidGlowVert.setTextureRect(sf::IntRect(0, 0, 1920, 1347));
	mAcidGlowVert.setTexture(vertGrad);
	mAcidGlowVert.setPosition(0, 0);
}

void LayerHandler::addAcidGradiantHoriz(sf::Texture & vertGrad){
	mAcidGlowVert.setTextureRect(sf::IntRect(0, 0, 1920, 1080));
	mAcidGlowVert.setTexture(vertGrad);
	mAcidGlowVert.setPosition(0, 0);
}


void LayerHandler::animate(){
	mTimer += ANIFramesPerFrame;
	if (mTimer >= 2){
		mAnimationIndex += 1;
		mTimer = 0;
		if (mAnimationIndex >= mHeartAnimation->size())
			mAnimationIndex = 0;
		if (mHeartAnimation->size() > 0){
			for (int i = 0; i < mLives.size(); i++){
				mLives[i].setTexture(*mHeartAnimation->at(mAnimationIndex));
			}
		}
	}
}

void LayerHandler::updateLife() {

	// Special case for when game is started
	//if (mPreviousLife == -1) {
	//	for (int i = 0; i < 3; i++) {
	//		mLives.push_back(sf::Sprite(mLifeSprite));
	//	}
	//	mPreviousLife = 3;
	//}

	//int currentLife = mEntityHandler->getPlayerLife();

	//// Removes or adds life sprite
	//if (mPreviousLife > currentLife) {
	//	mLives.pop_back();
	//} else if (mPreviousLife < currentLife) {
	//	mLives.push_back(sf::Sprite(mLifeSprite));
	//}

	//mPreviousLife = currentLife;

	//if (currentLife != 0) {
	//	int div = currentLife;
	//	if (div > 4) {
	//		div = 4;
	//	}
	//	ANIFramesPerFrame = 125 / div * Toolbox::getFrameTime();
	//}
}

void LayerHandler::updateVertGlowAlpha(int alpha){
	mAcidGlowVert.setColor(sf::Color(255, 255, 255, alpha));
}

void LayerHandler::clearLife() {
	mLives.clear();
}

void LayerHandler::internalClear() {
}

	//if (mTimerANI >= 1){
	//	mAnimationIndex += 1;
	//	mTimerANI = 0;
	//	if (mAnimationIndex >= mCurrentAnimation->size()){
	//		if (mState == DEATH){
	//			mIsAlive = false;
	//			mAnimationIndex -= 1;
	//		}
	//		else
	//			mAnimationIndex = 0;
	//	}

	//	if (mCurrentAnimation->size() > 0)
	//		mSprite.setTexture(*mCurrentAnimation->at(mAnimationIndex));
	//}
//}

