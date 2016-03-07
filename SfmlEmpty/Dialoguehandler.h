#pragma once

#include <vector>
#include <SFML\Graphics.hpp>
#include "Texthandler.h"

class Dialoguehandler {
public:
	enum CURRENTSPEAKER{LIVIA, MANSASOUL, TUMMY};

	typedef std::vector<std::string*> Strings;
	typedef std::vector<Strings*> StringVectors;
	static Dialoguehandler& getInstance();

	void renderDialogue(sf::RenderWindow &window);
	void updateDialogue(sf::Event &gEvent, sf::RenderWindow & window);
	void loadDialougehandler();
	void clear();
	void setCurrentDialogue(std::string filename);

	~Dialoguehandler();
	bool isInDialogue = false;

private:
	
	Dialoguehandler();
	void internalClear();
	void readFile();
	void setCurrentSpeaker(std::string &line);
	size_t currentDialouge;
	sf::Sprite mSpriteHudBackground;
	std::string mFilename;
	CURRENTSPEAKER mCurrentspeaker;
	int mIndex;
	StringVectors mStringVectors;

};

