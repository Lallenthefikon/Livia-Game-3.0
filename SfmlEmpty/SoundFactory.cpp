#include "SoundFactory.h"
#include "LiviaSound.h"
#include "WormSound.h"

SoundFX& SoundFactory::getLiviaSound() {
	return LiviaSound::createLiviaSound();
}

SoundFX& SoundFactory::getWormSound() {
	return WormSound::createWormSound();
}