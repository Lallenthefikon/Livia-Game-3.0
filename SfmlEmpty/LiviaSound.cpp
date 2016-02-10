#include "LiviaSound.h"


LiviaSound::LiviaSound() {
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
		mSound.setBuffer(Toolbox::getSound(Toolbox::SOUNDKEY::PLAYERRUN));
		break;
	case SoundFX::JUMPING:
		mSound.setBuffer(Toolbox::getSound(Toolbox::SOUNDKEY::PLAYERJUMP));
		break;
	case SoundFX::LANDING:
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
	mSound.play();
}

void LiviaSound::stopSound() {

}

SoundFX::SOUNDTYPE LiviaSound::getCurrentSound() {
	return mCurrentSound;
}