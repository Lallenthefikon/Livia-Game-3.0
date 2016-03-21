#pragma once

#include "Toolbox.h"
#include <SFML\Audio.hpp>

class LevelMusic {
public:
	enum MUSICTYPE { STOMACHMUSIC, STOMACHAMBIANCE, THROATMUSIC, HUBMUSIC, MOUTHMUSIC, INTESTINEMUSIC };
	typedef std::vector<sf::Music*> MusicVector;
	static LevelMusic& getInstance();
	virtual ~LevelMusic();
	virtual void playMusic(MUSICTYPE type);
	virtual void stopMusic(MUSICTYPE type);
	virtual void stopAllMusic();
private:
	LevelMusic();
	void initialize();
	void finalize();
	MusicVector mMusic;
	sf::Music& stomachAmbience;
	sf::Music& stomachMusic;
	sf::Music& throatMusic;
	sf::Music& hubMusic;
	sf::Music& mouthMusic;
	sf::Music& intestineMusic;
};

