#include "WormSound.h"


WormSound::WormSound() {
}


WormSound::~WormSound() {
}

SoundFX& WormSound::createWormSound() {
	static WormSound wormSound;
	return wormSound;
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

}
