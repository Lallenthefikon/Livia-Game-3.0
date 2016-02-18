#pragma once

#include <SFML\Audio.hpp>
#include <map>
#include "Toolbox.h"

class SoundFX {
public:
	enum SOUNDTYPE { RUNNING, JUMPING, LANDING, DAMAGED, IDLE, DEATH };
	typedef std::map<SOUNDTYPE, sf::Sound*> SoundQueue;
	SoundFX();
	virtual ~SoundFX();
	virtual void playSound(SOUNDTYPE type) = 0;
	virtual void stopSound(SOUNDTYPE type) = 0;
	virtual void stopAllSound() = 0;
};

