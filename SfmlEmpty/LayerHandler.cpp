#include "LayerHandler.h"
float BACKGROUNDSPEED = 0.5f;
float FOREGROUNDSPEED;


LayerHandler::LayerHandler(){
	
	//mForegroundObjects.push_back(background);
}

LayerHandler::~LayerHandler(){
}

LayerHandler& LayerHandler::getInstance(){
	static LayerHandler layerHandler;
	return layerHandler;
}
void LayerHandler::moveBackground(sf::Vector2i &pixelPos, sf::Vector2f &coordPos){

	sf::Sprite furthestRightBG;
	// Find the background furtest to the right
	if ((mBackgrounds[0].getPosition().x > mBackgrounds[1].getPosition().x)
		&& (mBackgrounds[0].getPosition().x > mBackgrounds[2].getPosition().x)){
		furthestRightBG = mBackgrounds[0];
	}
	else if ((mBackgrounds[1].getPosition().x > mBackgrounds[0].getPosition().x)
		&& (mBackgrounds[1].getPosition().x > mBackgrounds[2].getPosition().x)){
		furthestRightBG = mBackgrounds[1];
	}
	else{
		furthestRightBG = mBackgrounds[2];
	}
	// Move backgrounds left, pop to the right when exit screen
	for (size_t i = 0; i < mBackgrounds.size(); i++){
		if (mBackgrounds[i].getPosition().x < coordPos.x){
			//mBackgrounds[i].setPosition(sf::Vector2f(coordPos.x/2, coordPos.y));
			mBackgrounds[i].setPosition(sf::Vector2f(coordPos.x - std::abs(mBackgrounds[i].getPosition().x - coordPos.x), coordPos.y));
		}
		else{
			mBackgrounds[i].setPosition(sf::Vector2f(furthestRightBG.getPosition().x + mBackgrounds[i].getLocalBounds().width, coordPos.y));
		}
	}
}

void LayerHandler::moveForeground(sf::Vector2f &velocity){

}

void LayerHandler::addForegroundObject(sf::Sprite &foregroundSprite){
	
}

void LayerHandler::render(sf::RenderWindow &window){
	
	for (size_t i = 0; i < mBackgrounds.size(); i++){
		window.draw(mBackgrounds[i]);
	}
}

void LayerHandler::addBackground(sf::Sprite &background){
	mBackgrounds.push_back(background);
	mBackgrounds[0].setPosition(sf::Vector2f(0.f, 0.f));
	mBackgrounds.push_back(background);
	mBackgrounds[1].setPosition(sf::Vector2f(mBackgrounds[0].getPosition().x - mBackgrounds[1].getLocalBounds().width, 0.f));
	mBackgrounds.push_back(background);
	mBackgrounds[2].setPosition(sf::Vector2f(mBackgrounds[1].getPosition().x - mBackgrounds[2].getLocalBounds().width, 0.f));
}

