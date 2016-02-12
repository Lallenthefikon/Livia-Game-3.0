#pragma once

#include "SoundFX.h"

class LiviaSound : public SoundFX {
public:
	static SoundFX& createLiviaSound();
	virtual ~LiviaSound();
	virtual void playSound(SOUNDTYPE type);
	virtual void stopSound();
private:
	LiviaSound();
	sf::Sound mSound,
		mSoundExtra;
	sf::SoundBuffer mSoundBuffer;
};

