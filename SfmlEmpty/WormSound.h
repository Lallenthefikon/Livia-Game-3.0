#pragma once

#include "SoundFX.h"

class WormSound : public SoundFX {
public:
	static SoundFX& createWormSound();
	virtual ~WormSound();
	virtual void playSound(SOUNDTYPE type);
	virtual void stopSound(SOUNDTYPE type);
	virtual void stopAllSound();
private:
	WormSound();
	void initialize();
	void finalize();
	SoundQueue mSounds;
};