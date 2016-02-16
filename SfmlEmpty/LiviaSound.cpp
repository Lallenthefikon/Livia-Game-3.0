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
}

void LiviaSound::finalize() {
	for (auto i = mSounds.begin(); i != mSounds.end(); i++) {
		delete i->second;
	}
}

void LiviaSound::playSound(SOUNDTYPE type) {
	switch (type) {
	case SoundFX::RUNNING:
		if (mSounds[RUNNING]->getStatus() != sf::Sound::Status::Playing) {
			mSounds[RUNNING]->play();
		}
		break;

	case SoundFX::JUMPING:
		if (mSounds[JUMPING]->getStatus() != sf::Sound::Status::Playing) {
			mSounds[JUMPING]->play();
		}
		break;

	case SoundFX::LANDING:
		break;

	case SoundFX::DAMAGED:
		if (mSounds[DAMAGED]->getStatus() != sf::Sound::Status::Playing) {
			mSounds[DAMAGED]->play();
		}
		break;

	case SoundFX::IDLE:
		if (mSounds[IDLE]->getStatus() != sf::Sound::Status::Playing) {
			mSounds[IDLE]->play();
		}
		break;

	case SoundFX::RANDOM:
		break;

	default:
		break;
	}
}

void LiviaSound::stopSound() {
	for (auto i : mSounds) {
		i.second->stop();
	}
}