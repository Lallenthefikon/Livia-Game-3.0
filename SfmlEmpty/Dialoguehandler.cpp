#include "Dialoguehandler.h"
#include <fstream>
#include <iostream>

static float ANIFramesPerFrame = 0.5;

Dialoguehandler::Dialoguehandler(){
}

Dialoguehandler::~Dialoguehandler(){
	internalClear();
}

Dialoguehandler& Dialoguehandler::getInstance() {
	static Dialoguehandler dialogueHandler;
	return dialogueHandler;
}

void Dialoguehandler::renderDialogue(sf::RenderWindow & window){
	window.draw(mSpriteHudBackground);
	if (mCurrentspeaker != INSTRUCTIONS) {
		if (mLeftActive)
			window.draw(mDialoguespriteLeft);
		else
			window.draw(mDialoguespriteRight);
	}
	Texthandler::getInstance().renderDialougeText(window);
}


void Dialoguehandler::updateDialogue() {
	mDialoguespriteLeft.setTextureRect(sf::IntRect(mDialoguespriteLeft.getLocalBounds().width, 0, -mDialoguespriteLeft.getLocalBounds().width, mDialoguespriteLeft.getLocalBounds().height));
	
	animate();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
		if (mReturnRealesed) {
			mIndex++;
			if (mIndex >= mStringVectors.size()) {
				isInDialogue = false;
			}

			else {
				Dialoguehandler::setCurrentSpeaker(*mSpeakers[mIndex]);
				Texthandler::getInstance().setDialougeText(*mStringVectors[mIndex]->at(0), *mStringVectors[mIndex]->at(1), *mStringVectors[mIndex]->at(2));
			}
			mReturnRealesed = false;
		}
	}
	else {
		mReturnRealesed = true;
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

void Dialoguehandler::loadDialougehandler(char level){
	mReturnRealesed = true;
	Dialoguehandler::loadTexture(level);



	mSpriteHudBackground.setTexture(mTexture);
	mSpriteHudBackground.setScale(1.5, 1.4);
	mSpriteHudBackground.setPosition(sf::Vector2f(240,750));
	mDialoguespriteLeft.setPosition(mSpriteHudBackground.getPosition().x + 30, mSpriteHudBackground.getPosition().y + 25);
	mDialoguespriteLeft.setScale(0.47, 0.47);
	
	mDialoguespriteRight.setPosition(sf::Vector2f(mSpriteHudBackground.getPosition().x + mSpriteHudBackground.getGlobalBounds().width - 212,
	mSpriteHudBackground.getPosition().y + 25)); 
	mDialoguespriteRight.setScale(0.47, 0.47);
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
	Dialoguehandler::setCurrentSpeaker(*mSpeakers[mIndex]);
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
	mSpeakers.clear();
}

void Dialoguehandler::readFile(){
	int index(0);
	std::string line;
	std::ifstream dialougefile(mFilename);
	if (dialougefile.is_open()) {
		while (getline(dialougefile, line)) {
			if (index == 0) {
				mSpeakers.push_back(new std::string(line));
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
		if (line[1] == 'A') {
			mCurrentspeaker = MANSASOUL;
			mDialogueAnimationRight = Animations::getDialogueMansaANI();
			mLeftActive = false;
			ANIFramesPerFrame = 0.5;
		}
		else if (line[1] == 'I') {
			mCurrentspeaker = MUHNIN;
			mDialogueAnimationRight = Animations::getDialogueMuhninANI();
			mLeftActive = false;
			ANIFramesPerFrame = 0.5;
		}
		break;
	case 'L':
		if (line[1] == 'I') {
			mCurrentspeaker = LIVIA;
			mDialogueAnimationLeft = Animations::getDialogueLiviaANI();
			mLeftActive = true;
			ANIFramesPerFrame = 0.5;
		}
		break;
	case 'A':
		if (line[1] == 'C') {
			mCurrentspeaker = TUMMY;
			mDialogueAnimationRight = Animations::getDialogueTummyANI();
			mLeftActive = false;
			ANIFramesPerFrame = 0.25;
		}
	case 'I':
		if (line[1] == 'N') {
			mCurrentspeaker = INSTRUCTIONS;
		}
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

