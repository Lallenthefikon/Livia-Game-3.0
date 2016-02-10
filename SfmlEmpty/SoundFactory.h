#pragma once

class SoundFX;

struct SoundFactory {
	static SoundFX& getLiviaSound();
	static SoundFX& getWormSound();
};
