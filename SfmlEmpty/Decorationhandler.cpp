#include "Decorationhandler.h"

Decorationhandler::Decorationhandler(){
}

Decorationhandler::~Decorationhandler() {
}

Decorationhandler& Decorationhandler::getInstance() {
	static Decorationhandler decorationHandler;
	return decorationHandler;
}

void Decorationhandler::addDecoration(Decoration* decoration) {
	mDecorations.push_back(decoration);
}

void Decorationhandler::renderDecoration(sf::RenderWindow &window) {
	for (auto i : mDecorations) {
		i->render(window);
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
