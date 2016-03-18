#include "LiviaSound.h"
#include <iostream>

LiviaSound::LiviaSound() :
	mSounds() {
	initialize();
}

LiviaSound::~LiviaSound() {
	finalize();
}

SoundFX& LiviaSound::createLiviaSound() {
	static LiviaSound liviaSound;
	return liviaSound;
}

void LiviaSound::initialize() {
	mSounds.insert({ RUNNING, new sf::Sound(Toolbox::getSound(Toolbox::SOUNDKEY::PLAYERRUN)) });
	mSounds.insert({ JUMPING1, new sf::Sound(Toolbox::getSound(Toolbox::SOUNDKEY::PLAYERJUMP1)) });
	mSounds.insert({ JUMPING2, new sf::Sound(Toolbox::getSound(Toolbox::SOUNDKEY::PLAYERJUMP2)) });
	mSounds.insert({ JUMPING3, new sf::Sound(Toolbox::getSound(Toolbox::SOUNDKEY::PLAYERJUMP3)) });
	mSounds.insert({ DAMAGED, new sf::Sound(Toolbox::getSound(Toolbox::SOUNDKEY::PLAYERDAMAGED)) });
	mSounds.insert({ IDLE, new sf::Sound(Toolbox::getSound(Toolbox::SOUNDKEY::PLAYERIDLE)) });
	mSounds.insert({ DEATH, new sf::Sound(Toolbox::getSound(Toolbox::SOUNDKEY::PLAYERDEATH)) });
	mSounds.insert({ FALLDEATH, new sf::Sound(Toolbox::getSound(Toolbox::SOUNDKEY::PLAYERFALLDEATH)) });
	mSounds.insert({ WALLSLIDE, new sf::Sound(Toolbox::getSound(Toolbox::SOUNDKEY::PLAYERWALLSLIDE)) });
	mSounds.insert({ LANDING, new sf::Sound(Toolbox::getSound(Toolbox::SOUNDKEY::PLAYERLAND)) });
	mSounds.insert({ DROWN, new sf::Sound(Toolbox::getSound(Toolbox::SOUNDKEY::PLAYERDROWN)) });
	mSounds[RUNNING]->setLoop(true);
	mSounds[WALLSLIDE]->setLoop(true);

	mSounds[LANDING]->setVolume(15);
	mSounds[RUNNING]->setVolume(33);
	mSounds[JUMPING1]->setVolume(33);
	mSounds[JUMPING2]->setVolume(33);
	mSounds[JUMPING3]->setVolume(33);
	mSounds[DEATH]->setVolume(75);
	mSounds[DROWN]->setVolume(60);
}

void LiviaSound::finalize() {
	stopAllSound();
	for (auto i : mSounds) {
		delete i.second;
	}
}

void LiviaSound::playSound(SOUNDTYPE type) {
	switch (type) {
	case SoundFX::RUNNING:
		if (mSounds[RUNNING]->getStatus() != sf::Sound::Status::Playing)
			mSounds[RUNNING]->play();
		break;

	case SoundFX::JUMPING1:
		if (mSounds[JUMPING1]->getStatus() != sf::Sound::Status::Playing)
			mSounds[JUMPING1]->play();
		break;

	case SoundFX::JUMPING2:
		if (mSounds[JUMPING2]->getStatus() != sf::Sound::Status::Playing)
			mSounds[JUMPING2]->play();
		break;

	case SoundFX::JUMPING3:
		if (mSounds[JUMPING3]->getStatus() != sf::Sound::Status::Playing)
			mSounds[JUMPING3]->play();
		break;

	case SoundFX::LANDING:
		if (mSounds[LANDING]->getStatus() != sf::Sound::Status::Playing)
			mSounds[LANDING]->play();
		break;

	case SoundFX::DAMAGED:
		if (mSounds[DAMAGED]->getStatus() != sf::Sound::Status::Playing)
			mSounds[DAMAGED]->play();
		break;

	case SoundFX::IDLE:
		if (mSounds[IDLE]->getStatus() != sf::Sound::Status::Playing)
			mSounds[IDLE]->play();
		break;

	case SoundFX::DEATH:
		if (mSounds[DEATH]->getStatus() != sf::Sound::Status::Playing)
			mSounds[DEATH]->play();
		break;

	case SoundFX::FALLDEATH:
		if (mSounds[FALLDEATH]->getStatus() != sf::Sound::Status::Playing)
			mSounds[FALLDEATH]->play();
		break;

	case SoundFX::WALLSLIDE:
		if (mSounds[WALLSLIDE]->getStatus() != sf::Sound::Status::Playing)
			mSounds[WALLSLIDE]->play();
		break;

	case SoundFX::DROWN:
			mSounds[DROWN]->play();
		break;

	default:
		break;
	}
}

void LiviaSound::stopSound(SOUNDTYPE type) {
	switch (type) {
	case SoundFX::RUNNING:
		if (mSounds[RUNNING]->getStatus() == sf::Sound::Status::Playing)
			mSounds[RUNNING]->stop();
		break;

	case SoundFX::JUMPING1:
		if (mSounds[JUMPING1]->getStatus() == sf::Sound::Status::Playing)
			mSounds[JUMPING1]->stop();
		break;

	case SoundFX::JUMPING2:
		if (mSounds[JUMPING2]->getStatus() == sf::Sound::Status::Playing)
			mSounds[JUMPING2]->stop();
		break;

	case SoundFX::JUMPING3:
		if (mSounds[JUMPING3]->getStatus() == sf::Sound::Status::Playing)
			mSounds[JUMPING3]->stop();
		break;

	case SoundFX::LANDING:
		if (mSounds[LANDING]->getStatus() == sf::Sound::Status::Playing)
			mSounds[LANDING]->stop();
		break;

	case SoundFX::DAMAGED:
		if (mSounds[DAMAGED]->getStatus() == sf::Sound::Status::Playing)
			mSounds[DAMAGED]->stop();
		break;

	case SoundFX::IDLE:
		if (mSounds[IDLE]->getStatus() == sf::Sound::Status::Playing)
			mSounds[IDLE]->stop();
		break;

	case SoundFX::DEATH:
		if (mSounds[DEATH]->getStatus() == sf::Sound::Status::Playing)
			mSounds[DEATH]->stop();
		break;

	case SoundFX::WALLSLIDE:
		if (mSounds[WALLSLIDE]->getStatus() == sf::Sound::Status::Playing)
			mSounds[WALLSLIDE]->stop();
		break;

	case SoundFX::DROWN:
		if (mSounds[DROWN]->getStatus() == sf::Sound::Status::Playing)
			mSounds[DROWN]->stop();
		break;

	default:
		break;
	}
}

void LiviaSound::updateSound(SoundFX::SOUNDTYPE type, float &volume) {

}

void LiviaSound::stopAllSound() {
	for (auto i : mSounds) {
		i.second->stop();
	}
}

