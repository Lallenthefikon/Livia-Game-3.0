#include "MapEditMaploader.h"
#include <fstream>

MapEditMaploader::MapEditMaploader(){
}


MapEditMaploader::~MapEditMaploader(){
}

MapEditMaploader& MapEditMaploader::getInstance(){
	static MapEditMaploader mapeditmaploader;
	return mapeditmaploader;
}

MapEditMaploader::Terrains MapEditMaploader::getTerrain(std::string &filename){
	MapEditMaploader::readTerrainfile(filename);
	return mTerrains;
}

MapEditMaploader::Entities MapEditMaploader::getEntities(std::string &filename){
	MapEditMaploader::readEntityfile(filename);
	return mEntities;
}

MapEditMaploader::Decorations MapEditMaploader::getDecorations(std::string &filename) {
	MapEditMaploader::readDecorationfile(filename);
	return mDecorations;
}

MapEditMaploader::Dialogue MapEditMaploader::getDialogue(std::string &filename) {
	MapEditMaploader::readDialoguefile(filename);
	return mDialogue;
}

void MapEditMaploader::clear(){
	MapEditMaploader::internalClear();
}

void MapEditMaploader::readTerrainfile(std::string &filename) {

	std::string line;
	std::ifstream terrainfile(filename);

	if (terrainfile.is_open()) {
		while (getline(terrainfile, line)) {

			// Reads from textdoc and creates terrain according to letter
			//  with position according to x/y numbers
			switch (line[0]) {
			case 'B':
				switch (line[1]) {
				case '0':
					MapEditMaploader::createBlock0(MapEditMaploader::readPosition(line), line[2]);
					break;
				case 'W':
					MapEditMaploader::createBlock0WallJump(MapEditMaploader::readPosition(line), line[2]);
					break;
				case 'I':
					MapEditMaploader::createBlock0Icy(MapEditMaploader::readPosition(line), line[2]);
					break;
				default:
					break;
				}
				break;

				// Spikes
			case 'S':
				switch (line[1]) {
				case '0':
					MapEditMaploader::createSpikes(MapEditMaploader::readPosition(line), line[2]);
					break;
				default:
					break;
				}
				break;

				// Goal
			case 'G':
				switch (line[1]) {
				case '0':
					MapEditMaploader::createGoal(MapEditMaploader::readPosition(line));
					break;
				default:
					break;
				}

				// Meatball spawner
			case 'M':
				MapEditMaploader::createMeatballSpawner(MapEditMaploader::readPosition(line), 0.01f);
				break;

			default:
				break;
			}
		}
	}
	terrainfile.close();
}

 void MapEditMaploader::readEntityfile(std::string &filename){
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
					 MapEditMaploader::createPlayer(MapEditMaploader::readPosition(line));
					 break;
				 default:
					 break;
				 }
				 break;

			 case 'W':
				 switch (line[1]){
				 case '0':
					 MapEditMaploader::createWorm(MapEditMaploader::readPosition(line));
				 default:
					 break;
				 }
				 break;
			 case 'G':
				 switch (line[1]){
				 case 'E':
					 MapEditMaploader::createGerm(MapEditMaploader::readPosition(line));
				 default:
					 break;
				 }
				 break;
			 case 'A':
				 switch (line[1]){
				 case 'C':
					 MapEditMaploader::createAcidMonster(MapEditMaploader::readPosition(line));
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
 }

 void MapEditMaploader::readDecorationfile(std::string &filename) {
	 std::string line;
	 std::ifstream decorationFile(filename);

	 if (decorationFile.is_open()) {
		 while (getline(decorationFile, line)) {
			 switch (line[0]) {
			 case 'D':
				 MapEditMaploader::createDecoration(MapEditMaploader::readPosition(line), line[1], line[2]);
				 break;
			 default:
				 break;
			 }
		 }
	 }
	 decorationFile.close();
 }

 void MapEditMaploader::readDialoguefile(std::string &filename) {

	 std::string line;
	 std::ifstream dialoguefile(filename);

	 if (dialoguefile.is_open()) {
		 while (getline(dialoguefile, line)) {
			 switch (line[0]) {
			 case 'Q':
				 switch (line[1]){
				 case '0':
					 MapEditMaploader::createDialogue(MapEditMaploader::readPosition(line), line[1]);
					 break;
				 }
				 
			 default:
				 break;
			 }
		 }
	 }
	 dialoguefile.close();
 }

 void MapEditMaploader::createBlock0(sf::Vector2f &pos, char type){
	 mTerrains.push_back(Factory::createBlock0(pos, type));
 }

 void MapEditMaploader::createPlayer(sf::Vector2f &pos){
	 mEntities.push_back(Factory::createPlayer(pos));
 }

 void MapEditMaploader::createWorm(sf::Vector2f &pos){
	 mEntities.push_back(Factory::createWorm(pos));
 }

 void MapEditMaploader::createGerm(sf::Vector2f & pos){
	 mEntities.push_back(Factory::createGerm(pos));
 }

 void MapEditMaploader::createAcidMonster(sf::Vector2f &pos){
	 mEntities.push_back(Factory::createAcidMonster(pos));
 }

 void MapEditMaploader::createBlock0WallJump(sf::Vector2f &pos, char type){
	mTerrains.push_back(Factory::createBlock0WallJump(pos, type));
 }

 void MapEditMaploader::createBlock0Icy(sf::Vector2f & pos, char type){
	 mTerrains.push_back(Factory::createBlock0Icy(pos, type));
 }

 void MapEditMaploader::createSpikes(sf::Vector2f &pos, char type){
	 mTerrains.push_back(Factory::createSpikes(pos, type));
 }
 
 void MapEditMaploader::createGoal(sf::Vector2f &pos) {
	 mTerrains.push_back(Factory::createGoal(pos));
 }

 void MapEditMaploader::createDecoration(sf::Vector2f &pos, char id, char layer) {
	 mDecorations.push_back(Factory::createDecoration(pos, id, layer));
 }

 void MapEditMaploader::createDialogue(sf::Vector2f &pos, char type) {
	 mDialogue.push_back(Factory::createDialogue(pos));
 }

 void MapEditMaploader::createMeatballSpawner(sf::Vector2f &pos, float spawnRate) {
	 mTerrains.push_back(Factory::createMeatballSpawner(pos, spawnRate));
 }

 sf::Vector2f MapEditMaploader::readPosition(std::string line){


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

 void MapEditMaploader::internalClear(){
	 mEntities.clear();
	 mTerrains.clear();
	 mDialogue.clear();
	 mDecorations.clear();

 }