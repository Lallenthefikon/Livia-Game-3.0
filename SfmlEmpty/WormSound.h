#pragma once

#include "SoundFX.h"

class WormSound : public SoundFX {
public:
	static SoundFX& createWormSound();
	virtual ~WormSound();
	virtual void playSound(SOUNDTYPE type);
	virtual void stopSound();
private:
	WormSound();
	sf::Sound mSound;
	sf::SoundBuffer mSoundBuffer;
};

