#pragma once

#include <vector>
#include "Dialogue.h"

class Dialoguehandler {
public:
	typedef std::vector<Dialogue*> Dialogues;
	static Dialoguehandler& getInstance();


	void addDialogue(Dialogue* dialogue);
	void renderDialogue(sf::RenderWindow &window);
	void updateDialogue(const sf::Vector2f &pos);
	void clear();
	void setCurrentDialogue(size_t index);

	Dialogues& getDialogue() { return mDialogue; }
	~Dialoguehandler();
	bool isInDialogue = false;

private:
	
	Dialoguehandler();
	void internalClear();
	sf::Sprite mSpriteHudBackground;

	size_t currentDialouge;
	size_t page;

	Dialogues mDialogue;
};

