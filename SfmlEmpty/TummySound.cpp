#include "TummySound.h"



TummySound::TummySound() :
	mSounds() {
	initialize();
}

TummySound::~TummySound() {
	finalize();
}

SoundFX& TummySound::createTummySound() {
	static TummySound tummySound;
	return tummySound;
}

void TummySound::initialize() {
	mSounds.insert({ RUNNING, new sf::Sound(Toolbox::getSound(Toolbox::SOUNDKEY::TUMMYRUNNING)) });
}

void TummySound::finalize() {
	stopAllSound();
	for (auto i : mSounds) {
		delete i.second;
	}
}

void TummySound::playSound(SOUNDTYPE type) {
	switch (type) {
	case SoundFX::RUNNING:
		if (mSounds[RUNNING]->getStatus() != sf::Sound::Status::Playing)
			mSounds[RUNNING]->play();
		break;
	case SoundFX::JUMPING1:
		break;
	case SoundFX::JUMPING2:
		break;
	case SoundFX::JUMPING3:
		break;
	case SoundFX::LANDING:
		break;
	case SoundFX::DAMAGED:
		break;
	case SoundFX::IDLE:
		break;
	case SoundFX::DEATH:
		break;
	case SoundFX::FALLDEATH:
		break;
	case SoundFX::WALLSLIDE:
		break;
	default:
		break;
	}
}

void TummySound::stopSound(SOUNDTYPE type) {
	switch (type) {
	case SoundFX::RUNNING:
		if (mSounds[RUNNING]->getStatus() == sf::Sound::Status::Playing)
			mSounds[RUNNING]->stop();
		break;
	case SoundFX::JUMPING1:
		break;
	case SoundFX::JUMPING2:
		break;
	case SoundFX::JUMPING3:
		break;
	case SoundFX::LANDING:
		break;
	case SoundFX::DAMAGED:
		break;
	case SoundFX::IDLE:
		break;
	case SoundFX::DEATH:
		break;
	case SoundFX::FALLDEATH:
		break;
	case SoundFX::WALLSLIDE:
		break;
	default:
		break;
	}
}

void TummySound::updateSound(SoundFX::SOUNDTYPE type, float &volume) {
	mSounds[type]->setVolume(volume);
}

void TummySound::stopAllSound() {
}
