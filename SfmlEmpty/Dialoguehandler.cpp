#include "Dialoguehandler.h"

Dialoguehandler::Dialoguehandler(){
	/*Dialogue* d = Dialogue::createDialogue(sf::Vector2f (100,100));
	d->bounds
	d->pages.push_back("asdlkjasd\n");
	mDialogue.push_back(d);
*/
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
	for (size_t i = 0; i < mDialogue.size(); i++){
		mDialogue[i]->render(window);
		//if (isInDialogue) {
	
		//	/*printf(mDialogue[current]->pages[page].data());*/
		//}
	}
}

void Dialoguehandler::updateDialogue(const sf::Vector2f & pos){
	/*printf((std::to_string(pos.x) + " " + std::to_string(pos.y) + "\n").data());*/
	bool found = false;
	for (size_t i = 0; i < mDialogue.size(); i++) {
		printf("lol\n");
		if (mDialogue[i]->bounds.contains(pos)) {
			found = true;
			if (!isInDialogue) {
				// Player triggered a dialogue
				isInDialogue = true;
				mDialogue[i]->setIsInDialogue(true);
				current = i;
				page = 0;
				break;
			}
		}
	}
	if (!found) {
		isInDialogue = false;
	}
}

void Dialoguehandler::clear(){
	Dialoguehandler::internalClear();
}

void Dialoguehandler::internalClear() {
	//while (!mDialogue.empty()) {
	//	delete mDialogue.back();
	//	mDialogue.pop_back();
	//}
}
