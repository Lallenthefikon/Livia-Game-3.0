#include "MapGenerator.h"
#include <fstream>
#include <iostream>

MapGenerator::MapGenerator() :
mTerrainhandler(Terrainhandler::getInstance()),
mEntityHandler(Entityhandler::getInstance()),
mDecorationhandler(&Decorationhandler::getInstance()){
}

MapGenerator::~MapGenerator(){
}

MapGenerator& MapGenerator::getInstance(){
	static MapGenerator mapGenerator;
	return mapGenerator;
}


// Finds all mapfiles for a given mapname, mapname must have a letter in front of it
void MapGenerator::loadMap(std::string &mapname, Level *level){

	mEntityHandler->clear();
	mTerrainhandler->clear();
	mDecorationhandler->clear();

	mapname[15] = 'T';
	MapGenerator::readTerrainfile(mapname, level);


	mapname[15] = 'E';
	MapGenerator::readEntityfile(mapname);


	mapname[15] = 'D';
	MapGenerator::readDecorationfile(mapname);


	mapname[15] = 'm';

	createCollisionBlocks();
}

void MapGenerator::readTerrainfile(std::string &filename, Level *level){

	std::string eventSize;

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
					MapGenerator::createBlock0(MapGenerator::readPosition(line),line[2], line[3]);
					break;
				case 'W':
					MapGenerator::createBlock0WallJump(MapGenerator::readPosition(line),line[2], line[3]);
					break;
				case 'I':
					MapGenerator::createBlock0Icy(MapGenerator::readPosition(line), line[2], line[3]);
					break;
				default:
					break;
				}
				break;

				

			 // Event block

			case 'E':
				switch (line[1]){
				case 'V':
					for (int i = 3; i < line.size(); i++) {
						if (line[i] == '|')
							break;
						else
							eventSize.push_back(line[i]);
					}
					MapGenerator::createEvent(MapGenerator::readPosition(line),level, line[2], MapGenerator::readPosition(eventSize));
					eventSize.clear();
					break;
				default:
					break;
				}
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
				MapGenerator::createMeatballSpawner(MapGenerator::readPosition(line));
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
					break;
				default:
					break;
				}
				break;
			case 'G':
				switch (line[1]){
				case 'E':
					MapGenerator::createGerm(MapGenerator::readPosition(line));
				default:
					break;
				}
			case 'A':
				switch (line[1]){
				case 'C':
					MapGenerator::createAcidMonster(MapGenerator::readPosition(line));
					break;
				default:
					break;
				}
				break;
			case 'M':
				switch (line[1]) {
				case '0':
					MapGenerator::createMeatball(MapGenerator::readPosition(line));
					break;
				default:
					break;
				}
				break;
			case 'E':
				switch (line[1]) {
				case '0':
					MapGenerator::createExtraLife(MapGenerator::readPosition(line));
					break;
				default:
					break;
				}
				break;
			case 'O':
				switch (line[1]) {
				case 'P':
					MapGenerator::createOcto_Pi(MapGenerator::readPosition(line));
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
				MapGenerator::createDecoration(MapGenerator::readPosition(line), line[1], line[2], line[3]);
				break;
			default:
				break;
			}
		}
	}
	decorationFile.close();
}



// Create entities
void MapGenerator::createPlayer(sf::Vector2f pos){
	mEntityHandler->add(pos, '0');
}

void MapGenerator::createWorm(sf::Vector2f pos) {
	mEntityHandler->add(pos, '1');
}

void MapGenerator::createAcidMonster(sf::Vector2f pos){
	mEntityHandler->add(pos, '2');
}

void MapGenerator::createMeatball(sf::Vector2f pos) {
	mEntityHandler->add(pos, '3');
}

void MapGenerator::createExtraLife(sf::Vector2f pos) {
	mEntityHandler->add(pos, '4');
}

void MapGenerator::createGerm(sf::Vector2f pos) {
	mEntityHandler->add(pos, '5');
}

void MapGenerator::createOcto_Pi(sf::Vector2f pos) {
	mEntityHandler->add(pos, '6');
}

// Create terrains
void MapGenerator::createBlock0(sf::Vector2f pos, char type, char type1){
	mTempBlocks.push_back(Factory::createBlock0(pos, type, type1));
}

void MapGenerator::createBlock0WallJump(sf::Vector2f pos, char type, char type1){
	mTempBlocks.push_back(Factory::createBlock0WallJump(pos, type, type1));
}

void MapGenerator::createBlock0Icy(sf::Vector2f pos, char type, char type1){
	mTempBlocks.push_back(Factory::createBlock0Icy(pos, type, type1));
}

void MapGenerator::createSpikes(sf::Vector2f pos, char type){
	mTerrainhandler->add(pos, '2', type);
}

void MapGenerator::createGoal(sf::Vector2f pos) {
	mTerrainhandler->add(pos, '3');
}

void MapGenerator::createMeatballSpawner(sf::Vector2f pos) {
	mTerrainhandler->add(pos, '4');
}

void MapGenerator::createEvent(sf::Vector2f pos, Level *level, char eventType, sf::Vector2f size) {
	mTerrainhandler->createEvent(pos, level, eventType, size);
}


// Create decoration
void MapGenerator::createDecoration(sf::Vector2f pos, char id, char layer, char rotation) {
	mDecorationhandler->addDecoration(Factory::createDecoration(pos, id, layer, rotation));
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


void MapGenerator::mergeCollisionblocks(BlockTerrains& blockterrains) {
	for (BlockTerrains::size_type i = 0; i < blockterrains.size(); i++) {
		for (BlockTerrains::size_type j = i + 1; j < blockterrains.size(); j++) {
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
