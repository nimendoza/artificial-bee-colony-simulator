#include "pch.h"
#include "Fonts.h"


Fonts* Fonts::instance = nullptr;

Fonts::Fonts() {
	// CHANGE THIS
	std::string directory = "C:/Users/Owner/OneDrive/Documents/Programming/artificial-bee-colony-simulator";

	std::stringstream input;
	input << directory << "/External/cour.ttf";
	if (!font.loadFromFile(input.str())) {
		throw new std::exception("Error loading font file");
	}
}

Fonts* Fonts::get() {
	if (instance == nullptr) {
		instance = new Fonts();
	}

	return instance;
}