#pragma once

#include <SFML\Audio.hpp>
#include <map>
#include "Toolbox.h"

class SoundFX {
public:
	enum SOUNDTYPE {
		RUNNING, JUMPING1, JUMPING2, JUMPING3,
		LANDING, DAMAGED, IDLE, DEATH,
		FALLDEATH, DROWN, WALLSLIDE,
		SPEAKERLIVIA, SPEAKERTUMMY, SPEAKERMANSA, SPEAKERMUHNIN
	};
	typedef std::map<SOUNDTYPE, sf::Sound*> SoundQueue;
	SoundFX();
	virtual ~SoundFX();
	virtual void playSound(SOUNDTYPE type) = 0;
	virtual void stopSound(SOUNDTYPE type) = 0;
	virtual void stopAllSound() = 0;
	virtual void updateSound(SOUNDTYPE type, float &volume) = 0;
};

