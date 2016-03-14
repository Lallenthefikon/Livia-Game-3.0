#include "Decorationhandler.h"

Decorationhandler::Decorationhandler(){
}

Decorationhandler::~Decorationhandler() {
	internalClear();
}

Decorationhandler& Decorationhandler::getInstance() {
	static Decorationhandler decorationHandler;
	return decorationHandler;
}

void Decorationhandler::addDecoration(Decoration* decoration) {
	mDecorations.push_back(decoration);
}

void Decorationhandler::renderDecoration(sf::RenderWindow &window, char layer) {
	switch (layer) {
	case 'f':
		for (auto i : mDecorations) {
			if (i->getDecorationLayer() == Decoration::FRONT) {
				i->render(window);
			}
		}
		break;
	case 'b':
		for (auto i : mDecorations) {
			if (i->getDecorationLayer() == Decoration::BACK) {
				i->render(window);
			}
		}
		break;
	default:
		break;
	}
}

void Decorationhandler::updateDecoration() {
	for (auto i : mDecorations) {
		i->update();
	}
}

void Decorationhandler::clear() {
	Decorationhandler::internalClear();
}

void Decorationhandler::internalClear() {
	while (!mDecorations.empty()) {
		delete mDecorations.back();
		mDecorations.pop_back();
	}
}
