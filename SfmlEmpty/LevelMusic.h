#pragma once

#include "Toolbox.h"
#include <SFML\Audio.hpp>

class LevelMusic {
public:
	enum MUSICTYPE { STOMACHMUSIC, STOMACHAMBIANCE, THROATMUSIC, HUBMUSIC, INTESTINEMUSIC };
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
	sf::Music& tempMusic0;
	sf::Music& tempMusic1;
	sf::Music& tempMusic2;
	sf::Music& tempMusic3;
};

