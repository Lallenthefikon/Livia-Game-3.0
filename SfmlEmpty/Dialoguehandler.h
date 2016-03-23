#pragma once

#include <vector>
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include "Toolbox.h"
#include "Texthandler.h"
#include "Animations.h"
#include "SoundFX.h"
#include "SoundFactory.h"

class Dialoguehandler {
public:
	enum CURRENTSPEAKER{LIVIA, MANSASOUL, TUMMY, MUHNIN, INSTRUCTIONS};

	typedef std::vector<std::string*> Strings;
	typedef std::vector<Strings*> StringVectors;
	static Dialoguehandler& getInstance();

	void renderDialogue(sf::RenderWindow &window);
	void updateDialogue();
	void loadDialougehandler(char level);
	void clear();
	void setCurrentDialogue(std::string filename);
	std::string getFilename() { return mFilename; }

	~Dialoguehandler();
	bool isInDialogue = false;

private:
	
	Dialoguehandler();
	void internalClear();
	void readFile();
	void setCurrentSpeaker(std::string &line);
	void playSpeakerSound(CURRENTSPEAKER speaker, int ID);
	void loadTexture(char level);
	void animate();
	size_t currentDialouge;
	sf::Sprite mSpriteHudBackground;
	sf::Texture mTexture;
	std::string mFilename;
	CURRENTSPEAKER mCurrentspeaker;
	int mIndex;
	StringVectors mStringVectors;
	bool mReturnRealesed;
	float mTimer;
	int mAnimationIndexLeft;
	int mAnimationIndexRight;
	Animations::Textures* mDialogueAnimationRight;
	Animations::Textures* mDialogueAnimationLeft;
	sf::Sprite mDialoguespriteLeft;
	sf::Sprite mDialoguespriteRight;
	bool mLeftActive = true;
	Strings mSpeakers;
	int mSpeakerID;

	SoundFX& mSoundFX;
};

