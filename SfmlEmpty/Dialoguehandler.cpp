#include "Dialoguehandler.h"
#include <fstream>
#include <iostream>

static float ANIFramesPerFrame;

Dialoguehandler::Dialoguehandler(){
}

Dialoguehandler::~Dialoguehandler(){
}

Dialoguehandler& Dialoguehandler::getInstance() {
	static Dialoguehandler dialogueHandler;
	return dialogueHandler;
}

void Dialoguehandler::renderDialogue(sf::RenderWindow & window){
	window.draw(mSpriteHudBackground);
	if(mLeftActive)
		window.draw(mDialoguespriteLeft);
	else
		window.draw(mDialoguespriteRight);
	Texthandler::getInstance().renderDialougeText(window);
}


void Dialoguehandler::updateDialogue() {
	animate();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
		if (mReturnRealesed) {
			mIndex++;
			if (mIndex >= mStringVectors.size()) {
				isInDialogue = false;
			}

			else {
				Dialoguehandler::setCurrentSpeaker(*speakers.at(mIndex));
				Texthandler::getInstance().setDialougeText(*mStringVectors[mIndex]->at(0), *mStringVectors[mIndex]->at(1), *mStringVectors[mIndex]->at(2));
			}
			mReturnRealesed = false;
		}
	}
	else {
		mReturnRealesed = true;
	}
	mTimer += 0.5;
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

void Dialoguehandler::loadDialougehandler(char level){
	mReturnRealesed = true;
	Dialoguehandler::loadTexture(level);
	mSpriteHudBackground.setTexture(mTexture);
	mSpriteHudBackground.setScale(1.5, 1.4);
	mSpriteHudBackground.setPosition((Toolbox::getWindowSize().x / 2) - (mSpriteHudBackground.getGlobalBounds().width / 2), Toolbox::getWindowSize().y - mSpriteHudBackground.getGlobalBounds().height - 30);
	mDialoguespriteLeft.setPosition(mSpriteHudBackground.getPosition());
	mDialoguespriteRight.setPosition(sf::Vector2f(mSpriteHudBackground.getPosition().x + mSpriteHudBackground.getGlobalBounds().width - mDialoguespriteRight.getGlobalBounds().width,
		mSpriteHudBackground.getPosition().y));
	mTimer = 0;
}

void Dialoguehandler::clear(){
	Dialoguehandler::internalClear();
}

void Dialoguehandler::setCurrentDialogue(std::string filename){
	Dialoguehandler::internalClear();
	isInDialogue = true;
	mIndex = 0;
	mFilename = filename;
	Dialoguehandler::readFile();
	Texthandler::getInstance().setDialougeText(*mStringVectors[0]->at(0), *mStringVectors[0]->at(1), *mStringVectors[0]->at(2));
	Dialoguehandler::setCurrentSpeaker(*speakers.at(mIndex));
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
				speakers.push_back(new std::string(line));
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
			mDialogueAnimationRight = Animations::getDialogueMansaANI();
			mLeftActive = false;
		}
		break;
	case 'L':
		if (line[1] == 'I') {
			mCurrentspeaker = LIVIA;
			mDialogueAnimationLeft = Animations::getDialogueLiviaANI();
			mLeftActive = true;
		}
		break;
	default:
		break;
	}
}

void Dialoguehandler::loadTexture(char level) {
	int xIndex;
	int yIndex;
	switch (level) {
	case 's':
	default:
		xIndex = 0;
		yIndex = 0;
		break;
	}
	mTexture.loadFromImage(Toolbox::getTexture(Toolbox::DIALOGUEBOXSHEET), sf::IntRect(xIndex, yIndex, 1000, 200));
}

void Dialoguehandler::animate() {
	mTimer += ANIFramesPerFrame;

	if (mTimer >= 1) {
		mTimer = 0;
		if (mLeftActive) {
			mAnimationIndexLeft += 1;
			if (mAnimationIndexLeft >= mDialogueAnimationLeft->size()) {
				mAnimationIndexLeft = 0;
			}
			if (mDialogueAnimationLeft->size() > 0)
				mDialoguespriteLeft.setTexture(*mDialogueAnimationLeft->at(mAnimationIndexLeft));
		}
		else {
			mAnimationIndexRight += 1;
			if (mAnimationIndexRight >= mDialogueAnimationRight->size()) {
				mAnimationIndexRight = 0;
			}
			if (mDialogueAnimationRight->size() > 0)
				mDialoguespriteRight.setTexture(*mDialogueAnimationRight->at(mAnimationIndexRight));
		}
	}
}


//mTimer += ANIFramesPerFrame;
//if (mTimer >= 2) {
//	mAnimationIndex += 1;
//	mTimer = 0;
//	if (mAnimationIndex >= mHeartAnimation->size())
//		mAnimationIndex = 0;
//	if (mHeartAnimation->size() > 0) {
//		for (int i = 0; i < mLives.size(); i++) {
//			mLives[i].setTexture(*mHeartAnimation->at(mAnimationIndex));
//		}
//	}
//}

