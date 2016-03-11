#pragma once

#include <vector>
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include "Toolbox.h"
#include "Texthandler.h"
#include "Animations.h"


class Dialoguehandler {
public:
	enum CURRENTSPEAKER{LIVIA, MANSASOUL, TUMMY};

	typedef std::vector<std::string*> Strings;
	typedef std::vector<Strings*> StringVectors;
	static Dialoguehandler& getInstance();

	void renderDialogue(sf::RenderWindow &window);
	void updateDialogue();
	void loadDialougehandler(char level);
	void clear();
	void setCurrentDialogue(std::string filename);

	~Dialoguehandler();
	bool isInDialogue = false;

private:
	
	Dialoguehandler();
	void internalClear();
	void readFile();
	void setCurrentSpeaker(std::string &line);
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
	int mAnimationIndex;
	Animations::Textures* mDialogueAnimationRight;
	Animations::Textures* mDialogueAnimationLeft;
	sf::Sprite mDialoguespriteLeft;
	sf::Sprite mDialoguespriteRight;

};

