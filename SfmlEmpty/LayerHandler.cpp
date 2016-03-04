#include "LayerHandler.h"
#include <iostream>

float BACKGROUNDSPEED = 0.5f;
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
	else 	if ((furthestLeftBG == &mBackgrounds[0] && furthestRightBG == &mBackgrounds[2])
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
	
	// if furthest left outside screen furthest left placed on right
	if (furthestLeftBG->getPosition().x < -furthestLeftBG->getLocalBounds().width){
		furthestLeftBG->setPosition(furthestRightBG->getPosition().x + furthestLeftBG->getLocalBounds().width, 0);
	}
	// if furthest right outside screen furthest right placed on left
	/*if (furthestRightBG->getPosition().x > 1080){
		furthestRightBG->setPosition(furthestLeftBG->getPosition().x - 1080, 0);
	}*/
	float bgSpeed = 0.07;

	furthestRightBG->move(-cam.getVelocity().x * bgSpeed, 0.f);
	middleBG->move(-cam.getVelocity().x * bgSpeed, 0.f);
	furthestLeftBG->move(-cam.getVelocity().x * bgSpeed, 0.f);
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

void LayerHandler::addForegroundObject(sf::Sprite &foregroundSprite){
	
}

void LayerHandler::renderBackground(sf::RenderWindow &window){

	for (size_t i = 0; i < mBackgrounds.size(); i++){
		window.draw(mBackgrounds[i]);
	}
}

void LayerHandler::renderForeground(sf::RenderWindow &window){
	for (size_t i = 0; i < mForegroundObjects.size(); i++) {
		window.draw(mForegroundObjects[i]);
	}
}

void LayerHandler::renderHud(sf::RenderWindow &window){

	if (mEntityHandler.getPlayerLife() == 3){
		window.draw(mLives[0]);
		window.draw(mLives[1]);
		window.draw(mLives[2]);
		ANIFramesPerFrame = 31.25 * Toolbox::getFrameTime();
	}

	else if (mEntityHandler.getPlayerLife() == 2){
		window.draw(mLives[0]);
		window.draw(mLives[1]);
		ANIFramesPerFrame = 62.5 * Toolbox::getFrameTime();
	}

	else if (mEntityHandler.getPlayerLife() == 1){
		window.draw(mLives[0]);
		ANIFramesPerFrame = 125 * Toolbox::getFrameTime();
	}

	if (mDialogueHandler.isInDialogue){
		mDialogueHandler.renderDialogue(window);
		
	}
}

void LayerHandler::updateHud(sf::Vector2f viewCamCoordPos, sf::Vector2f tileCamCoordPos){
	for (int i = 0; i < mLives.size(); i++){
		mLives[i].setPosition(viewCamCoordPos.x - 1700 + (i * 180), tileCamCoordPos.y + 50);

	}

	LayerHandler::animate();

	// Updates Game Over text
	mTextHandler.updateText(viewCamCoordPos);
}

void LayerHandler::addBackground(sf::Texture &backgroundTexture){
	mBackground1.setTexture(backgroundTexture);
	mBackgrounds.push_back(mBackground1);
	mBackgrounds[0].setPosition(sf::Vector2f(0.f, 0.f));
	mBackground2.setTexture(backgroundTexture);
	mBackgrounds.push_back(mBackground2);
	mBackgrounds[1].setPosition(sf::Vector2f(mBackgrounds[0].getPosition().x + mBackgrounds[1].getLocalBounds().width, 0.f));
	mBackground3.setTexture(backgroundTexture);
	mBackgrounds.push_back(mBackground3);
	mBackgrounds[2].setPosition(sf::Vector2f(mBackgrounds[1].getPosition().x + mBackgrounds[2].getLocalBounds().width, 0.f));
}

void LayerHandler::addLifeSprite(sf::Sprite &life){
	mLives.push_back(life);
	mLives.push_back(life);
	mLives.push_back(life);

	for (int i = 0; i < mLives.size(); i++){
		mLives[i].setTexture(*mHeartAnimation->at(0));
	}
}

void LayerHandler::addAcid(sf::Texture &acidTexture) {
	mForeground1.setTexture(acidTexture);
	mForeground1.setScale(4, 1);
	mForegroundObjects.push_back(mForeground1);
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

