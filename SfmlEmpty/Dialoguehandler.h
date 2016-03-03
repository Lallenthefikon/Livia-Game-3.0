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

	Dialogues& getDialogue() { return mDialogue; }
	~Dialoguehandler();
private:
	Dialoguehandler();
	void internalClear();
	size_t current;
	size_t page;
	bool isInDialogue = false;
	Dialogues mDialogue;
};

