#include "Intestine.h"

Intestine::Intestine() :
// Initiate singleton classes
mBackground(),
mTerrainHandler(Terrainhandler::getInstance()),
mEntityHandler(Entityhandler::getInstance()),
mMapGenerator(MapGenerator::getInstance()),
mCollisionHandler(Collisionhandler::getInstance()),
mLayerHandler(LayerHandler::getInstance()),
mCamera(),
mMapName("Intestine"),
mMapPath("resources/maps/mMap0.txt"){
	Toolbox::loadTextures("Intestine");
	Animations::loadTextures();

	mLifeTexture.loadFromImage(Toolbox::getTexture(Toolbox::LIFETEXTURE));
	mLifeSprite.setTexture(mLifeTexture);
	mLayerHandler.addLifeSprite(mLifeSprite);

	mBackgroundTexture.loadFromImage(Toolbox::getTexture(Toolbox::INTESTINEBACKGROUND));
	mBackgroundSprite.setTexture(mBackgroundTexture);
	
	mLayerHandler.addBackground(mBackgroundSprite);
	mMapGenerator.loadMap(mMapPath);
}

Intestine::~Intestine(){
}

Intestine& Intestine::getInstance(){
	static Intestine intestine;
	return intestine;
}

void Intestine::update(sf::RenderWindow &window){
	// Specific event loop for gameRun state
	sf::Event gEvent;
	while (window.pollEvent(gEvent)){
		if (gEvent.type == sf::Event::Closed)
			window.close();
	}

	mEntityHandler.updateEntities();
	mTerrainHandler.updateTerrains();
	mCollisionHandler.checkCollision(mEntityHandler.getEntities(), mTerrainHandler.getTerrains());
	mEntityHandler.bringOutTheDead();
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	mCamera.updateIntestineCam(window, "Standard");

	sf::Vector2i pixel_pos = sf::Vector2i(mCamera.getView().getCenter().x, 0);
	sf::Vector2f coord_pos = window.mapPixelToCoords(pixel_pos);

	mLayerHandler.moveBackground(pixel_pos, coord_pos);

	pixel_pos = sf::Vector2i(mCamera.getView().getCenter().x, mCamera.getView().getCenter().y);
	coord_pos = window.mapPixelToCoords(pixel_pos);

	mLayerHandler.updateHud(coord_pos);
	// Funktion som återställer hud(coord_pos)

	window.setView(mCamera.getView());
}

void Intestine::render(sf::RenderWindow &window){
	window.clear();
	mLayerHandler.renderBackground(window);
	mTerrainHandler.renderTerrains(window);
	mCollisionHandler.renderCollision(window);
	mEntityHandler.renderEntities(window);
	mLayerHandler.renderHud(window);

	window.display();
}

void Intestine::loadLevel(){
	Toolbox::loadTextures(mMapName);
	mMapGenerator.loadMap(mMapPath);
}

void Intestine::unloadLevel(){
	//Toolbox::unloadTextures(mMapName);
}

void Intestine::setCurrentMap(std::string &mapname){
}