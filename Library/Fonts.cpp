#include "Fonts.h"
Fonts* Fonts::instance{ nullptr };

Fonts::Fonts() {
	if (!font.loadFromFile("../External/cour.ttf")) {
		throw new std::exception("Error loading font file");
	}
}

Fonts* Fonts::get() {
	if (instance == nullptr) {
		instance = new Fonts();
	}

	return instance;
}