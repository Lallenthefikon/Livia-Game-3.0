#pragma once

#include "SoundFX.h"

class LiviaSound : public SoundFX {
public:
	static SoundFX& createLiviaSound();
	virtual ~LiviaSound();
	virtual void playSound(SOUNDTYPE type);
	virtual void stopSound();
	virtual void clearSoundQueue();
private:
	LiviaSound();
	void removeStopped();
	sf::Sound mSound;
	sf::SoundBuffer mSoundBuffer;
	SoundQueue mSounds;
};

