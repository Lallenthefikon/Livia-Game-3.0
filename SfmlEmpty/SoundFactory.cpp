#include "SoundFactory.h"
#include "LiviaSound.h"
#include "WormSound.h"
#include "TummySound.h"
#include "DialogueSound.h"

SoundFX& SoundFactory::getLiviaSound() {
	return LiviaSound::createLiviaSound();
}

SoundFX& SoundFactory::getWormSound() {
	return WormSound::createWormSound();
}

SoundFX& SoundFactory::getTummySound() {
	return TummySound::createTummySound();
}

SoundFX& SoundFactory::getDialogueSound() {
	return DialogueSound::createDialogueSound();
}