#include "WormSound.h"


WormSound::WormSound() :
mSounds() {
}


WormSound::~WormSound() {
}

SoundFX& WormSound::createWormSound() {
	static WormSound wormSound;
	return wormSound;
}

void WormSound::initialize() {

}

void WormSound::finalize() {

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
	case SoundFX::RANDOM:
		break;
	default:
		break;
	}
}

void WormSound::stopSound() {
	for (auto i : mSounds) {
		i.second->stop();
	}
}
