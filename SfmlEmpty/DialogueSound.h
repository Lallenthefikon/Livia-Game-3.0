#pragma once

#include "SoundFX.h"

class DialogueSound : public SoundFX {
public:
	static SoundFX& createDialogueSound();
	virtual ~DialogueSound();
	virtual void playSound(SOUNDTYPE type);
	virtual void stopSound(SOUNDTYPE type);
	virtual void stopAllSound();
	virtual void updateSound(SOUNDTYPE type, float &volume);
private:
	DialogueSound();
	void initialize();
	void finalize();
	SoundQueue mSounds;
};

