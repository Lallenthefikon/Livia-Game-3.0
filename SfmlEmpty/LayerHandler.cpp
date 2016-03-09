#include "LayerHandler.h"
#include <iostream>

float BACKGROUNDSPEED = 0.07f;
float MIDDLEGROUNDSPEED = BACKGROUNDSPEED * 2;
float FOREGROUNDSPEED;

static float ANIFramesPerFrame(0.25);

LayerHandler::LayerHandler() :
mEntityHandler(Entityhandler::getInstance()),
mTextHandler(Texthandler::getInstance()),
mDialogueHandler(Dialoguehandler::getInstance()),
mHeartAnimation(Animations::getHeartANI()){
	
	//mForegroundObjects.push_back(background);
}

LayerHandler::~LayerHandler(){
	LayerHandler::internalClear();
}

LayerHandler& LayerHandler::getInstance(){
	static LayerHandler layerHandler;
	return layerHandler;
}

void LayerHandler::moveBackground(sf::RenderWindow &window, Camera &cam, sf::Vector2f &middleCamCoordPosSceneView, sf::Vector2f &middleCamCoordPosTileView){

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

	/*if (mEntityHandler->getPlayerLife() == 3){
		window.draw(mLives[0]);
		window.draw(mLives[1]);
		window.draw(mLives[2]);
		ANIFramesPerFrame = 31.25 * Toolbox::getFrameTime();
	}

	else if (mEntityHandler->getPlayerLife() == 2){
		window.draw(mLives[0]);
		window.draw(mLives[1]);
		ANIFramesPerFrame = 62.5 * Toolbox::getFrameTime();
	}

	else if (mEntityHandler->getPlayerLife() == 1){
		window.draw(mLives[0]);
		ANIFramesPerFrame = 125 * Toolbox::getFrameTime();
	}*/

	for (int i = 0; i < mEntityHandler->getPlayerLife(); i++) {
		window.draw(mLives[i]);
	}

	int div;
	if (mEntityHandler->getPlayerLife() != 0) {
		div = mEntityHandler->getPlayerLife();
		if (div > 3) {
			div = 3;
		}
		ANIFramesPerFrame = 125 / div * Toolbox::getFrameTime();
	}

	if (mDialogueHandler.isInDialogue){
		mDialogueHandler.renderDialogue(window);
		
	}
}

void LayerHandler::updateHud(sf::Vector2f viewCamCoordPos, sf::Vector2f tileCamCoordPos){
	updateLife();
	for (int i = 0; i < mLives.size(); i++){
		mLives[i].setPosition(viewCamCoordPos.x - 1700 + (i * 180), tileCamCoordPos.y + 50);
	}

	LayerHandler::animate();

	// Updates Game Over text
	mTextHandler.updateText(viewCamCoordPos);
}

void LayerHandler::addBackground(sf::Texture &backgroundTexture){

	mBackground.setTexture(backgroundTexture);
	mBackgrounds.push_back(mBackground);
	mBackgrounds[0].setPosition(sf::Vector2f(0.f, 0.f));
	mBackgrounds.push_back(mBackground);
	mBackgrounds[1].setPosition(sf::Vector2f(mBackgrounds[0].getPosition().x + mBackgrounds[1].getLocalBounds().width, 0.f));
	mBackgrounds.push_back(mBackground);
	mBackgrounds[2].setPosition(sf::Vector2f(mBackgrounds[1].getPosition().x + mBackgrounds[2].getLocalBounds().width, 0.f));
}

void LayerHandler::addMiddleground(sf::Texture & middlegroundTexture){

	mMiddleground.setTexture(middlegroundTexture);
	mMiddlegrounds.push_back(mMiddleground);
	mMiddlegrounds[0].setPosition(sf::Vector2f(0.f, 0.f));
	mMiddlegrounds.push_back(mMiddleground);
	mMiddlegrounds[1].setPosition(sf::Vector2f(mMiddlegrounds[0].getPosition().x + mMiddlegrounds[1].getLocalBounds().width, 0.f));
	mMiddlegrounds.push_back(mMiddleground);
	mMiddlegrounds[2].setPosition(sf::Vector2f(mMiddlegrounds[1].getPosition().x + mMiddlegrounds[2].getLocalBounds().width, 0.f));
}

void LayerHandler::addForegroundObject(sf::Texture &foregroundTexture) {

	mForeground.setTexture(foregroundTexture);
	mForeground.setScale(4, 1);
	mForegroundObjects.push_back(mForeground);
	mForegroundObjects[0].setPosition(sf::Vector2f(0.f, 10.f));
}

void LayerHandler::addLifeSprite(sf::Sprite &life){
	mLifeSprite = sf::Sprite(life);

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
	for (int i = 0; i < mEntityHandler->getPlayerLife(); i++) {
		mLives.push_back(sf::Sprite(mLifeSprite));
	}
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

