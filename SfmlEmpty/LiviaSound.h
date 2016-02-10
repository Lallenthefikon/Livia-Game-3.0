#pragma once

#include "SoundFX.h"

class LiviaSound : public SoundFX {
public:
	static SoundFX& createLiviaSound();
	virtual ~LiviaSound();
	virtual void playSound(SOUNDTYPE type);
	virtual void stopSound();
	virtual SOUNDTYPE getCurrentSound();
private:
	LiviaSound();
	sf::Sound mSound;
	sf::SoundBuffer mSoundBuffer;
	SOUNDTYPE mCurrentSound;
};

