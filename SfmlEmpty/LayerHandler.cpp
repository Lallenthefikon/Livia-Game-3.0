#include "LayerHandler.h"


LayerHandler::LayerHandler() :
mBackground(){
	//mForegroundObjects.push_back(background);
}

LayerHandler::~LayerHandler(){
}

LayerHandler& LayerHandler::getInstance(){
	static LayerHandler layerHandler;
	return layerHandler;
}
void moveBackground(sf::Vector2f &velocity){

}

void moveForeground(sf::Vector2f &velocity){

}

void addForegroundObject(sf::Sprite &foregroundSprite){
	
}

void LayerHandler::render(sf::RenderWindow &window){

}

void LayerHandler::setBackground(sf::Sprite &background){
	mBackground = background;
}



