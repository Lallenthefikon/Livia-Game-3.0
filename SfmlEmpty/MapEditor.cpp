#include "MapEditor.h"
#include <iostream>
#include <fstream>
#include <sstream>

MapEditor::MapEditor(std::string &levelDirectory, std::string &levelName) :
mMapDimensionsTiles(1000, 50), //Design, 250/350 för tarm, 50/500 för magsäck, 500/50 för strupe
mTileDimensions(100, 100),

mInsertType(MapEditorMeny::BLOCK0),
mEventType('a'),

mEventSize(100,100),

mRotDirection('t'),
mCurrentLevelDirectory(levelDirectory),

mMaploader(MapEditMaploader::getInstance()),
mMeny(MapEditorMeny::getInstance()),
mTextHandler(Texthandler::getInstance()),
mLayerHandler(LayerHandler::getInstance()),
mDialogueHandler(Dialoguehandler::getInstance()),

mCamera(),

mDecorationLayer('b'),

mAirHorn(Toolbox::getSound(Toolbox::WORMIDLE)) {

	Toolbox::loadTextures(levelName);
	mTileTexture.loadFromImage(Toolbox::getTexture(Toolbox::TILETEXTURE));
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
				std::cout << "Saved..." << std::endl;
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
			case sf::Keyboard::E:
				MapEditor::changeEventType();
				break;
			case sf::Keyboard::P:
				mEventSize.y += 30;
				break;
			case sf::Keyboard::O:
				mEventSize.y -= 30;
				break;
			case sf::Keyboard::I:
				mEventSize.x += 30;
				break;
			case sf::Keyboard::U:
				mEventSize.x -= 30;
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

	// Grid
	for (size_t i = 0; i < mGrid.size(); i++) {
		window.draw(mGrid[i]);
	}

	// Decoration back
	for (Decorations::size_type i = 0; i < mDecorations.size(); i++) {
		if (mDecorations[i]->getDecorationLayer() == Decoration::BACK)
			mDecorations[i]->render(window);
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
		if (mDecorations[i]->getDecorationLayer() == Decoration::FRONT)
			mDecorations[i]->render(window);
	}


	mMeny.render(window);

	displayCurrentLayer(window);

	window.display();
}

// Entities
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

void MapEditor::createWorm(sf::Vector2f mousePos){
	mEntities.push_back(Factory::createWorm(mousePos));
}

void MapEditor::createGerm(sf::Vector2f mousePos) {
	mEntities.push_back(Factory::createGerm(mousePos));
}

void MapEditor::createAcidMonster(sf::Vector2f mousePos){
	mEntities.push_back(Factory::createAcidMonster(mousePos));
}

void MapEditor::createMeatball(sf::Vector2f mousePos) {
	mEntities.push_back(Factory::createMeatball(mousePos));
}

void MapEditor::createExtraLife(sf::Vector2f mousePos) {
	mEntities.push_back(Factory::createExtraLife(mousePos));
}

void MapEditor::createOcto_Pi(sf::Vector2f mousePos){
	mEntities.push_back(Factory::createOcto_Pi(mousePos));
}



// Terrains
void MapEditor::createBlock0(sf::Vector2f mousePos){
	mTerrains.push_back(Factory::createBlock0(mousePos,'a', 'q'));
}

void MapEditor::createBlock0WallJump(sf::Vector2f mousePos){
	mTerrains.push_back(Factory::createBlock0WallJump(mousePos, 'p', 'q'));
}

void MapEditor::createBlock0Icy(sf::Vector2f mousePos){
	mTerrains.push_back(Factory::createBlock0Icy(mousePos, 'a', 'q'));
}

void MapEditor::createSpikes(sf::Vector2f mousePos){
	mTerrains.push_back(Factory::createSpikes(mousePos, mRotDirection));
}

void MapEditor::createGoal(sf::Vector2f mousepos) {
	mTerrains.push_back(Factory::createGoal(mousepos));
}

void MapEditor::createEditorEvent(sf::Vector2f mousePos) {
	mTerrains.push_back(Factory::createEditorEvent(mousePos, mEventType,mEventSize));
}

void MapEditor::createMeatballSpawner(sf::Vector2f mousepos) {
	mTerrains.push_back(Factory::createMeatballSpawner(mousepos));
}

// Decorations
void MapEditor::createDecoration(sf::Vector2f mousepos, char id, char layer, char rotation) {
	if (id == '0') {	// Lol
		mAirHorn.play();
	}
	mDecorations.push_back(Factory::createDecoration(mousepos, id, layer, rotation));
}


void MapEditor::setCurrentLevel(std::string & levelDirectory, std::string & levelName){
	mCurrentLevelDirectory = levelDirectory;
	mCurrentLevelName = levelName;

}

void MapEditor::loadLevel(){

	MapEditor::createGrid();

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
	switch (mInsertType) {
	case MapEditorMeny::BLOCK0:
		MapEditor::createBlock0(mousePos);
		break;
	case MapEditorMeny::PLAYER:
		MapEditor::createPlayer(mousePos);
		break;
	case MapEditorMeny::WORM:
		MapEditor::createWorm(mousePos);
		break;
	case MapEditorMeny::GERM:
		MapEditor::createGerm(mousePos);
		break;
	case MapEditorMeny::ACIDMONSTER:
		MapEditor::createAcidMonster(mousePos);
		break;
	case MapEditorMeny::EXTRALIFE:
		MapEditor::createExtraLife(mousePos);
		break;
	case MapEditorMeny::OCTO_PI:
		MapEditor::createOcto_Pi(mousePos);
		break;
	case MapEditorMeny::BLOCK0WALLJUMP:
		MapEditor::createBlock0WallJump(mousePos);
		break;
	case MapEditorMeny::BLOCK0ICY:
		MapEditor::createBlock0Icy(mousePos);
		break;
	case MapEditorMeny::SPIKES:
		MapEditor::createSpikes(mousePos);
		break;
	case MapEditorMeny::BLOCKGOAL:
		MapEditor::createGoal(mousePos);
		break;
	case MapEditorMeny::DECORATION0:
		MapEditor::createDecoration(mousePos, '0', mDecorationLayer, mRotDirection);
		break;
	case MapEditorMeny::DECORATION1:
		MapEditor::createDecoration(mousePos, '1', mDecorationLayer, mRotDirection);
		break;
	case MapEditorMeny::DECORATION2:
		MapEditor::createDecoration(mousePos, '2', mDecorationLayer, mRotDirection);
		break;
	case MapEditorMeny::DECORATION3:
		MapEditor::createDecoration(mousePos, '3', mDecorationLayer, mRotDirection);
		break;
	case MapEditorMeny::DECORATION4:
		MapEditor::createDecoration(mousePos, '4', mDecorationLayer, mRotDirection);
		break;
	case MapEditorMeny::DECORATION5:
		MapEditor::createDecoration(mousePos, '5', mDecorationLayer, mRotDirection);
		break;
	case MapEditorMeny::DECORATION6:
		MapEditor::createDecoration(mousePos, '6', mDecorationLayer, mRotDirection);
		break;
	case MapEditorMeny::DECORATION7:
		MapEditor::createDecoration(mousePos, '7', mDecorationLayer, mRotDirection);
		break;
	case MapEditorMeny::DECORATION8:
		MapEditor::createDecoration(mousePos, '8', mDecorationLayer, mRotDirection);
		break;
	case MapEditorMeny::DECORATION9:
		MapEditor::createDecoration(mousePos, '9', mDecorationLayer, mRotDirection);
		break;
	case MapEditorMeny::DECORATION10:
		MapEditor::createDecoration(mousePos, 'a', mDecorationLayer, mRotDirection);
		break;
	case MapEditorMeny::DECORATION11:
		MapEditor::createDecoration(mousePos, 'b', mDecorationLayer, mRotDirection);
		break;
	case MapEditorMeny::DECORATION12:
		MapEditor::createDecoration(mousePos, 'c', mDecorationLayer, mRotDirection);
		break;
	case MapEditorMeny::DECORATION13:
		MapEditor::createDecoration(mousePos, 'd', mDecorationLayer, mRotDirection);
		break;
	case MapEditorMeny::DECORATION14:
		MapEditor::createDecoration(mousePos, 'e', mDecorationLayer, mRotDirection);
		break;
	case MapEditorMeny::DECORATION15:
		MapEditor::createDecoration(mousePos, 'f', mDecorationLayer, mRotDirection);
		break;
	case MapEditorMeny::DECORATION16:
		MapEditor::createDecoration(mousePos, 'g', mDecorationLayer, mRotDirection);
		break;
	case MapEditorMeny::DECORATION17:
		MapEditor::createDecoration(mousePos, 'h', mDecorationLayer, mRotDirection);
		break;
	case MapEditorMeny::DECORATION18:
		MapEditor::createDecoration(mousePos, 'j', mDecorationLayer, mRotDirection);
		break;
	case MapEditorMeny::DECORATION19:
		MapEditor::createDecoration(mousePos, 'k', mDecorationLayer, mRotDirection);
		break;
	case MapEditorMeny::DECORATION20:
		MapEditor::createDecoration(mousePos, 'l', mDecorationLayer, mRotDirection);
		break;
	case MapEditorMeny::DECORATION21:
		MapEditor::createDecoration(mousePos, 'm', mDecorationLayer, mRotDirection);
		break;
	case MapEditorMeny::DECORATION22:
		MapEditor::createDecoration(mousePos, 'n', mDecorationLayer, mRotDirection);
		break;
	case MapEditorMeny::DECORATION23:
		MapEditor::createDecoration(mousePos, 'o', mDecorationLayer, mRotDirection);
		break;
	case MapEditorMeny::DECORATION24:
		MapEditor::createDecoration(mousePos, 'p', mDecorationLayer, mRotDirection);
		break;
	case MapEditorMeny::DECORATION25:
		MapEditor::createDecoration(mousePos, 'q', mDecorationLayer, mRotDirection);
		break;
	case MapEditorMeny::DECORATION26:
		MapEditor::createDecoration(mousePos, 'r', mDecorationLayer, mRotDirection);
		break;
	case MapEditorMeny::DECORATION27:
		MapEditor::createDecoration(mousePos, 's', mDecorationLayer, mRotDirection);
		break;
	case MapEditorMeny::DECORATION28:
		MapEditor::createDecoration(mousePos, 't', mDecorationLayer, mRotDirection);
		break;
	case MapEditorMeny::DECORATION29:
		MapEditor::createDecoration(mousePos, 'u', mDecorationLayer, mRotDirection);
		break;
	case MapEditorMeny::MEATBALL:
		MapEditor::createMeatball(mousePos);
		break;
	case MapEditorMeny::MEATBALLSPAWNER:
		MapEditor::createMeatballSpawner(mousePos);
		break;
	case MapEditorMeny::EVENT:
		MapEditor::createEditorEvent(mousePos);
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
		mInsertType = MapEditorMeny::GERM;
		break;
	case MapEditorMeny::GERM:
		mInsertType = MapEditorMeny::BLOCK0;
		break;
	case MapEditorMeny::BLOCK0:
		mInsertType = MapEditorMeny::BLOCK0WALLJUMP;
		break;
	case MapEditorMeny::BLOCK0WALLJUMP:
		mInsertType = MapEditorMeny::BLOCK0ICY;
		break;
	case MapEditorMeny::BLOCK0ICY:
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
		mInsertType = MapEditorMeny::DECORATION2;
		break;
	case MapEditorMeny::DECORATION2:
		mInsertType = MapEditorMeny::DECORATION3;
		break;
	case MapEditorMeny::DECORATION3:
		mInsertType = MapEditorMeny::DECORATION4;
		break;
	case MapEditorMeny::DECORATION4:
		mInsertType = MapEditorMeny::DECORATION5;
		break;
	case MapEditorMeny::DECORATION5:
		mInsertType = MapEditorMeny::DECORATION6;
		break;
	case MapEditorMeny::DECORATION6:
		mInsertType = MapEditorMeny::DECORATION7;
		break;
	case MapEditorMeny::DECORATION7:
		mInsertType = MapEditorMeny::DECORATION8;
		break;
	case MapEditorMeny::DECORATION8:
		mInsertType = MapEditorMeny::DECORATION9;
		break;
	case MapEditorMeny::DECORATION9:
		mInsertType = MapEditorMeny::EVENT;
		break;
	case MapEditorMeny::EVENT:
		mInsertType = MapEditorMeny::MEATBALLSPAWNER;
		break;
	case MapEditorMeny::MEATBALLSPAWNER:
		mInsertType = MapEditorMeny::MEATBALL;
		break;
	case MapEditorMeny::MEATBALL:
		mInsertType = MapEditorMeny::EXTRALIFE;
		break;
	case MapEditorMeny::EXTRALIFE:
		mInsertType = MapEditorMeny::OCTO_PI;
		break;
	case MapEditorMeny::OCTO_PI:
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
	mTextHandler.renderCurrentLayer(window, textToRender + layerToString());
}

std::string MapEditor::layerToString() const {
	switch (mDecorationLayer) {
	case 'b':	return "Back";
	case 'f':	return "Front";
	default:	return "Unknown";
	}
}

void MapEditor::saveMap(){

	std::string currentLevelDirectory = Toolbox::getCurrentLevelDirectory();
	MapEditor::sortVectors();

	currentLevelDirectory[15] = 'T';
	MapEditor::writeTerrainToFile(currentLevelDirectory);

	currentLevelDirectory[15] = 'E';
	MapEditor::writeEntityToFile(currentLevelDirectory);

	currentLevelDirectory[15] = 'D';
	MapEditor::writeDecorationToFile(currentLevelDirectory);


	currentLevelDirectory[15] = 'm';

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

	// Sort terrain after x-pos, then y-pos
	for (Terrains::size_type i = 0; i < mTerrains.size(); i++) {
		for (Terrains::size_type j = 0; j < mTerrains.size() - 1; j++) {
			if (mTerrains[j]->getPos().x > mTerrains[j + 1]->getPos().x) {
				Terrain* temp(mTerrains[j]);
				mTerrains[j] = mTerrains[j + 1];
				mTerrains[j + 1] = temp;
			}
			else if ((mTerrains[j]->getPos().x == mTerrains[j + 1]->getPos().x && mTerrains[j]->getPos().y > mTerrains[j + 1]->getPos().y)) {
				Terrain* temp(mTerrains[j]);
				mTerrains[j] = mTerrains[j + 1];
				mTerrains[j + 1] = temp;
			}
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
				for (int i1 = 0; i1 < blockType(mTerrains[i]).size(); i1++) {
					output.push_back(blockType(mTerrains[i])[i1]);
				}
				break;

			case Terrain::BLOCK0WALLJUMP:
				output.push_back('B');
				output.push_back('W');
				// Push what type of block it is
				for (int i1 = 0; i1 < blockType(mTerrains[i]).size(); i1++) {
					output.push_back(blockType(mTerrains[i])[i1]);
				}
				break;

			case Terrain::BLOCK0ICY:
				output.push_back('B');
				output.push_back('I');
				// Push what type of block it is
				for (int i1 = 0; i1 < blockType(mTerrains[i]).size(); i1++) {
					output.push_back(blockType(mTerrains[i])[i1]);
				}
				break;

			case Terrain::SPIKES:
				output.push_back('S');
				output.push_back('0');
				// Push what rot is has
				output.push_back(mTerrains[i]->getTileType());
				break;

			case Terrain::BLOCKGOAL:
				output.push_back('G');
				output.push_back('0');
				break;

			case Terrain::EVENT:
				output.push_back('E');
				output.push_back('V');
				output.push_back(mTerrains[i]->getTileType());
				posString = MapEditor::floatToString(mTerrains[i]->getWidth());

				for (std::string::size_type iS = 0; iS < posString.size(); iS++) {
					output.push_back(posString[iS]);
				}
				output.push_back(',');
				posString = MapEditor::floatToString(mTerrains[i]->getHeight());

				for (std::string::size_type iS = 0; iS < posString.size(); iS++) {
					output.push_back(posString[iS]);
				}

				break;

			case Terrain::MEATBALLSPAWNER:
				output.push_back('M');
				output.push_back('0');
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

			case Entity::GERM:
				output.push_back('G');
				output.push_back('E');
				break;

			case Entity::ACIDMONSTER:
				output.push_back('A');
				output.push_back('C');
				break;

			case Entity::MEATBALL:
				output.push_back('M');
				output.push_back('0');
				break;

			case Entity::EXTRALIFE:
				output.push_back('E');
				output.push_back('0');
				break;

			case Entity::OCTO_PI:
				output.push_back('O');
				output.push_back('P');
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
			case Decoration::HIGH:
				output.push_back('2');
				break;
			case Decoration::FIVE:
				output.push_back('3');
				break;
			case Decoration::FOURTWENTYBLAZEITFAGGOT:
				output.push_back('4');
				break;
			case Decoration::DANK:
				output.push_back('5');
				break;
			case Decoration::SHREK:
				output.push_back('6');
				break;
			case Decoration::TRUMP:
				output.push_back('7');
				break;
			case Decoration::BERNIE:
				output.push_back('8');
				break;
			case Decoration::LIVIA:
				output.push_back('9');
				break;
			case Decoration::TEN:
				output.push_back('a');
				break;
			case Decoration::ELEVEN:
				output.push_back('b');
				break;
			case Decoration::TWELVE:
				output.push_back('c');
				break;
			case Decoration::THIRTEEN:
				output.push_back('d');
				break;
			case Decoration::FOURTEEN:
				output.push_back('e');
				break;
			case Decoration::FIFTEEN:
				output.push_back('f');
				break;
			case Decoration::SIXTEEN:
				output.push_back('g');
				break;
			case Decoration::SEVENTEEN:
				output.push_back('h');
				break;
			case Decoration::EIGHTEEN:
				output.push_back('i');
				break;
			case Decoration::NINETEEN:
				output.push_back('j');
				break;
			case Decoration::TWENTY:
				output.push_back('k');
				break;
			case Decoration::TWENTYONE:
				output.push_back('l');
				break;
			case Decoration::TWENTYTWO:
				output.push_back('m');
				break;
			case Decoration::TWENTYTHREE:
				output.push_back('n');
				break;
			case Decoration::TWENTYFOUR:
				output.push_back('o');
				break;
			case Decoration::TWENTYFIVE:
				output.push_back('p');
				break;
			case Decoration::TWENTYSIX:
				output.push_back('q');
				break;
			case Decoration::TWENTYSEVEN:
				output.push_back('r');
				break;
			case Decoration::TWENTYEIGHT:
				output.push_back('s');
				break;
			case Decoration::TWENTYNINE:
				output.push_back('t');
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
			output.push_back(mDecorations[i]->getRotation());
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

std::string MapEditor::blockType(Terrain* terrain){

	bool leftOccupied(false);
	bool rightOccupied(false);
	bool topOccupied(false);
	bool botOccupied(false);
	bool topLeftOccupied(true);
	bool topRightOccupied(true);
	bool botLeftOccupied(true);
	bool botRightOccupied(true);

	sf::Vector2f thisPos(terrain->getPos());
	std::string returnString;

	Terrains relevantTerrains;
	for (Terrains::size_type i = 0; i < mTerrains.size(); i++){
		if (mTerrains[i]->getPos().x < thisPos.x + 200 && mTerrains[i]->getPos().x > thisPos.x - 200)
			if(mTerrains[i]->getType() == Terrain::BLOCK0 || 
				mTerrains[i]->getType() == Terrain::BLOCK0ICY || 
				mTerrains[i]->getType() == Terrain::BLOCK0WALLJUMP)
			relevantTerrains.push_back(mTerrains[i]);
	}

	
	sf::Vector2f leftBorder(thisPos.x - 1, 
		thisPos.y + (terrain->getHeight()/ 2));
	sf::Vector2f rightBorder(thisPos.x + terrain->getWidth() + 1, 
		thisPos.y + (terrain->getHeight() / 2));
	sf::Vector2f topBorder(thisPos.x + (terrain->getWidth() / 2), 
		thisPos.y - 1);
	sf::Vector2f botBorder(thisPos.x + (terrain->getWidth() / 2), 
		thisPos.y + (terrain->getHeight() + 1));
	sf::Vector2f topLeftBorder(terrain->getPos());
	topLeftBorder.x -= 1;
	topLeftBorder.y -= 1;
	sf::Vector2f topRightBorder(terrain->getPos());
	topRightBorder.x += terrain->getWidth() + 1;
	topRightBorder.y -= 1;
	sf::Vector2f botLeftBorder(terrain->getPos());
	botLeftBorder.x -= 1;
	botLeftBorder.y += terrain->getHeight() + 1;
	sf::Vector2f botRightBorder(terrain->getPos());
	botRightBorder.x += terrain->getWidth() + 1;
	botRightBorder.y += terrain->getHeight() + 1;

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
		returnString.push_back('a');
	if (leftOccupied && rightOccupied && topOccupied && !botOccupied)
		returnString.push_back('b');
	if (leftOccupied && rightOccupied && !topOccupied && botOccupied)
		returnString.push_back('c');
	if (leftOccupied && !rightOccupied && topOccupied && botOccupied)
		returnString.push_back('d');
	if (!leftOccupied && rightOccupied && topOccupied && botOccupied)
		returnString.push_back('e');
	if (leftOccupied && rightOccupied && !topOccupied && !botOccupied)
		returnString.push_back('f');
	if (leftOccupied && !rightOccupied && topOccupied && !botOccupied)
		returnString.push_back('g');
	if (!leftOccupied && rightOccupied && topOccupied && !botOccupied)
		returnString.push_back('h');
	if (leftOccupied && !rightOccupied && !topOccupied && botOccupied)
		returnString.push_back('i');
	if (!leftOccupied && rightOccupied && !topOccupied && botOccupied)
		returnString.push_back('j');
	if (!leftOccupied && !rightOccupied && topOccupied && botOccupied)
		returnString.push_back('k');
	if (leftOccupied && !rightOccupied && !topOccupied && !botOccupied)
		returnString.push_back('l');
	if (!leftOccupied && rightOccupied && !topOccupied && !botOccupied)
		returnString.push_back('m');
	if (!leftOccupied && !rightOccupied && topOccupied && !botOccupied)
		returnString.push_back('n');
	if (!leftOccupied && !rightOccupied && !topOccupied && botOccupied)
		returnString.push_back('o');
	if (!leftOccupied && !rightOccupied && !topOccupied && !botOccupied)
		returnString.push_back('p');

	bool tileDecNeeded(false);

	if (returnString[0] == 'a') {
		topLeftOccupied = false;
		topRightOccupied = false;
		botLeftOccupied = false;
		botRightOccupied = false;
		for (Terrains::size_type i = 0; i < relevantTerrains.size(); i++) {
		
			if (MapEditor::isSpriteClicked(relevantTerrains[i]->getSprite(), &topLeftBorder))
				topLeftOccupied = true;
			if (MapEditor::isSpriteClicked(relevantTerrains[i]->getSprite(), &topRightBorder))
				topRightOccupied = true;
			if (MapEditor::isSpriteClicked(relevantTerrains[i]->getSprite(), &botLeftBorder))
				botLeftOccupied = true;
			if (MapEditor::isSpriteClicked(relevantTerrains[i]->getSprite(), &botRightBorder))
				botRightOccupied = true;

		}
		tileDecNeeded = true;
	}
	if (returnString[0] == 'b') {
		topLeftOccupied = false;
		topRightOccupied = false;
		for (Terrains::size_type i = 0; i < relevantTerrains.size(); i++) {

			if (MapEditor::isSpriteClicked(relevantTerrains[i]->getSprite(), &topLeftBorder))
				topLeftOccupied = true;
			if (MapEditor::isSpriteClicked(relevantTerrains[i]->getSprite(), &topRightBorder))
				topRightOccupied = true;
		}
		tileDecNeeded = true;
	}
	if (returnString[0] == 'c') {
		botLeftOccupied = false;
		botRightOccupied = false;
		for (Terrains::size_type i = 0; i < relevantTerrains.size(); i++) {
			if (MapEditor::isSpriteClicked(relevantTerrains[i]->getSprite(), &botLeftBorder))
				botLeftOccupied = true;
			if (MapEditor::isSpriteClicked(relevantTerrains[i]->getSprite(), &botRightBorder))
				botRightOccupied = true;
		}
		tileDecNeeded = true;
	}
	if (returnString[0] == 'd') {
		topLeftOccupied = false;
		botLeftOccupied = false;
		for (Terrains::size_type i = 0; i < relevantTerrains.size(); i++) {
			if (MapEditor::isSpriteClicked(relevantTerrains[i]->getSprite(), &topLeftBorder))
				topLeftOccupied = true;
			if (MapEditor::isSpriteClicked(relevantTerrains[i]->getSprite(), &botLeftBorder))
				botLeftOccupied = true;
		}
		tileDecNeeded = true;
	}
	if (returnString[0] == 'e') {
		topRightOccupied = false;
		botRightOccupied = false;
		for (Terrains::size_type i = 0; i < relevantTerrains.size(); i++) {
			if (MapEditor::isSpriteClicked(relevantTerrains[i]->getSprite(), &topRightBorder))
				topRightOccupied = true;
			if (MapEditor::isSpriteClicked(relevantTerrains[i]->getSprite(), &botRightBorder))
				botRightOccupied = true;
		}
		tileDecNeeded = true;
	}
	if (returnString[0] == 'g') {
		topLeftOccupied = false;
		for (Terrains::size_type i = 0; i < relevantTerrains.size(); i++) {
			if (MapEditor::isSpriteClicked(relevantTerrains[i]->getSprite(), &topLeftBorder))
				topLeftOccupied = true;
		}
		tileDecNeeded = true;
	}
	if (returnString[0] == 'h') {
		topRightOccupied = false;
		for (Terrains::size_type i = 0; i < relevantTerrains.size(); i++) {
			if (MapEditor::isSpriteClicked(relevantTerrains[i]->getSprite(), &topRightBorder))
				topRightOccupied = true;
		}
		tileDecNeeded = true;
	}
	if (returnString[0] == 'i') {
		botLeftOccupied = false;
		for (Terrains::size_type i = 0; i < relevantTerrains.size(); i++) {
			if (MapEditor::isSpriteClicked(relevantTerrains[i]->getSprite(), &botLeftBorder))
				botLeftOccupied = true;
		}
		tileDecNeeded = true;
	}
	if (returnString[0] == 'j') {
		botRightOccupied = false;
		for (Terrains::size_type i = 0; i < relevantTerrains.size(); i++) {
			if (MapEditor::isSpriteClicked(relevantTerrains[i]->getSprite(), &botRightBorder))
				botRightOccupied = true;
		}
		tileDecNeeded = true;
	}
	if (tileDecNeeded) {
		if (!topLeftOccupied && !topRightOccupied && !botRightOccupied && !botLeftOccupied)
			returnString.push_back('a');
		if (topLeftOccupied && topRightOccupied && !botRightOccupied && !botLeftOccupied)
			returnString.push_back('b');
		if (!topLeftOccupied && topRightOccupied && botRightOccupied && !botLeftOccupied)
			returnString.push_back('c');
		if (topLeftOccupied && !topRightOccupied && !botRightOccupied && botLeftOccupied)
			returnString.push_back('d');
		if (!topLeftOccupied && !topRightOccupied && botRightOccupied && botLeftOccupied)
			returnString.push_back('e');
		if (!topLeftOccupied && topRightOccupied && botRightOccupied && botLeftOccupied)
			returnString.push_back('f');
		if (topLeftOccupied && !topRightOccupied && botRightOccupied && botLeftOccupied)
			returnString.push_back('g');
		if (topLeftOccupied && topRightOccupied && !botRightOccupied && botLeftOccupied)
			returnString.push_back('h');
		if (topLeftOccupied && topRightOccupied && botRightOccupied && !botLeftOccupied)
			returnString.push_back('i');
		if (topLeftOccupied && !topRightOccupied && !botRightOccupied && !botLeftOccupied)
			returnString.push_back('j');
		if (!topLeftOccupied && topRightOccupied && !botRightOccupied && !botLeftOccupied)
			returnString.push_back('k');
		if (!topLeftOccupied && !topRightOccupied && botRightOccupied && !botLeftOccupied)
			returnString.push_back('l');
		if (!topLeftOccupied && !topRightOccupied && !botRightOccupied && botLeftOccupied)
			returnString.push_back('m');	
	}

	return returnString;
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
	std::string currentLevelName = Toolbox::getCurrentLevelName();
	if (currentLevelName == "Throat") {
		mMapDimensionsTiles = sf::Vector2f(50, 500);
	}
	else if (currentLevelName == "Stomach") {
		mMapDimensionsTiles = sf::Vector2f(500, 50);
	}
	else if (currentLevelName == "Hub") {
		mMapDimensionsTiles = sf::Vector2f(100, 100);
	}
	else if (currentLevelName == "Intestine") {
		mMapDimensionsTiles = sf::Vector2f(250, 350);
	}
	else if (currentLevelName == "Mouth") {
		mMapDimensionsTiles = sf::Vector2f(500, 50);
	}

	mGrid.clear();

	sf::Vector2f lastTilePos(-mTileDimensions.x, -mTileDimensions.y);
	//std::vector<sf::Sprite> tiles;

	for (size_t i = 0; i < mMapDimensionsTiles.x; i++){
		sf::Vector2f tilePos(0, -1000);
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

void MapEditor::changeEventType() {
	mEventType++;
	if (mEventType == 'h') {
		mEventType = 'a';
	}
}