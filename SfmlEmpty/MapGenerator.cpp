#include "MapGenerator.h"
#include <fstream>

MapGenerator::MapGenerator() :
mTerrainhandler(&Terrainhandler::getInstance()),
mEntityhandler(&Entityhandler::getInstance()),
mDecorationhandler(&Decorationhandler::getInstance()){
}

MapGenerator::~MapGenerator(){
}

MapGenerator& MapGenerator::getInstance(){
	static MapGenerator mapGenerator;
	return mapGenerator;
}


// Finds all mapfiles for a given mapname, mapname must have a letter in front of it
void MapGenerator::loadMap(std::string &mapname){

	mEntityhandler->clear();
	mTerrainhandler->clear();
	mDecorationhandler->clear();

	mapname[15] = 'T';
	MapGenerator::readTerrainfile(mapname);


	mapname[15] = 'E';
	MapGenerator::readEntityfile(mapname);


	mapname[15] = 'D';
	MapGenerator::readDecorationfile(mapname);


	mapname[15] = 'm';

	createCollisionBlocks();
}

void MapGenerator::readTerrainfile(std::string &filename){

	std::string line;
	std::ifstream terrainfile(filename);

	if (terrainfile.is_open()){
		while (getline(terrainfile, line)){

			// Reads from textdoc and creates terrain according to letter
			//  with position according to x/y numbers
			switch (line[0]){
			case 'B':
				switch (line[1]){
				case '0':
					MapGenerator::createBlock0(MapGenerator::readPosition(line),line[2]);
					break;
				case 'W':
					MapGenerator::createBlock0WallJump(MapGenerator::readPosition(line),line[2]);
					break;
				case 'I':
					MapGenerator::createBlock0Icy(MapGenerator::readPosition(line), line[2]);
					break;
				default:
					break;
				}
				break;
				
				

			 // Event block

			case 'O':
					MapGenerator::createEvent(MapGenerator::readPosition(line), line[1]);
					break;

			// Spikes
			case 'S':
				switch (line[1]){
				case '0':
					MapGenerator::createSpikes(MapGenerator::readPosition(line), line[2]);
					break;
				default:
					break;
				}
				break;

			// Goal
			case 'G':
				MapGenerator::createGoal(MapGenerator::readPosition(line));
				break;

			// Meatball spawner
			case 'M':
				MapGenerator::createMeatballSpawner(MapGenerator::readPosition(line), 0.01);
				break;

			default:
				break;
			}
		}
	}
	terrainfile.close();
}

void MapGenerator::readEntityfile(std::string &filename){
	bool playerLoaded(false);
	std::string line;
	std::ifstream entityfile(filename);

	if (entityfile.is_open()){
		while (getline(entityfile, line)){

			// Reads from textdoc and creates entity according to letter
			//  with position according to x/y numbers
			switch (line[0]){
			case 'P':
				switch (line[1]){
				case '0':
					MapGenerator::createPlayer(MapGenerator::readPosition(line));
					playerLoaded = true;
					break;
				default:
					break;
				}
				break;
			case 'W':
				switch (line[1]){
				case '0':
					MapGenerator::createWorm(MapGenerator::readPosition(line));
				default:
					break;
				}
				break;
			case 'A':
				switch (line[1]){
				case 'C':
					MapGenerator::createAcidMonster(MapGenerator::readPosition(line));
				default:
					break;
				}
				break;
			case 'M':
				switch (line[1]) {
				case 'B':
					MapGenerator::createMeatball(MapGenerator::readPosition(line));
				default:
					break;
				}
				break;
			default:
				break;

			}
		}
	}
	entityfile.close();
	if (!playerLoaded)
		MapGenerator::createPlayer(sf::Vector2f(0,0));
}

void MapGenerator::readDecorationfile(std::string &filename) {
	std::string line;
	std::ifstream decorationFile(filename);

	if (decorationFile.is_open()) {
		while (getline(decorationFile, line)) {
			switch (line[0]) {
			case 'D':
				MapGenerator::createDecoration(MapGenerator::readPosition(line), line[1], line[2]);
				break;
			default:
				break;
			}
		}
	}
	decorationFile.close();
}



// Create entities
void MapGenerator::createWorm(sf::Vector2f pos){
	mEntityhandler->addEntity(Factory::createWorm(pos));
}

void MapGenerator::createPlayer(sf::Vector2f pos){
	mEntityhandler->addEntity(Factory::createPlayer(pos));
}

void MapGenerator::createAcidMonster(sf::Vector2f pos){
	mEntityhandler->addEntity(Factory::createAcidMonster(pos));
}

void MapGenerator::createMeatball(sf::Vector2f pos) {
	mEntityhandler->addEntity(Factory::createMeatball(pos));
}


// Create terrains
void MapGenerator::createBlock0(sf::Vector2f pos, char type){
	mTempBlocks.push_back(Factory::createBlock0(pos, type));
}

void MapGenerator::createBlock0WallJump(sf::Vector2f pos, char type){
	mTempBlocks.push_back(Factory::createBlock0WallJump(pos, type));
}

void MapGenerator::createBlock0Icy(sf::Vector2f pos, char type){
	mTempBlocks.push_back(Factory::createBlock0Icy(pos, type));
}

void MapGenerator::createSpikes(sf::Vector2f pos, char type){
	mTerrainhandler->addTerrain(Factory::createSpikes(pos, type));
}

void MapGenerator::createGoal(sf::Vector2f pos) {
	mTerrainhandler->addTerrain(Factory::createGoal(pos));
}

void MapGenerator::createMeatballSpawner(sf::Vector2f pos, float spawnRate) {
	mTerrainhandler->addTerrain(Factory::createMeatballSpawner(pos, spawnRate));
}

void MapGenerator::createEvent(sf::Vector2f pos, char eventType) {
	mTerrainhandler->addTerrain(Factory::createEvent(pos, eventType));
}


// Create decoration
void MapGenerator::createDecoration(sf::Vector2f pos, char id, char layer) {
	mDecorationhandler->addDecoration(Factory::createDecoration(pos, id, layer));
}


// Create collision blocks
void MapGenerator::createCollisionBlocks() {
	BlockTerrains collisionBlocks;
	for (Terrains::size_type i = 0; i < mTempBlocks.size(); i++) {
		if (collisionBlocks.empty()) {
			collisionBlocks.push_back(Factory::createCollisionBlock(mTempBlocks[i]->getPos()));
			collisionBlocks.back()->addBlockTerrain(mTempBlocks[i], true);
		}
		else {
			if (mTempBlocks[i]->getPos().x == collisionBlocks.back()->getPos().x) {
				if (mTempBlocks[i]->getPos().y == collisionBlocks.back()->getPos().y + collisionBlocks.back()->getHeight()) {
					collisionBlocks.back()->addBlockTerrain(mTempBlocks[i], false);
				}
				else {
					collisionBlocks.push_back(Factory::createCollisionBlock(mTempBlocks[i]->getPos()));
					collisionBlocks.back()->addBlockTerrain(mTempBlocks[i], true);
				}
			}
			else {
				collisionBlocks.push_back(Factory::createCollisionBlock(mTempBlocks[i]->getPos()));
				collisionBlocks.back()->addBlockTerrain(mTempBlocks[i], true);
			}
		}
	}
	MapGenerator::mergeCollisionblocks(collisionBlocks);
	for (BlockTerrains::size_type i = 0; i < collisionBlocks.size(); i++) {
		mTerrainhandler->addCollisionblock(collisionBlocks[i]);
	}
	mTempBlocks.clear();
}


void MapGenerator::mergeCollisionblocks(BlockTerrains& blockterrains){
	for (BlockTerrains::size_type i = 0; i < blockterrains.size(); i++) {
		for (BlockTerrains::size_type j = i+1; j < blockterrains.size(); j++) {
			if (blockterrains[i]->getPos().x == (blockterrains[j]->getPos().x - blockterrains[i]->getWidth())
				&& blockterrains[i]->getPos().y == blockterrains[j]->getPos().y 
				&& blockterrains[i]->getHeight() == blockterrains[j]->getHeight()) {
				bool Xnew;
				for (BlockTerrain::Terrains2D::size_type BI = 0; BI < blockterrains[j]->getBlocks().size(); BI++) {
					Xnew = true;
					for (BlockTerrain::Terrains::size_type BJ = 0; BJ < blockterrains[j]->getBlocks()[BI]->size(); BJ++) {
						blockterrains[i]->addBlockTerrain(blockterrains[j]->getBlocks()[BI]->at(BJ), Xnew);
						Xnew = false;
					}
				}
				delete blockterrains[j];
				blockterrains.erase(blockterrains.begin() + j);
				j--;
			}
		}
	}

}



sf::Vector2f MapGenerator::readPosition(std::string line){


	// Translates string of two cordinates too floats of corndinates
	// returns cordinates when a "-" is read

	bool yDone = false;
	bool deciDone = false;

	float xSum = 0.0;
	float ySum = 0.0;

	int multiplier = 1;
	int deciDivider = 1;



	for (int i = line.size(); i > -1; i--){

		switch (line[i]){

		case '0':
			if (!deciDone){
				deciDivider *= 10;
			}
			multiplier *= 10;
			break;


		case '1':
			if (!yDone){
				ySum += multiplier;
			}
			else{
				xSum += multiplier;
			}
			if (!deciDone){
				deciDivider *= 10;
			}
			multiplier *= 10;
			break;


		case '2':
			if (!yDone){
				ySum += (2 * multiplier);
			}
			else{
				xSum += (2 * multiplier);
			}
			if (!deciDone){
				deciDivider *= 10;
			}
			multiplier *= 10;
			break;

		case '3':
			if (!yDone){
				ySum += (3 * multiplier);
			}
			else{
				xSum += (3 * multiplier);
			}
			if (!deciDone){
				deciDivider *= 10;
			}
			multiplier *= 10;
			break;

		case '4':
			if (!yDone){
				ySum += (4 * multiplier);
			}
			else{
				xSum += (4 * multiplier);
			}
			if (!deciDone){
				deciDivider *= 10;
			}
			multiplier *= 10;
			break;


		case '5':
			if (!yDone){
				ySum += (5 * multiplier);
			}
			else{
				xSum += (5 * multiplier);
			}
			if (!deciDone){
				deciDivider *= 10;
			}
			multiplier *= 10;
			break;

		case '6':
			if (!yDone){
				ySum += (6 * multiplier);
			}
			else{
				xSum += (6 * multiplier);
			}
			if (!deciDone){
				deciDivider *= 10;
			}
			multiplier *= 10;
			break;

		case '7':
			if (!yDone){
				ySum += (7 * multiplier);
			}
			else{
				xSum += (7 * multiplier);
			}
			if (!deciDone){
				deciDivider *= 10;
			}
			multiplier *= 10;
			break;


		case '8':
			if (!yDone){
				ySum += (8 * multiplier);
			}
			else{
				xSum += (8 * multiplier);
			}
			if (!deciDone){
				deciDivider *= 10;
			}
			multiplier *= 10;
			break;

		case '9':
			if (!yDone){
				ySum += (9 * multiplier);
			}
			else{
				xSum += (9 * multiplier);
			}
			if (!deciDone){
				deciDivider *= 10;
			}
			multiplier *= 10;
			break;

		case '.':
			deciDone = true;
			break;

		case ',':
			if (deciDone)
				ySum /= deciDivider;

			yDone = true;
			deciDone = false;
			multiplier = 1;
			deciDivider = 1;
			break;

		case '|':
			if (deciDone)
				xSum /= deciDivider;

			return sf::Vector2f(xSum, ySum);
			break;

		case '-':
			if (yDone)
				xSum *= -1;
			else
				ySum *= -1;
			break;

		default:
			break;
		}
	}
	return sf::Vector2f(xSum, ySum);
}
