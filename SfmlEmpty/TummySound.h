#pragma once

#include "SoundFX.h"

class TummySound : public SoundFX {
public:
	virtual ~TummySound();
	static SoundFX& createTummySound();
	virtual void playSound(SOUNDTYPE type);
	virtual void stopSound(SOUNDTYPE type);
	virtual void stopAllSound();
	virtual void updateSound(SOUNDTYPE type, float &volume);
private:
	TummySound();
	void initialize();
	void finalize();
	SoundQueue mSounds;
};

