#pragma once
#include "pch.h"
class Fonts {
private:
	Fonts();

	static Fonts* instance;
public:
	~Fonts();

	static Fonts* get();

	sf::Font font;
};