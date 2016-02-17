#include "LiviaSound.h"
#include <iostream>


LiviaSound::LiviaSound() :
mSounds(){
}


LiviaSound::~LiviaSound() {
	stopSound();
	clearSoundQueue();
}

SoundFX& LiviaSound::createLiviaSound() {
	static LiviaSound liviaSound;
	return liviaSound;
}

void LiviaSound::playSound(SOUNDTYPE type) {

	SoundQueue::iterator lastInserted;
	sf::Sound *tempSound;

	switch (type) {
	case SoundFX::RUNNING:
		tempSound = new sf::Sound(Toolbox::getSound(Toolbox::SOUNDKEY::PLAYERRUN));
		lastInserted = mSounds.insert({ RUNNING, tempSound }).first;
		if (!lastInserted->second) {
			delete tempSound;
		}
		break;

	case SoundFX::JUMPING:
		tempSound = new sf::Sound(Toolbox::getSound(Toolbox::SOUNDKEY::PLAYERJUMP));
		lastInserted = mSounds.insert({ JUMPING, tempSound }).first;
		if (!lastInserted->second) {
			delete tempSound;
		}
		break;

	case SoundFX::LANDING:
		break;

	case SoundFX::DAMAGED:
		tempSound = new sf::Sound(Toolbox::getSound(Toolbox::SOUNDKEY::PLAYERDAMAGED));
		lastInserted = mSounds.insert({ DAMAGED, tempSound }).first;
		if (!lastInserted->second) {
			delete tempSound;
		}
		break;

	case SoundFX::IDLE:
		tempSound = new sf::Sound(Toolbox::getSound(Toolbox::SOUNDKEY::PLAYERIDLE));
		lastInserted = mSounds.insert({ IDLE, tempSound }).first;
		if (!lastInserted->second) {
			delete tempSound;
		}
		break;

	case SoundFX::RANDOM:
		break;

	default:
		break;
	}

	if (lastInserted->second->getStatus() != sf::Sound::Status::Playing) {
		lastInserted->second->play();
	}

	std::cout << mSounds.size() << std::endl;

	removeStopped();
}

void LiviaSound::removeStopped() {
	/*if (!mSounds.empty()) {
		for (SoundQueue::size_type i = 0; i < mSounds.size(); i++) {
			
			if (mSounds[i]->getStatus() == sf::Sound::Status::Playing)
				std::cout << "Playing" << std::endl;
			if (mSounds[i]->getStatus() == sf::Sound::Status::Paused)
				std::cout << "Paused" << std::endl;
			if (mSounds[i]->getStatus() == sf::Sound::Status::Stopped)
				std::cout << "Stopped" << std::endl;

			if (mSounds[i]->getStatus() == sf::Sound::Status::Stopped) {
				delete mSounds[i];
				mSounds.erase(mSounds.begin() + i);
			}
		}
	}*/
	for (SoundQueue::iterator i = mSounds.begin(); i != mSounds.end();) {
		if (i->second->getStatus() != sf::Sound::Status::Playing) {
			mSounds.erase(i++);
		}
		else
			++i;
	}
}

void LiviaSound::stopSound() {
	for (SoundQueue::iterator i = mSounds.begin(); i != mSounds.end(); ++i) {
		i->second->stop();
	}
}

void LiviaSound::clearSoundQueue() {
	while (!mSounds.empty()) {
		delete mSounds.end()->second;
		mSounds.erase(mSounds.end());
	}
	mSounds.clear();
}