#pragma once

#include <vector>
#include "Decoration.h"

class Decorationhandler {
public:
	typedef std::vector<Decoration*> Decorations;
	static Decorationhandler& getInstance();

	void addDecoration(Decoration* decoration);
	void renderDecoration(sf::RenderWindow &window, char layer);
	void updateDecoration();
	void clear();

	Decorations& getDecorations() { return mDecorations; }
	~Decorationhandler();
private:
	Decorationhandler();
	void internalClear();

	Decorations mDecorations;
};

