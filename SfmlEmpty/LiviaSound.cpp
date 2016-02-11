#include "LiviaSound.h"


LiviaSound::LiviaSound() {
	mSound.setVolume(25);
}


LiviaSound::~LiviaSound() {
}

SoundFX& LiviaSound::createLiviaSound() {
	static LiviaSound liviaSound;
	return liviaSound;
}

void LiviaSound::playSound(SOUNDTYPE type) {
	switch (type) {
	case SoundFX::RUNNING:
		break;
	case SoundFX::JUMPING:
		mSound.setBuffer(Toolbox::getSound(Toolbox::SOUNDKEY::PLAYERJUMP));
		break;
	case SoundFX::LANDING:
		mSound.setBuffer(Toolbox::getSound(Toolbox::SOUNDKEY::PLAYERRUN));
		break;
	case SoundFX::DAMAGED:
		break;
	case SoundFX::IDLE:
		mSound.setBuffer(Toolbox::getSound(Toolbox::SOUNDKEY::PLAYERIDLE));
		break;
	case SoundFX::RANDOM:
		break;
	default:
		break;
	}
//	if (mSound.getPlayingOffset().asMilliseconds() < mSound.getBuffer()->getDuration().asMilliseconds())
	mSound.play();
}

void LiviaSound::stopSound() {

}
