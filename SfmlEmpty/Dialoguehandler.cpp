#include "Dialoguehandler.h"
#include <fstream>


Dialoguehandler::Dialoguehandler(){

}

Dialoguehandler::~Dialoguehandler(){
}

Dialoguehandler& Dialoguehandler::getInstance() {
	static Dialoguehandler dialogueHandler;
	return dialogueHandler;
}

void Dialoguehandler::renderDialogue(sf::RenderWindow & window){
	Texthandler::getInstance().renderDialougeText(window);
}


void Dialoguehandler::updateDialogue(sf::Event &gEvent, sf::RenderWindow & window) {
	while (window.pollEvent(gEvent)) {
		if (gEvent.type == sf::Event::KeyPressed) {
			if (gEvent.key.code == sf::Keyboard::BackSpace) {
				Texthandler::getInstance().setDialougeText(*mStringVectors[mIndex]->at(0), *mStringVectors[mIndex]->at(1), *mStringVectors[mIndex]->at(2));
				mIndex++;
				if (mIndex >= mStringVectors.size()) {
					isInDialogue = false;
				}
			}
		}
	}
	///*printf((std::to_string(pos.x) + " " + std::to_string(pos.y) + "\n").data());*/
	//bool found = false;
	//for (size_t i = 0; i < mDialogue.size(); i++) {
	//	/*printf("lol\n");*/
	//	if (mDialogue[i]->bounds.contains(pos)) {
	//		found = true;
	//		if (!isInDialogue) {
	//			// Player triggered a dialogue
	//			isInDialogue = true;
	//			mDialogue[i]->setIsInDialogue(true);
	//			current = i;
	//			page = 0;
	//			break;
	//		}
	//	}
	//}
	//if (!found) {
	//	isInDialogue = false;
	//}
	
}

void Dialoguehandler::loadDialougehandler(){
	
}

void Dialoguehandler::clear(){
	Dialoguehandler::internalClear();
}

void Dialoguehandler::setCurrentDialogue(std::string filename){
	Dialoguehandler::internalClear();
	isInDialogue = true;
	mIndex = 1;
	mFilename = filename;
	Dialoguehandler::readFile();
	Texthandler::getInstance().setDialougeText(*mStringVectors[0]->at(0), *mStringVectors[0]->at(1), *mStringVectors[0]->at(2));
}

void Dialoguehandler::internalClear() {
	while (!mStringVectors.empty()) {
		while (!mStringVectors.back()->empty()) {
			delete mStringVectors.back()->back();
			mStringVectors.back()->pop_back();
		}
		delete mStringVectors.back();
		mStringVectors.pop_back();
	}
}

void Dialoguehandler::readFile(){
	int index(0);
	std::string line;
	std::ifstream dialougefile(mFilename);
	if (dialougefile.is_open()) {
		while (getline(dialougefile, line)) {
			if (index == 0) {
				Dialoguehandler::setCurrentSpeaker(line);
				mStringVectors.push_back(new Strings);
			}
			else if (index < 4) {
				mStringVectors.back()->push_back(new std::string(line));
			}
			index++;
			if (index > 3)
				index = 0;
		}
	}
	dialougefile.close();

}

void Dialoguehandler::setCurrentSpeaker(std::string &line){
	switch (line[0]) {
	case 'M':
		if (line[1] == 'S') {
			mCurrentspeaker = MANSASOUL;
		}
		break;
	case 'L':
		if (line[1] == 'I')
			mCurrentspeaker = LIVIA;
		break;
	default:
		break;
	}
}
