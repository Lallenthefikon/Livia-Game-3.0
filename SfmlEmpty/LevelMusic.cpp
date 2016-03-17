#include "LevelMusic.h"


LevelMusic::LevelMusic() : 
tempMusic0(Toolbox::getMusic(Toolbox::STOMACHAMBIENCE)),
tempMusic1(Toolbox::getMusic(Toolbox::STOMACHMUSIC)),
tempMusic2(Toolbox::getMusic(Toolbox::THROATMUSIC)),
tempMusic3(Toolbox::getMusic(Toolbox::HUBMUSIC)){
	initialize();
}

LevelMusic::~LevelMusic() {
	finalize();
}

LevelMusic& LevelMusic::getInstance() {
	static LevelMusic levelMusic;
	return levelMusic;
}

void LevelMusic::initialize() {
	/*tempMusic0.openFromFile(Toolbox::getMusic(Toolbox::STOMACHMUSIC));
	tempMusic1.openFromFile(Toolbox::getMusic(Toolbox::STOMACHAMBIENCE));
	tempMusic2.openFromFile(Toolbox::getMusic(Toolbox::THROATMUSIC));
	tempMusic3.openFromFile(Toolbox::getMusic(Toolbox::HUBMUSIC));*/

	mMusic.push_back(&tempMusic0);
	mMusic.push_back(&tempMusic1);
	mMusic.push_back(&tempMusic2);
	mMusic.push_back(&tempMusic3);

	mMusic[0]->setVolume(80);
	mMusic[0]->setLoop(true);

	mMusic[1]->setVolume(25);
	mMusic[1]->setLoop(true);

	mMusic[2]->setVolume(25);
	mMusic[2]->setLoop(true);

	mMusic[3]->setVolume(25);
	mMusic[3]->setLoop(true);
}

void LevelMusic::finalize() {
	stopAllMusic();
}

void LevelMusic::playMusic(MUSICTYPE type) {
	switch (type) {
	case LevelMusic::STOMACHMUSIC:
		if (tempMusic0.getStatus() != sf::Music::Playing)
			tempMusic0.play();
		break;
	case LevelMusic::STOMACHAMBIANCE:
		if (tempMusic1.getStatus() != sf::Music::Playing)
			tempMusic1.play();
		break;
	case LevelMusic::THROATMUSIC:
		if (tempMusic2.getStatus() != sf::Music::Playing)
			tempMusic2.play();
		break;
	case LevelMusic::HUBMUSIC:
		if (tempMusic3.getStatus() != sf::Music::Playing)
			tempMusic3.play();
		break;
	case LevelMusic::INTESTINEMUSIC:
		if (tempMusic3.getStatus() != sf::Music::Playing)
			tempMusic3.play();
		break;
	default:
		break;
	}
}

void LevelMusic::stopMusic(MUSICTYPE type) {
	switch (type) {
	case LevelMusic::STOMACHMUSIC:
		if (tempMusic0.getStatus() == sf::Music::Playing)
			tempMusic0.stop();
		break;
	case LevelMusic::STOMACHAMBIANCE:
		if (tempMusic1.getStatus() == sf::Music::Playing)
			tempMusic1.stop();
		break;
	case LevelMusic::THROATMUSIC:
		if (tempMusic2.getStatus() == sf::Music::Playing)
			tempMusic2.stop();
		break;
	case LevelMusic::HUBMUSIC:
		if (tempMusic3.getStatus() == sf::Music::Playing)
			tempMusic3.stop();
		break;
	case LevelMusic::INTESTINEMUSIC:
		if (tempMusic3.getStatus() == sf::Music::Playing)
			tempMusic3.stop();
		break;
	default:
		break;
	}
}

void LevelMusic::stopAllMusic() {
	/*for (MusicVector::size_type i = 0; i < mMusic.size(); i++) {
		mMusic[i].stop();
	}*/
	tempMusic0.stop();
	tempMusic1.stop();
	tempMusic2.stop();
	tempMusic3.stop();
}
