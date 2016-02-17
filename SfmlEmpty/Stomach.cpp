#include "Stomach.h"

Stomach::Stomach() :
// Initiate singleton classes
mBackground(),
mTerrainHandler(Terrainhandler::getInstance()),
mEntityHandler(Entityhandler::getInstance()),
mMapGenerator(MapGenerator::getInstance()),
mCollisionHandler(Collisionhandler::getInstance()),
mLayerHandler(LayerHandler::getInstance()),
mCamera(),
mMapName("Stomach"),
mMapPath("resources/maps/mMap0.txt"){
	Toolbox::loadTextures(mMapName);
	Toolbox::loadSounds(mMapName);
	Animations::loadTextures();

	mLifeTexture.loadFromImage(Toolbox::getTexture(Toolbox::LIFETEXTURE));
	mLifeSprite.setTexture(mLifeTexture);
	mLayerHandler.addLifeSprite(mLifeSprite);

	mBackgroundTexture.loadFromImage(Toolbox::getTexture(Toolbox::INTESTINEBACKGROUND));
	mBackgroundSprite.setTexture(mBackgroundTexture);
	
	mLayerHandler.addBackground(mBackgroundSprite);
	mMapGenerator.loadMap(mMapPath);
	mCamera.zoomOut(0.5f, 1);
}

Stomach::~Stomach(){
}

Stomach& Stomach::getInstance(){
	static Stomach Stomach;
	return Stomach;
}

void Stomach::update(sf::RenderWindow &window){
	// Specific event loop for gameRun state
	sf::Event gEvent;
	while (window.pollEvent(gEvent)){
		if (gEvent.type == sf::Event::Closed)
			window.close();
	}
	mCamera.updateStomachCam(window, "Standard");
	window.setView(mCamera.getTileView());

	mEntityHandler.updateEntities();
	mTerrainHandler.updateTerrains();
	mCollisionHandler.checkCollision(mEntityHandler.getEntities(), mTerrainHandler.getTerrains());
	mEntityHandler.bringOutTheDead();
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))

	sf::Vector2i pixel_pos = sf::Vector2i(mCamera.getTileView().getCenter().x, 0);
	sf::Vector2f coord_pos = window.mapPixelToCoords(pixel_pos);

	mLayerHandler.moveBackground(pixel_pos, coord_pos);

	pixel_pos = sf::Vector2i(mCamera.getView().getCenter().x, mCamera.getView().getCenter().y);
	coord_pos = window.mapPixelToCoords(pixel_pos);

	mLayerHandler.updateHud(coord_pos);
	// Funktion som återställer hud(coord_pos)

	window.setView(mCamera.getView());
}

void Stomach::render(sf::RenderWindow &window){
	window.clear();
	mLayerHandler.renderBackground(window);
	window.setView(mCamera.getTileView());
	mTerrainHandler.renderTerrains(window);
	mCollisionHandler.renderCollision(window);
	mEntityHandler.renderEntities(window);
	mLayerHandler.renderHud(window);

	window.display();
}

void Stomach::loadLevel(){
	Toolbox::loadTextures(mMapName);
	mMapGenerator.loadMap(mMapPath);
}

void Stomach::unloadLevel(){
	//Toolbox::unloadTextures(mMapName);
}

void Stomach::setCurrentMap(std::string &mapname){
}