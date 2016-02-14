#include "LayerHandler.h"


LayerHandler::LayerHandler(sf::Sprite &background) :
mBackground(background){
	//mForegroundObjects.push_back(background);
}

LayerHandler::~LayerHandler(){
}

LayerHandler& LayerHandler::getInstance(sf::Sprite &background){
	static LayerHandler layerHandler(background);
	return layerHandler;
}
void moveBackground(sf::Vector2f &velocity){

}

void moveForeground(sf::Vector2f &velocity){

}

void addForegroundObject(sf::Sprite &foregroundSprite){
	
}

void render(sf::Window &window){

}