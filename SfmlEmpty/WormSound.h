#pragma once

#include "SoundFX.h"

class WormSound : public SoundFX {
public:
	static SoundFX& createWormSound();
	virtual ~WormSound();
	virtual void playSound(SOUNDTYPE type);
	virtual void stopSound(SOUNDTYPE type);
	virtual void stopAllSound();
	virtual void updateSound(SOUNDTYPE type, float &volume);
private:
	WormSound();
	void initialize();
	void finalize();
	SoundQueue mSounds;
};