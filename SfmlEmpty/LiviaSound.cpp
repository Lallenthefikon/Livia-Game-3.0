#include "LiviaSound.h"
#include <iostream>

LiviaSound::LiviaSound() :
mSounds(){
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
	mSounds.insert({ JUMPING, new sf::Sound(Toolbox::getSound(Toolbox::SOUNDKEY::PLAYERJUMP)) });
	mSounds.insert({ DAMAGED, new sf::Sound(Toolbox::getSound(Toolbox::SOUNDKEY::PLAYERDAMAGED)) });
	mSounds.insert({ IDLE, new sf::Sound(Toolbox::getSound(Toolbox::SOUNDKEY::PLAYERIDLE)) });
	mSounds.insert({ DEATH, new sf::Sound(Toolbox::getSound(Toolbox::SOUNDKEY::PLAYERDEATH)) });
	mSounds.insert({ WALLSLIDE, new sf::Sound(Toolbox::getSound(Toolbox::SOUNDKEY::PLAYERWALLSLIDE)) });
	mSounds.insert({ LANDING, new sf::Sound(Toolbox::getSound(Toolbox::SOUNDKEY::PLAYERLAND)) });
	mSounds[RUNNING]->setLoop(true);
	mSounds[WALLSLIDE]->setLoop(true);
	
	mSounds[LANDING]->setVolume(15);
	mSounds[RUNNING]->setVolume(33);
	mSounds[JUMPING]->setVolume(33);
	mSounds[DEATH]->setVolume(75);
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

	case SoundFX::JUMPING:
		if (mSounds[JUMPING]->getStatus() != sf::Sound::Status::Playing)
			mSounds[JUMPING]->play();
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

	case SoundFX::WALLSLIDE:
		if (mSounds[WALLSLIDE]->getStatus() != sf::Sound::Status::Playing)
			mSounds[WALLSLIDE]->play();
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

	case SoundFX::JUMPING:
		if (mSounds[JUMPING]->getStatus() == sf::Sound::Status::Playing)
			mSounds[JUMPING]->stop();
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

	default:
		break;
	}
}

void LiviaSound::stopAllSound() {
	for (auto i : mSounds) {
		i.second->stop();
	}
}

