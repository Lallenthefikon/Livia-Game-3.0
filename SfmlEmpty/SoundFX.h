#pragma once

#include <SFML\Audio.hpp>
#include "Toolbox.h"

class SoundFX {
public:
	enum SOUNDTYPE { RUNNING, JUMPING, LANDING, DAMAGED, IDLE, RANDOM };
	SoundFX();
	virtual ~SoundFX();
	virtual void playSound(SOUNDTYPE type) = 0;
	virtual void stopSound() = 0;
	virtual SOUNDTYPE getCurrentSound() = 0;
};

