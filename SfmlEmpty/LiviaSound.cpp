#include "LiviaSound.h"


LiviaSound::LiviaSound() {
	mSound.setVolume(25);
	mSoundExtra.setVolume(25);
}


LiviaSound::~LiviaSound() {
}

SoundFX& LiviaSound::createLiviaSound() {
	static LiviaSound liviaSound;
	return liviaSound;
}

void LiviaSound::playSound(SOUNDTYPE type) {
	if (mSound.getStatus() == sf::Sound::Status::Stopped) {
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
			mSound.setBuffer(Toolbox::getSound(Toolbox::SOUNDKEY::PLAYERDAMAGED));
			break;
		case SoundFX::IDLE:
			mSound.setBuffer(Toolbox::getSound(Toolbox::SOUNDKEY::PLAYERIDLE));
			break;
		case SoundFX::RANDOM:
			break;
		default:
			break;
		}
	}
	else {
		switch (type) {
		case SoundFX::RUNNING:
			mSoundExtra.setBuffer(Toolbox::getSound(Toolbox::SOUNDKEY::PLAYERRUN));
			break;
		case SoundFX::JUMPING:
			mSoundExtra.setBuffer(Toolbox::getSound(Toolbox::SOUNDKEY::PLAYERJUMP));
			break;
		case SoundFX::LANDING:
			break;
		case SoundFX::DAMAGED:
			mSoundExtra.setBuffer(Toolbox::getSound(Toolbox::SOUNDKEY::PLAYERDAMAGED));
			break;
		case SoundFX::IDLE:
			mSoundExtra.setBuffer(Toolbox::getSound(Toolbox::SOUNDKEY::PLAYERIDLE));
			break;
		case SoundFX::RANDOM:
			break;
		default:
			break;
		}
	}
	if (mSound.getStatus() == sf::Sound::Status::Stopped){
		mSound.play();
	}
	else {
		mSoundExtra.play();
	}
}

void LiviaSound::stopSound() {
	mSound.stop();
}
