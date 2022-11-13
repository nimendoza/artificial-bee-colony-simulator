#include "pch.h"
#include "Foodsources.h"
#include "Foodsource.h"
Foodsources* Foodsources::instance = nullptr;

Foodsources::Foodsources() : list{} {}
Foodsources::~Foodsources() {
	for (auto i{ begin(list) }; i != end(list); i++) {
		delete (*i);
	}

	list.clear();
}

Foodsources* Foodsources::get() {
	if (instance == nullptr) {
		instance = new Foodsources();
	}

	return instance;
}
void Foodsources::update(const double& deltaTime) {
	for (auto i{ begin(list) }; i != end(list); i++) {
		(*i)->update(deltaTime);
	}
}
void Foodsources::render(Window& window) {
	for (auto i{ begin(list) }; i != end(list); i++) {
		(*i)->render(window);
	}
}
void Foodsources::spawn(const Point& position) {
	list.push_back(new Foodsource(position));
}