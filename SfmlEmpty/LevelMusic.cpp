#include "LevelMusic.h"


LevelMusic::LevelMusic() : 
	stomachAmbience(Toolbox::getMusic(Toolbox::STOMACHAMBIENCE)),
	stomachMusic(Toolbox::getMusic(Toolbox::STOMACHMUSIC)),
	throatMusic(Toolbox::getMusic(Toolbox::THROATMUSIC)),
	hubMusic(Toolbox::getMusic(Toolbox::HUBMUSIC)),
	mouthMusic(Toolbox::getMusic(Toolbox::MOUTHMUSIC)),
	intestineMusic(Toolbox::getMusic(Toolbox::INTESTINEMUSIC)){
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

	mMusic.push_back(&stomachAmbience);
	mMusic.push_back(&stomachMusic);
	mMusic.push_back(&throatMusic);
	mMusic.push_back(&hubMusic);
	mMusic.push_back(&mouthMusic);
	mMusic.push_back(&intestineMusic);

	mMusic[0]->setVolume(80);
	mMusic[0]->setLoop(true);

	mMusic[1]->setVolume(25);
	mMusic[1]->setLoop(true);

	mMusic[2]->setVolume(25);
	mMusic[2]->setLoop(true);

	mMusic[3]->setVolume(25);
	mMusic[3]->setLoop(true);
	
	mMusic[4]->setVolume(25);
	mMusic[4]->setLoop(true);

	mMusic[5]->setVolume(25);
	mMusic[5]->setLoop(true);
}

void LevelMusic::finalize() {
	stopAllMusic();
}

void LevelMusic::playMusic(MUSICTYPE type) {
	switch (type) {
	case LevelMusic::STOMACHAMBIANCE:
		if (mMusic[0]->getStatus() != sf::Music::Playing)
			mMusic[0]->play();
		break;
	case LevelMusic::STOMACHMUSIC :
		if (mMusic[1]->getStatus() != sf::Music::Playing)
			mMusic[1]->play();
		break;
	case LevelMusic::THROATMUSIC:
		if (mMusic[2]->getStatus() != sf::Music::Playing)
			mMusic[2]->play();
		break;
	case LevelMusic::HUBMUSIC:
		if (mMusic[3]->getStatus() != sf::Music::Playing)
			mMusic[3]->play();
		break;
	case LevelMusic::MOUTHMUSIC:
		if (mMusic[4]->getStatus() != sf::Music::Playing)
			mMusic[4]->play();
		break;
	case LevelMusic::INTESTINEMUSIC:
		if (mMusic[5]->getStatus() != sf::Music::Playing)
			mMusic[5]->play();
		break;
	default:
		break;
	}
}

void LevelMusic::stopMusic(MUSICTYPE type) {
	switch (type) {
	case LevelMusic::STOMACHAMBIANCE:
		if (mMusic[0]->getStatus() == sf::Music::Playing)
			mMusic[0]->stop();
		break;
	case LevelMusic::STOMACHMUSIC:
		if (mMusic[1]->getStatus() == sf::Music::Playing)
			mMusic[1]->stop();
		break;
	case LevelMusic::THROATMUSIC:
		if (mMusic[2]->getStatus() == sf::Music::Playing)
			mMusic[2]->stop();
		break;
	case LevelMusic::HUBMUSIC:
		if (mMusic[3]->getStatus() == sf::Music::Playing)
			mMusic[3]->stop();
		break;
	case LevelMusic::MOUTHMUSIC:
		if (mMusic[4]->getStatus() == sf::Music::Playing)
			mMusic[4]->stop();
		break;
	case LevelMusic::INTESTINEMUSIC:
		if (mMusic[5]->getStatus() == sf::Music::Playing)
			mMusic[5]->stop();
		break;
	default:
		break;
	}
}

void LevelMusic::stopAllMusic() {
	/*for (auto i : mMusic)
		i->stop();*/
	for (MusicVector::size_type i = 0; i < mMusic.size(); i++) {
		mMusic[i]->stop();
	}
}
