#include "MapEditor.h"
#include <iostream>
#include <fstream>
#include <sstream>

MapEditor::MapEditor(std::string &mapName) :
mMapDimensionsTiles(500, 50),
mTileDimensions(120, 120),
mInsertType(MapEditorMeny::BLOCK0),
mCurrentMap(mapName),
mMaploader(MapEditMaploader::getInstance()),
mMeny(MapEditorMeny::getInstance()),
mCamera(){

	Toolbox::loadTextures();
	mTileTexture.loadFromImage(Toolbox::getTexture(Toolbox::TILETEXTURE));
	MapEditor::loadMap();
	MapEditor::createGrid();
}

MapEditor::~MapEditor(){
}

MapEditor* MapEditor::getInstance(std::string &mapName){
	static MapEditor mapeditor(mapName);
	return &mapeditor;
}

void MapEditor::update(sf::RenderWindow &window){
	// Events
	sf::Event gEvent;
	while (window.pollEvent(gEvent)){

		if (gEvent.type == sf::Event::Closed)
			window.close();

		if (gEvent.type == sf::Event::MouseButtonPressed){


			if (mMeny.menyClicked(sf::Mouse::getPosition(window))){
				MapEditor::updateInsertType();
			}

			else{
				sf::Vector2i pixel_pos = sf::Mouse::getPosition(window);
				sf::Vector2f coord_pos = window.mapPixelToCoords(pixel_pos);
				int i;

				sf::Sprite clickedTile;
				switch (gEvent.mouseButton.button){

				case sf::Mouse::Left:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
						MapEditor::insertObject(sf::Vector2f(coord_pos.x, coord_pos.y));
					}
					else{
						sf::Vector2i pixel_pos = sf::Mouse::getPosition(window);
						sf::Vector2f coord_pos = window.mapPixelToCoords(pixel_pos);
						clickedTile = determineSelectedTileInGrid(coord_pos, &mGrid);
						// Offset applied in all tiles, counteroffset needed here to match grid.
						MapEditor::insertObject(sf::Vector2f(
							clickedTile.getPosition().x + clickedTile.getLocalBounds().width / 2
							, clickedTile.getPosition().y + clickedTile.getLocalBounds().height / 2));
					}
					break;


				case sf::Mouse::Right:
					for (i = mEntities.size() - 1; i > -1; i--){
						if (MapEditor::isSpriteClicked(mEntities[i]->getSprite(), &coord_pos)){
							MapEditor::eraseEntity(i);
							break;
						}
					}
					for (i = mTerrains.size() - 1; i > -1; i--){
						if (MapEditor::isSpriteClicked(mTerrains[i]->getSprite(), &coord_pos)){
							MapEditor::eraseTerrain(i);
							break;
						}
					}
					break;

				case sf::Mouse::Middle:
					MapEditor::changeInsertType();
					break;

				default:
					break;
				}
			}
		}
		if (gEvent.type == sf::Event::MouseWheelMoved){
			mCamera.zoomCameraEDITOR(gEvent);
		}

		if (gEvent.type == sf::Event::KeyPressed){
			switch (gEvent.key.code){
			case sf::Keyboard::S:

				MapEditor::saveMap();
				break;
			case sf::Keyboard::Delete:
				MapEditor::internalClear();
				break;
			default:
				break;
			}
		}
	}

	// Camera movement
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		mCamera.updateCamEDITOR(window, "Up");
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		mCamera.updateCamEDITOR(window, "Down");
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		mCamera.updateCamEDITOR(window, "Right");
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		mCamera.updateCamEDITOR(window, "Left");

	window.setView(mCamera.getView());
}

void MapEditor::render(sf::RenderWindow &window){
	window.clear();

	for (size_t i = 0; i < mGrid.size(); i++){
		window.draw(mGrid[i]);
	}

	for (Terrains::size_type i = 0; i < mTerrains.size(); i++){
		mTerrains[i]->render(window);
	}

	for (Entities::size_type i = 0; i < mEntities.size(); i++){
		mEntities[i]->render(window);
	}
	mMeny.render(window);

	window.display();
}

void MapEditor::createBlock0(sf::Vector2f mousePos){
	mTerrains.push_back(Factory::createBlock0(mousePos,'a'));
}

void MapEditor::createPlayer(sf::Vector2f mousePos){
	if (mEntities.empty())
		Factory::createPlayer(mousePos);

	else if (mEntities[0]->getType() == Entity::PLAYER){
		delete mEntities[0];
		mEntities[0] = Factory::createPlayer(mousePos);
	}
	else{
		mEntities.push_back(mEntities[0]);
		mEntities[0] = Factory::createPlayer(mousePos);
	}
}

void MapEditor::createWorm(sf::Vector2f mousePos){
	mEntities.push_back(Factory::createWorm(mousePos));
}

void MapEditor::loadMap(){
	mCurrentMap[15] = 'E';
	mEntities = mMaploader.getEntities(mCurrentMap);

	mCurrentMap[15] = 'T';
	mTerrains = mMaploader.getTerrain(mCurrentMap);

	mCurrentMap[15] = 'm';

	mMaploader.clear();
}

void MapEditor::clearMap(){
	MapEditor::internalClear();
}


// Privates

void MapEditor::insertObject(sf::Vector2f mousePos) {
	switch (mInsertType){
	case MapEditorMeny::BLOCK0:
		MapEditor::createBlock0(mousePos);
		break;
	case MapEditorMeny::PLAYER:
		MapEditor::createPlayer(mousePos);
		break;
	case MapEditorMeny::WORM:
		MapEditor::createWorm(mousePos);
		break;
	default:
		break;
	}
}

void MapEditor::eraseEntity(int index){
	delete mEntities[index];
	mEntities.erase(mEntities.begin() + index);
}

void MapEditor::eraseTerrain(int index){
	delete mTerrains[index];
	mTerrains.erase(mTerrains.begin() + index);
}

void MapEditor::changeInsertType(){
	switch (mInsertType){
	case MapEditorMeny::BLOCK0:
		mInsertType = MapEditorMeny::PLAYER;
		break;
	case MapEditorMeny::PLAYER:
		mInsertType = MapEditorMeny::WORM;
		break;
	case MapEditorMeny::WORM:
		mInsertType = MapEditorMeny::BLOCK0;
		break;
	default:
		break;
	}
}

void MapEditor::saveMap(){

	mCurrentMap[15] = 'T';
	MapEditor::writeTerrainToFile(mCurrentMap);

	mCurrentMap[15] = 'E';
	MapEditor::writeEntityToFile(mCurrentMap);

	mCurrentMap[15] = 'm';

}

void MapEditor::writeTerrainToFile(std::string filename){

	std::string posString;
	std::string output;
	std::ofstream terrainfile(filename);

	if (terrainfile.is_open()){
		for (Terrains::size_type i = 0; i < mTerrains.size(); i++){
			terrainfile << std::endl;
			
			// Inserts typename into output followed by '-'
			switch (mTerrains[i]->getType()){
			case Terrain::BLOCK0:
				output.push_back('B');
				output.push_back('0');
				// Push what type of block it is
				output.push_back(blockType(mTerrains[i]));
				break;

			default:
				break;

			}
			output.push_back('|');

			// Inserts xpos into output followed by a ','
			posString = MapEditor::floatToString(mTerrains[i]->getPos().x + mTerrains[i]->getOffset().x);
			for (std::string::size_type iS = 0; iS < posString.size(); iS++){
				output.push_back(posString[iS]);
			}
			output.push_back(',');

			// Inserts ypos into output
			posString = MapEditor::floatToString(mTerrains[i]->getPos().y + mTerrains[i]->getOffset().y);
			for (std::string::size_type iS = 0; iS < posString.size(); iS++){
				output.push_back(posString[iS]);
			}

			// Writes output into file
			terrainfile << output;
			//

			output.clear();
			posString.clear();
		}
	}
	terrainfile.close();
}

void MapEditor::writeEntityToFile(std::string filename){

	std::string posString;
	std::string output;
	std::ofstream entityFile(filename);

	if (entityFile.is_open()){
		for (Entities::size_type i = 0; i < mEntities.size(); i++){

			// Inserts typename into output followed by '-'
			switch (mEntities[i]->getType()){
			case Entity::PLAYER:
				output.push_back('P');
				output.push_back('0');
				break;

			case Entity::WORM:
				output.push_back('W');
				output.push_back('0');
				break;

			default:
				break;
			}
			output.push_back('|');

			// Inserts xpos into output followed by a ','
			posString = MapEditor::floatToString(mEntities[i]->getPos().x + mEntities[i]->getOffset().x);
			for (std::string::size_type iS = 0; iS < posString.size(); iS++){
				output.push_back(posString[iS]);
			}
			output.push_back(',');

			// Inserts ypos into output
			posString = MapEditor::floatToString(mEntities[i]->getPos().y + mEntities[i]->getOffset().y);
			for (std::string::size_type iS = 0; iS < posString.size(); iS++){
				output.push_back(posString[iS]);
			}

			// Writes output into file
			entityFile << output << std::endl;
			//

			output.clear();
			posString.clear();
		}
	}
	entityFile.close();
}

char MapEditor::blockType(Terrain* terrain){

	bool leftOccupied(false);
	bool rightOccupied(false);
	bool topOccupied(false);
	bool botOccupied(false);

	sf::Vector2f thisPos(terrain->getPos());

	Terrains relevantTerrains;
	for (Terrains::size_type i = 0; i < mTerrains.size(); i++){
		if (mTerrains[i]->getPos().x < thisPos.x + 200 && mTerrains[i]->getPos().x > thisPos.x - 200)
			relevantTerrains.push_back(mTerrains[i]);
	}

	// Check left side
	sf::Vector2f leftBorder(thisPos.x - 1, 
		thisPos.y + (terrain->getHeight()/ 2));
	sf::Vector2f rightBorder(thisPos.x + terrain->getWidth() + 1, 
		thisPos.y + (terrain->getHeight() / 2));
	sf::Vector2f topBorder(thisPos.x + (terrain->getWidth() / 2), 
		thisPos.y - 1);
	sf::Vector2f botBorder(thisPos.x + (terrain->getWidth() / 2), 
		thisPos.y + (terrain->getHeight() + 1));

	for (Terrains::size_type i = 0; i < relevantTerrains.size(); i++){
		if (MapEditor::isSpriteClicked(relevantTerrains[i]->getSprite(), &leftBorder))
			leftOccupied = true;
		if (MapEditor::isSpriteClicked(relevantTerrains[i]->getSprite(), &rightBorder))
			rightOccupied = true;
		if (MapEditor::isSpriteClicked(relevantTerrains[i]->getSprite(), &topBorder))
			topOccupied = true;
		if (MapEditor::isSpriteClicked(relevantTerrains[i]->getSprite(), &botBorder))
			botOccupied = true;
	}

	if (leftOccupied && rightOccupied && topOccupied && botOccupied)
		return 'a';
	if (leftOccupied && rightOccupied && topOccupied && !botOccupied)
		return 'b';
	if (leftOccupied && rightOccupied && !topOccupied && botOccupied)
		return 'c';
	if (leftOccupied && !rightOccupied && topOccupied && botOccupied)
		return 'd';
	if (!leftOccupied && rightOccupied && topOccupied && botOccupied)
		return 'e';
	if (leftOccupied && rightOccupied && !topOccupied && !botOccupied)
		return 'f';
	if (leftOccupied && !rightOccupied && topOccupied && !botOccupied)
		return 'g';
	if (!leftOccupied && rightOccupied && topOccupied && !botOccupied)
		return 'h';
	if (leftOccupied && !rightOccupied && !topOccupied && botOccupied)
		return 'i';
	if (!leftOccupied && rightOccupied && !topOccupied && botOccupied)
		return 'j';
	if (!leftOccupied && !rightOccupied && topOccupied && botOccupied)
		return 'k';
	if (leftOccupied && !rightOccupied && !topOccupied && !botOccupied)
		return 'l';
	if (!leftOccupied && rightOccupied && !topOccupied && !botOccupied)
		return 'm';
	if (!leftOccupied && !rightOccupied && topOccupied && !botOccupied)
		return 'n';
	if (!leftOccupied && !rightOccupied && !topOccupied && botOccupied)
		return 'o';
	if (!leftOccupied && !rightOccupied && !topOccupied && !botOccupied)
		return 'p';
	return '0';
}
	
void MapEditor::internalClear(){
	while (!mEntities.empty()){
		delete mEntities.back();
		mEntities.pop_back();
	}

	while (!mTerrains.empty()){
		delete mTerrains.back();
		mTerrains.pop_back();
	}
}

std::string MapEditor::floatToString(float f){
	std::ostringstream ss;
	ss << f;
	std::string pos(ss.str());
	return pos;
}

void MapEditor::createGrid(){
	sf::Vector2f lastTilePos(-mTileDimensions.x, -mTileDimensions.y);
	//std::vector<sf::Sprite> tiles;

	for (size_t i = 0; i < mMapDimensionsTiles.x; i++){
		sf::Vector2f tilePos(0, 0);
		tilePos.x = lastTilePos.x;
		tilePos.x += mTileDimensions.x;

		sf::Sprite xTile;
		xTile.setTexture(mTileTexture);
		xTile.setPosition(tilePos);

		mGrid.push_back(xTile);
		//std::cout << "X: " << xTile.getPosition().x << std::endl << "Y: " << xTile.getPosition().y << std::endl << std::endl;

		for (size_t j = 0; j < mMapDimensionsTiles.y - 1; j++){
			tilePos.y += mTileDimensions.y;

			sf::Sprite yTile;
			yTile.setTexture(mTileTexture);
			yTile.setPosition(tilePos);
			mGrid.push_back(yTile);

			lastTilePos = tilePos;
			//std::cout << "X: " << yTile.getPosition().x << std::endl << "Y: " << yTile.getPosition().y << std::endl << std::endl;
		}
		lastTilePos.y = 0;
		lastTilePos.x = tilePos.x;
	}
	std::cout << "Tiles created: " << mGrid.size() << std::endl;
}


sf::Sprite MapEditor::determineSelectedTileInGrid(sf::Vector2f position, std::vector<sf::Sprite> *grid){
	for (size_t i = 0; i < grid->size(); i++){
		if (isSpriteClicked(grid->at(i), &position)){
			return grid->at(i);
		}
	}
	return grid->at(0);
}


bool MapEditor::isSpriteClicked(sf::Sprite& spr, sf::Vector2f *mousePos){
	return mousePos->x > spr.getPosition().x
		&& mousePos->x < spr.getPosition().x + spr.getLocalBounds().width
		&& mousePos->y > spr.getPosition().y
		&& mousePos->y < spr.getPosition().y + spr.getLocalBounds().height;
}

void MapEditor::updateInsertType(){
	mInsertType = mMeny.getInsertType();
}

