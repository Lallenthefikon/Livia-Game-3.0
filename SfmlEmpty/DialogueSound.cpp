#include "DialogueSound.h"

DialogueSound::DialogueSound() :
	mSounds() {
	initialize();
}

DialogueSound::~DialogueSound() {
	finalize();
}

SoundFX& DialogueSound::createDialogueSound() {
	static DialogueSound dialogueSound;
	return dialogueSound;
}

void DialogueSound::initialize() {
	mSounds.insert({ SPEAKERLIVIA, new sf::Sound(Toolbox::getSound(Toolbox::SOUNDKEY::PLAYERDEATH)) });
	mSounds.insert({ SPEAKERMANSA, new sf::Sound(Toolbox::getSound(Toolbox::SOUNDKEY::PLAYERDAMAGED)) });
	mSounds.insert({ SPEAKERMUHNIN, new sf::Sound(Toolbox::getSound(Toolbox::SOUNDKEY::PLAYERFALLDEATH)) });
	mSounds.insert({ SPEAKERTUMMY, new sf::Sound(Toolbox::getSound(Toolbox::SOUNDKEY::PLAYERJUMP1)) });
}

void DialogueSound::finalize() {
	stopAllSound();
	for (auto i : mSounds) {
		delete i.second;
	}
}

void DialogueSound::playSound(SOUNDTYPE type) {
	switch (type) {
	case SoundFX::SPEAKERLIVIA:
		mSounds[SPEAKERLIVIA]->play();
		break;
	case SoundFX::SPEAKERTUMMY:
		mSounds[SPEAKERTUMMY]->play();
		break;
	case SoundFX::SPEAKERMANSA:
		mSounds[SPEAKERMANSA]->play();
		break;
	case SoundFX::SPEAKERMUHNIN:
		mSounds[SPEAKERMUHNIN]->play();
		break;
	default:
		break;
	}
}

void DialogueSound::stopSound(SOUNDTYPE type) {
	switch (type) {
	case SoundFX::SPEAKERLIVIA:
		mSounds[SPEAKERLIVIA]->stop();
		break;
	case SoundFX::SPEAKERTUMMY:
		mSounds[SPEAKERTUMMY]->stop();
		break;
	case SoundFX::SPEAKERMANSA:
		mSounds[SPEAKERMANSA]->stop();
		break;
	case SoundFX::SPEAKERMUHNIN:
		mSounds[SPEAKERMUHNIN]->stop();
		break;
	default:
		break;
	}
}

void DialogueSound::stopAllSound() {
	for (auto i : mSounds) {
		i.second->stop();
	}
}

void DialogueSound::updateSound(SOUNDTYPE type, float & volume) {
}
