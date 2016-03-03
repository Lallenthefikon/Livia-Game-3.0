#include "Dialoguehandler.h"

Dialoguehandler::Dialoguehandler(){
}

Dialoguehandler::~Dialoguehandler(){
}

Dialoguehandler& Dialoguehandler::getInstance() {
	static Dialoguehandler dialogueHandler;
	return dialogueHandler;
}

void Dialoguehandler::addDialogue(Dialogue* dialogue){
	mDialogue.push_back(dialogue);
}

void Dialoguehandler::renderDialogue(sf::RenderWindow & window){
	for (auto i : mDialogue) {
		i->render(window);
	}
}

void Dialoguehandler::updateDialogue(){
	for (auto i : mDialogue) {
		i->update();
	}
}

void Dialoguehandler::clear(){
	Dialoguehandler::internalClear();
}

void Dialoguehandler::internalClear() {
	while (!mDialogue.empty()) {
		delete mDialogue.back();
		mDialogue.pop_back();
	}
}
