#pragma once

#include "SoundFX.h"

class LiviaSound : public SoundFX {
public:
	static SoundFX& createLiviaSound();
	virtual ~LiviaSound();
	virtual void playSound(SOUNDTYPE type);
	virtual void stopSound(SOUNDTYPE type);
	virtual void stopAllSound();
	virtual void updateSound(SOUNDTYPE type, float &volume);
private:
	LiviaSound();
	void initialize();
	void finalize();
	SoundQueue mSounds;
};

