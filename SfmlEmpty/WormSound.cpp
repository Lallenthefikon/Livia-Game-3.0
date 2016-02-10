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

}

void WormSound::stopSound() {

}

SoundFX::SOUNDTYPE WormSound::getCurrentSound() {
	return mCurrentSound;
}