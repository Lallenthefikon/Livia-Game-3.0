#include "GermSound.h"



GermSound::GermSound():
	mSounds() {
		initialize();
}


GermSound::~GermSound(){
	finalize();
}

SoundFX& GermSound::createGermSound() {
	static GermSound germSound;
	return germSound;
}

void GermSound::initialize() {
	mSounds.insert({ DEATH, new sf::Sound(Toolbox::getSound(Toolbox::SOUNDKEY::GERMDEATH)) });
}

void GermSound::finalize() {
	stopAllSound();
	for (auto i : mSounds) {
		delete i.second;
	}
}

void GermSound::playSound(SOUNDTYPE type) {
	switch (type) {
	case SoundFX::DEATH:
		if (mSounds[DEATH]->getStatus() != sf::Sound::Status::Playing)
			mSounds[DEATH]->play();
		break;
	}
}

void GermSound::stopSound(SOUNDTYPE type) {
	switch (type) {
	case SoundFX::DEATH:
		if (mSounds[DEATH]->getStatus() == sf::Sound::Status::Playing)
			mSounds[DEATH]->stop();
		break;
	}
}

void GermSound::updateSound(SoundFX::SOUNDTYPE type, float &volume) {
	mSounds[type]->setVolume(volume);
}

void GermSound::stopAllSound() {
	for (auto i : mSounds)
		i.second->stop();
}
