#include "WormSound.h"

WormSound::WormSound() :
mSounds() {
	initialize();
}

WormSound::~WormSound() {
	finalize();
}

SoundFX& WormSound::createWormSound() {
	static WormSound wormSound;
	return wormSound;
}

void WormSound::initialize() {
	mSounds.insert({ DEATH, new sf::Sound(Toolbox::getSound(Toolbox::SOUNDKEY::WORMDEATH)) });
}

void WormSound::finalize() {
	stopAllSound();
	for (auto i : mSounds) {
		delete i.second;
	}
}

void WormSound::playSound(SOUNDTYPE type) {
	switch (type) {
	case SoundFX::RUNNING:
		break;
	case SoundFX::JUMPING:
		break;
	case SoundFX::LANDING:
		break;
	case SoundFX::DAMAGED:
		break;
	case SoundFX::IDLE:
		break;
	case SoundFX::DEATH:
		if (mSounds[DEATH]->getStatus() != sf::Sound::Status::Playing)
			mSounds[DEATH]->play();
		break;
	default:
		break;
	}
}

void WormSound::stopAllSound() {
	for (auto i : mSounds) {
		i.second->stop();
	}
}

void WormSound::stopSound(SOUNDTYPE type) {
	switch (type) {
	case SoundFX::RUNNING:
		break;
	case SoundFX::JUMPING:
		break;
	case SoundFX::LANDING:
		break;
	case SoundFX::DAMAGED:
		break;
	case SoundFX::IDLE:
		break;
	case SoundFX::DEATH:
		if (mSounds[DEATH]->getStatus() == sf::Sound::Status::Playing)
			mSounds[DEATH]->stop();
		break;
	default:
		break;
	}
}
