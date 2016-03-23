#pragma once

#include "SoundFX.h"

class GermSound : public SoundFX{
public:
	virtual ~GermSound();
	static SoundFX& createGermSound();
	virtual void playSound(SOUNDTYPE type);
	virtual void stopSound(SOUNDTYPE type);
	virtual void stopAllSound();
	virtual void updateSound(SOUNDTYPE type, float &volume);
private:
	GermSound();
	void initialize();
	void finalize();
	SoundQueue mSounds;
};

