#include "Stomach.h"

Stomach::Stomach() :
// Initiate singleton classes
mBackground(),
mTexture(),
mTerrainHandler(Terrainhandler::getInstance()),
mEntityHandler(Entityhandler::getInstance()),
mMapGenerator(MapGenerator::getInstance()),
mCollisionHandler(Collisionhandler::getInstance()),
mLayerHandler(LayerHandler::getInstance()),
mTextHandler(Texthandler::getInstance()),
mCamera(),
mMapName("Stomach"),
mMapPath("resources/maps/mMap0.txt"){
	Toolbox::loadTextures(mMapName);
	Toolbox::loadSounds(mMapName);
	Toolbox::loadFonts(mMapName);
	Animations::loadTextures();

	mLifeTexture.loadFromImage(Toolbox::getTexture(Toolbox::LIFETEXTURE));
	mLifeSprite.setTexture(mLifeTexture);
	mLifeSprite.setScale(1.5,1.5);
	mLayerHandler.addLifeSprite(mLifeSprite);

	mBackgroundTexture.loadFromImage(Toolbox::getTexture(Toolbox::STOMACHBACKGROUND));

	mLayerHandler.addBackground(mBackgroundTexture);

	mMapGenerator.loadMap(mMapPath);
	mCamera.zoomOut(0.5f, 1);

}

Stomach::~Stomach(){
}

Stomach& Stomach::getInstance(){
	static Stomach Stomach;
	return Stomach;
}

void Stomach::update(sf::RenderWindow &window, float &frameTime){
	// Specific event loop for gameRun state
	sf::Event gEvent;
	while (window.pollEvent(gEvent)){
		if (gEvent.type == sf::Event::Closed)
			window.close();
	}
	mCamera.updateStomachCam(window, "Standard");
	window.setView(mCamera.getTileView());

	mEntityHandler.updateEntities(frameTime);
	mTerrainHandler.updateTerrains();
	mCollisionHandler.checkCollision(mEntityHandler.getEntities(), mTerrainHandler.getTerrains());
	mEntityHandler.bringOutTheDead();
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))

	sf::Vector2i pixel_pos_tileV = sf::Vector2i(mCamera.getTileView().getCenter().x, 0);
	sf::Vector2f coord_pos_tileV = window.mapPixelToCoords(pixel_pos_tileV);

	window.setView(mCamera.getSceneryView());
	
	sf::Vector2i pixel_pos_sceneV = sf::Vector2i(pixel_pos_tileV.x, 0);
	sf::Vector2f coord_pos_sceneV = window.mapPixelToCoords(pixel_pos_sceneV);

	mLayerHandler.moveBackground(window, mCamera, coord_pos_sceneV, coord_pos_tileV);

	pixel_pos_sceneV = sf::Vector2i(mCamera.getTileView().getCenter().x, mCamera.getTileView().getCenter().y);
	coord_pos_sceneV = window.mapPixelToCoords(pixel_pos_sceneV);

	mLayerHandler.updateHud(coord_pos_sceneV);
	// Funktion som återställer hud(coord_pos)

	window.setView(mCamera.getTileView());
}

void Stomach::render(sf::RenderWindow &window){
	window.clear();
	
	window.setView(mCamera.getSceneryView());
	//mLayerHandler.render(window);
	mLayerHandler.renderBackground(window);
	window.setView(mCamera.getTileView());
	mTerrainHandler.renderTerrains(window);
	mCollisionHandler.renderCollision(window);
	mEntityHandler.renderEntities(window);

	if (!mEntityHandler.isPlayerAlive()) {
		mTextHandler.renderText(window);
	}
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