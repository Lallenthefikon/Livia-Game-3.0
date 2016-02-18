#pragma once

#include "SoundFX.h"

class LiviaSound : public SoundFX {
public:
	static SoundFX& createLiviaSound();
	virtual ~LiviaSound();
	virtual void playSound(SOUNDTYPE type);
	virtual void stopSound(SOUNDTYPE type);
	virtual void stopAllSound();
private:
	LiviaSound();
	void initialize();
	void finalize();
	SoundQueue mSounds;
};

