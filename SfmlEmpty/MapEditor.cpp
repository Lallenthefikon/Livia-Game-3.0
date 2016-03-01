#include "MapEditor.h"
#include <iostream>
#include <fstream>
#include <sstream>

MapEditor::MapEditor(std::string &levelDirectory, std::string &levelName) :
mMapDimensionsTiles(500, 50),
mTileDimensions(100, 100),

mInsertType(MapEditorMeny::BLOCK0),

mRotDirection('t'),
mCurrentLevelDirectory(levelDirectory),

mMaploader(MapEditMaploader::getInstance()),
mMeny(MapEditorMeny::getInstance()),
mTextHandler(Texthandler::getInstance()),
mLayerHandler(LayerHandler::getInstance()),

mCamera(),

mDecorationLayer('b') {

	Toolbox::loadTextures(levelName);
	mTileTexture.loadFromImage(Toolbox::getTexture(Toolbox::TILETEXTURE));
	MapEditor::loadLevel();
	MapEditor::createGrid();
}

MapEditor::~MapEditor(){
}

MapEditor* MapEditor::getInstance(std::string &levelDirectory, std::string &levelName){
	static MapEditor mapeditor(levelDirectory, levelName);
	return &mapeditor;
}

void MapEditor::update(sf::RenderWindow &window){
	// Events
	sf::Event gEvent;
	while (window.pollEvent(gEvent)){

		if (gEvent.type == sf::Event::Closed)
			window.close();

		if (gEvent.type == sf::Event::MouseButtonPressed){
			sf::Vector2i pixel_pos = sf::Mouse::getPosition(window);
			sf::Vector2f coord_pos = window.mapPixelToCoords(pixel_pos);

			if (mMeny.menyClicked(sf::Vector2i(coord_pos))){
				MapEditor::updateInsertType();
			}
			else{
				
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
					for (i = mDecorations.size() - 1; i > -1; i--) {
						if (MapEditor::isSpriteClicked(mDecorations[i]->getSprite(), &coord_pos)) {
							MapEditor::eraseDecoration(i);
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
			sf::Vector2i pixel_pos = window.getPosition();
			sf::Vector2f coord_pos = window.mapPixelToCoords(pixel_pos);
			mMeny.resetMenusPos(coord_pos);
		}

		if (gEvent.type == sf::Event::KeyPressed){
			switch (gEvent.key.code){
			case sf::Keyboard::S:
				MapEditor::saveMap();
				break;
			case sf::Keyboard::Num0:
				MapEditor::changeInsertType();
				break;
			case sf::Keyboard::L:
				MapEditor::changeLayer();
				break;
			case sf::Keyboard::Delete:
				MapEditor::internalClear();
				break;
			case sf::Keyboard::R:
				MapEditor::changeRotDirection();
				break;
			default:
				break;
			}
		}
	}

	// Camera movement & following menu 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
		mCamera.updateCamEDITOR(window, "Up");
		sf::Vector2i pixel_pos = window.getPosition();
		sf::Vector2f coord_pos = window.mapPixelToCoords(pixel_pos);
		mMeny.resetMenusPos(coord_pos);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
		mCamera.updateCamEDITOR(window, "Down");
		sf::Vector2i pixel_pos = window.getPosition();
		sf::Vector2f coord_pos = window.mapPixelToCoords(pixel_pos);
		mMeny.resetMenusPos(coord_pos);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
		mCamera.updateCamEDITOR(window, "Right");
		sf::Vector2i pixel_pos = window.getPosition();
		sf::Vector2f coord_pos = window.mapPixelToCoords(pixel_pos);
		mMeny.resetMenusPos(coord_pos);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
		mCamera.updateCamEDITOR(window, "Left");
		sf::Vector2i pixel_pos = window.getPosition();
		sf::Vector2f coord_pos = window.mapPixelToCoords(pixel_pos);
		mMeny.resetMenusPos(coord_pos);
	}

	window.setView(mCamera.getTileView());

	sf::Vector2f tileViewCoordPos = Toolbox::findCoordPos(sf::Vector2i(mCamera.getTileView().getCenter().x, 0), window);
	mLayerHandler.updateHud(mCamera.getTileView().getCenter(), tileViewCoordPos);
}

void MapEditor::render(sf::RenderWindow &window){
	window.clear();

	for (size_t i = 0; i < mGrid.size(); i++) {
		window.draw(mGrid[i]);
	}

	// Decoration back
	for (Decorations::size_type i = 0; i < mDecorations.size(); i++) {
		if (mDecorations[i]->getDecorationLayer() == Decoration::BACK) {
			mDecorations[i]->render(window);
		}
	}

	// Terrain
	for (Terrains::size_type i = 0; i < mTerrains.size(); i++) {
		mTerrains[i]->render(window);
	}

	// Entities
	for (Entities::size_type i = 0; i < mEntities.size(); i++) {
		mEntities[i]->render(window);
	}

	// Decoration front
	for (Decorations::size_type i = 0; i < mDecorations.size(); i++) {
		if (mDecorations[i]->getDecorationLayer() == Decoration::FRONT) {
			mDecorations[i]->render(window);
		}
	}

	mMeny.render(window);

	displayCurrentLayer(window);

	window.display();
}

void MapEditor::createPlayer(sf::Vector2f mousePos){
	if (mEntities.empty())
		mEntities.push_back(Factory::createPlayer(mousePos));

	else if (mEntities[0]->getType() == Entity::PLAYER){
		delete mEntities[0];
		mEntities[0] = Factory::createPlayer(mousePos);
	}
	else{
		mEntities.push_back(mEntities[0]);
		mEntities[0] = Factory::createPlayer(mousePos);
	}
}

void MapEditor::createBlock0(sf::Vector2f mousePos){
	mTerrains.push_back(Factory::createBlock0(mousePos,'a'));
}

void MapEditor::createWorm(sf::Vector2f mousePos){
	mEntities.push_back(Factory::createWorm(mousePos));
}

void MapEditor::createAcidMonster(sf::Vector2f mousePos){
	mEntities.push_back(Factory::createAcidMonster(mousePos));
}

void MapEditor::createBlock0WallJump(sf::Vector2f mousePos){
	mTerrains.push_back(Factory::createBlock0WallJump(mousePos, 'p'));
}

void MapEditor::createSpikes(sf::Vector2f mousePos){
	mTerrains.push_back(Factory::createSpikes(mousePos, mRotDirection));
}

void MapEditor::createGoal(sf::Vector2f mousepos) {
	mTerrains.push_back(Factory::createGoal(mousepos));
}

void MapEditor::createDecoration(sf::Vector2f mousepos, char id, char layer) {
	mDecorations.push_back(Factory::createDecoration(mousepos, id, layer));
}

void MapEditor::loadLevel(){
	mCurrentLevelDirectory[15] = 'E';
	mEntities = mMaploader.getEntities(mCurrentLevelDirectory);

	mCurrentLevelDirectory[15] = 'T';
	mTerrains = mMaploader.getTerrain(mCurrentLevelDirectory);

	mCurrentLevelDirectory[15] = 'D';
	mDecorations = mMaploader.getDecorations(mCurrentLevelDirectory);

	mCurrentLevelDirectory[15] = 'm';

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
	case MapEditorMeny::ACIDMONSTER:
		MapEditor::createAcidMonster(mousePos);
		break;
	case MapEditorMeny::BLOCK0WALLJUMP:
		MapEditor::createBlock0WallJump(mousePos);
		break;
	case MapEditorMeny::SPIKES:
		MapEditor::createSpikes(mousePos);
		break;
	case MapEditorMeny::BLOCKGOAL:
		MapEditor::createGoal(mousePos);
		break;
	case MapEditorMeny::DECORATION0:
		MapEditor::createDecoration(mousePos, '0', mDecorationLayer);
		break;
	case MapEditorMeny::DECORATION1:
		MapEditor::createDecoration(mousePos, '1', mDecorationLayer);
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

void MapEditor::eraseDecoration(int index) {
	delete mDecorations[index];
	mDecorations.erase(mDecorations.begin() + index);
}

void MapEditor::changeInsertType(){
	switch (mInsertType){
	case MapEditorMeny::ACIDMONSTER:
		mInsertType = MapEditorMeny::PLAYER;
		break;
	case MapEditorMeny::PLAYER:
		mInsertType = MapEditorMeny::WORM;
		break;
	case MapEditorMeny::WORM:
		mInsertType = MapEditorMeny::BLOCK0;
		break;
	case MapEditorMeny::BLOCK0:
		mInsertType = MapEditorMeny::BLOCK0WALLJUMP;
		break;
	case MapEditorMeny::BLOCK0WALLJUMP:
		mInsertType = MapEditorMeny::SPIKES;
		break;
	case MapEditorMeny::SPIKES:
		mInsertType = MapEditorMeny::BLOCKGOAL;
		break;
	case MapEditorMeny::BLOCKGOAL:
		mInsertType = MapEditorMeny::DECORATION0;
		break;
	case MapEditorMeny::DECORATION0:
		mInsertType = MapEditorMeny::DECORATION1;
		break;
	case MapEditorMeny::DECORATION1:
		mInsertType = MapEditorMeny::ACIDMONSTER;
		break;
	default:
		break;
	}
	//std::cout << std::to_string(mInsertType)<< std::endl;
}

void MapEditor::changeRotDirection(){
	switch (mRotDirection){
	case 't':
		mRotDirection = 'r';
		break;
	case 'r':
		mRotDirection = 'b';
		break;
	case 'b':
		mRotDirection = 'l';
		break;
	case 'l':
		mRotDirection = 't';
		break;

	default:
		break;
	}
}

void MapEditor::changeLayer() {
	switch (mDecorationLayer) {
	case 'b':
		mDecorationLayer = 'f';
		break;
	case 'f':
		mDecorationLayer = 'b';
		break;
	default:
		break;
	}
	//std::cout << "'MapEditor' Current layer: " << mDecorationLayer << std::endl;
}

void MapEditor::displayCurrentLayer(sf::RenderWindow & window) {
	std::string textToRender = "Current layer: ";
	mTextHandler.renderText(window, textToRender + layerToString());
}

std::string MapEditor::layerToString() const {
	switch (mDecorationLayer) {
	case 'b':	return "Back";
	case 'f':	return "Front";
	default:	return "Unknown";
	}
}

void MapEditor::saveMap(){

	MapEditor::sortVectors();

	mCurrentLevelDirectory[15] = 'T';
	MapEditor::writeTerrainToFile(mCurrentLevelDirectory);

	mCurrentLevelDirectory[15] = 'E';
	MapEditor::writeEntityToFile(mCurrentLevelDirectory);

	mCurrentLevelDirectory[15] = 'D';
	MapEditor::writeDecorationToFile(mCurrentLevelDirectory);

	mCurrentLevelDirectory[15] = 'm';

}

void MapEditor::sortVectors(){
	// Put acid monster at back
	for (Entities::size_type i = 0; i < mEntities.size(); i++){
		if (mEntities[i]->getType() == Entity::ACIDMONSTER){
			Entity* temp(mEntities[i]);
			mEntities[i] = mEntities.back();
			mEntities.back() = temp;
		}
	}
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

			case Terrain::BLOCK0WALLJUMP:
				output.push_back('B');
				output.push_back('W');
				// Push what type of block it is
				output.push_back(blockType(mTerrains[i]));
				break;

			case Terrain::SPIKES:
				output.push_back('S');
				output.push_back('0');
				// Push what rot is has
				output.push_back(mTerrains[i]->getTileType());
				break;

			case Terrain::BLOCKGOAL:
				output.push_back('G');
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

			case Entity::ACIDMONSTER:
				output.push_back('A');
				output.push_back('C');
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

void MapEditor::writeDecorationToFile(std::string filename) {
	std::string posString;
	std::string output;
	std::ofstream decorationFile(filename);

	if (decorationFile.is_open()) {
		for (Decorations::size_type i = 0; i < mDecorations.size(); i++) {
			output.push_back('D');
			switch (mDecorations[i]->getDecorationID()) {
			case Decoration::FLOWER:
				output.push_back('0');
				break;
			case Decoration::SAYS:
				output.push_back('1');
				break;
			default:
				break;
			}
			switch (mDecorations[i]->getDecorationLayer()) {
			case Decoration::FRONT:
				output.push_back('f');
				break;
			case Decoration::BACK:
				output.push_back('b');
				break;
			default:
				break;
			}
			output.push_back('|');

			// Inserts xpos into output followed by a ','
			posString = MapEditor::floatToString(mDecorations[i]->getPos().x + mDecorations[i]->getOffset().x);
			for (std::string::size_type iS = 0; iS < posString.size(); iS++) {
				output.push_back(posString[iS]);
			}
			output.push_back(',');

			// Inserts ypos into output
			posString = MapEditor::floatToString(mDecorations[i]->getPos().y + mDecorations[i]->getOffset().y);
			for (std::string::size_type iS = 0; iS < posString.size(); iS++) {
				output.push_back(posString[iS]);
			}

			// Writes output into file
			decorationFile << output << std::endl;

			output.clear();
			posString.clear();
		}
	}
	decorationFile.close();
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

	while (!mDecorations.empty()) {
		delete mDecorations.back();
		mDecorations.pop_back();
	}
}

std::string MapEditor::floatToString(float f){
	std::ostringstream ss;
	ss << f;
	std::string pos(ss.str());
	return pos;
}

//std::string MapEditor::spikeFloatToString(Terrain* terrain){
//	switch (terrain->getTileType()){
//	case 't':
//		return MapEditor::floatToString()
//	default:
//		break;
//	}
//}

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