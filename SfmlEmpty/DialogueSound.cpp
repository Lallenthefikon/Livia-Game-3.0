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
	mSounds.insert({ SPEAKERLIVIA1, new sf::Sound(Toolbox::getSound(Toolbox::SOUNDKEY::SPEAKERLIVIASOUND1)) });
	mSounds.insert({ SPEAKERLIVIA2, new sf::Sound(Toolbox::getSound(Toolbox::SOUNDKEY::SPEAKERLIVIASOUND2)) });
	mSounds.insert({ SPEAKERLIVIA3, new sf::Sound(Toolbox::getSound(Toolbox::SOUNDKEY::SPEAKERLIVIASOUND3)) });
	mSounds.insert({ SPEAKERLIVIA4, new sf::Sound(Toolbox::getSound(Toolbox::SOUNDKEY::SPEAKERLIVIASOUND4)) });
	mSounds.insert({ SPEAKERLIVIA5, new sf::Sound(Toolbox::getSound(Toolbox::SOUNDKEY::SPEAKERLIVIASOUND5)) });
	mSounds.insert({ SPEAKERMANSA1, new sf::Sound(Toolbox::getSound(Toolbox::SOUNDKEY::SPEAKERMANSASOUND1)) });
	mSounds.insert({ SPEAKERMANSA2, new sf::Sound(Toolbox::getSound(Toolbox::SOUNDKEY::SPEAKERMANSASOUND2)) });
	mSounds.insert({ SPEAKERMANSA3, new sf::Sound(Toolbox::getSound(Toolbox::SOUNDKEY::SPEAKERMANSASOUND3)) });
	mSounds.insert({ SPEAKERMANSA4, new sf::Sound(Toolbox::getSound(Toolbox::SOUNDKEY::SPEAKERMANSASOUND4)) });
	mSounds.insert({ SPEAKERMANSA5, new sf::Sound(Toolbox::getSound(Toolbox::SOUNDKEY::SPEAKERMANSASOUND5)) });
	mSounds.insert({ SPEAKERMANSA6, new sf::Sound(Toolbox::getSound(Toolbox::SOUNDKEY::SPEAKERMANSASOUND6)) });
	mSounds.insert({ SPEAKERMUHNIN1, new sf::Sound(Toolbox::getSound(Toolbox::SOUNDKEY::SPEAKERMHUININSOUND1)) });
	mSounds.insert({ SPEAKERMUHNIN2, new sf::Sound(Toolbox::getSound(Toolbox::SOUNDKEY::SPEAKERMHUININSOUND2)) });
	mSounds.insert({ SPEAKERMUHNIN3, new sf::Sound(Toolbox::getSound(Toolbox::SOUNDKEY::SPEAKERMHUININSOUND3)) });
	mSounds.insert({ SPEAKERTUMMY, new sf::Sound(Toolbox::getSound(Toolbox::SOUNDKEY::SPEAKERTUMMYSOUND)) });
}


      void DialogueSound::finalize() {
	stopAllSound();
	for (auto i : mSounds) {
		delete i.second;
	}
}

  void DialogueSound::playSound(SOUNDTYPE type) {
	switch (type) {
	case SoundFX::SPEAKERLIVIA1:
		mSounds[SPEAKERLIVIA1]->play();
		break;
	case SoundFX::SPEAKERLIVIA2:
		mSounds[SPEAKERLIVIA2]->play();
		break;
	case SoundFX::SPEAKERLIVIA3:
		mSounds[SPEAKERLIVIA3]->play();
		break;
	case SoundFX::SPEAKERLIVIA4:
		mSounds[SPEAKERLIVIA4]->play();
		break;
	case SoundFX::SPEAKERLIVIA5:
		mSounds[SPEAKERLIVIA5]->play();
		break;
	case SoundFX::SPEAKERTUMMY:
		mSounds[SPEAKERTUMMY]->play();
		break;
	case SoundFX::SPEAKERMANSA1:
		mSounds[SPEAKERMANSA1]->play();
		break;
	case SoundFX::SPEAKERMANSA2:
		mSounds[SPEAKERMANSA2]->play();
		break;
	case SoundFX::SPEAKERMANSA3:
		mSounds[SPEAKERMANSA3]->play();
		break;
	case SoundFX::SPEAKERMANSA4:
		mSounds[SPEAKERMANSA4]->play();
		break;
	case SoundFX::SPEAKERMANSA5:
		mSounds[SPEAKERMANSA5]->play();
		break;
	case SoundFX::SPEAKERMANSA6:
		mSounds[SPEAKERMANSA6]->play();
		break;
	case SoundFX::SPEAKERMUHNIN1:
		mSounds[SPEAKERMUHNIN1]->play();
		break;
	case SoundFX::SPEAKERMUHNIN2:
		mSounds[SPEAKERMUHNIN2]->play();
		break;
	case SoundFX::SPEAKERMUHNIN3:
		mSounds[SPEAKERMUHNIN3]->play();
		break;
	default:
		break;
	}
}

void DialogueSound::stopSound(SOUNDTYPE type) {
	switch (type) {
	case SoundFX::SPEAKERLIVIA1:
		mSounds[SPEAKERLIVIA1]->stop();
		break;
	case SoundFX::SPEAKERLIVIA2:
		mSounds[SPEAKERLIVIA2]->stop();
		break;
	case SoundFX::SPEAKERLIVIA3:
		mSounds[SPEAKERLIVIA3]->stop();
		break;
	case SoundFX::SPEAKERLIVIA4:
		mSounds[SPEAKERLIVIA4]->stop();
		break;
	case SoundFX::SPEAKERLIVIA5:
		mSounds[SPEAKERLIVIA5]->stop();
		break;
	case SoundFX::SPEAKERTUMMY:
		mSounds[SPEAKERTUMMY]->stop();
		break;
	case SoundFX::SPEAKERMANSA1:
		mSounds[SPEAKERMANSA1]->stop();
		break;
	case SoundFX::SPEAKERMANSA2:
		mSounds[SPEAKERMANSA2]->stop();
		break;
	case SoundFX::SPEAKERMANSA3:
		mSounds[SPEAKERMANSA3]->stop();
		break;
	case SoundFX::SPEAKERMANSA4:
		mSounds[SPEAKERMANSA4]->stop();
		break;
	case SoundFX::SPEAKERMANSA5:
		mSounds[SPEAKERMANSA5]->stop();
		break;
	case SoundFX::SPEAKERMUHNIN1:
		mSounds[SPEAKERMUHNIN1]->stop();
		break;
	case SoundFX::SPEAKERMUHNIN2:
		mSounds[SPEAKERMUHNIN2]->stop();
		break;
	case SoundFX::SPEAKERMUHNIN3:
		mSounds[SPEAKERMUHNIN3]->stop();
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
