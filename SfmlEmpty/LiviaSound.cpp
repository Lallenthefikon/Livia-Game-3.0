#include "LiviaSound.h"


LiviaSound::LiviaSound() {
	mSound.setVolume(25);
	mSoundExtra.setVolume(50);
	/*mSound.setPitch(0.3);
	mSoundExtra.setPitch(0.3);*/
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
	else if (mSoundExtra.getStatus() == sf::Sound::Status::Stopped) {
		switch (type) {
		case SoundFX::RUNNING:
			mSoundExtra.setBuffer(Toolbox::getSoundExtra(Toolbox::SOUNDKEY::PLAYERRUN));
			break;
		case SoundFX::JUMPING:
			mSoundExtra.setBuffer(Toolbox::getSoundExtra(Toolbox::SOUNDKEY::PLAYERJUMP));
			break;
		case SoundFX::LANDING:
			break;
		case SoundFX::DAMAGED:
			mSoundExtra.setBuffer(Toolbox::getSoundExtra(Toolbox::SOUNDKEY::PLAYERDAMAGED));
			break;
		case SoundFX::IDLE:
			mSoundExtra.setBuffer(Toolbox::getSoundExtra(Toolbox::SOUNDKEY::PLAYERIDLE));
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
	else if (mSoundExtra.getStatus() == sf::Sound::Status::Stopped) {
		mSoundExtra.play();
	}
}

void LiviaSound::stopSound() {
	mSound.stop();
}
