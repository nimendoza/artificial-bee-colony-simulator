#include "pch.h"
#include "Hives.h"
Hives* Hives::instance = nullptr;

Hives::Hives() : list{} {}
Hives::~Hives() {
	for (auto i{ begin(list) }; i != end(list); i++) {
		delete (*i);
	}

	list.clear();
}

Hives* Hives::get() {
	if (instance == nullptr) {
		instance = new Hives();
	}
	return instance;
}
void Hives::update(const double& deltaTime) {
	for (auto i{ begin(list) }; i != end(list); i++) {
		(*i)->update(deltaTime);
	}
}
void Hives::render(Window& window) {
	for (auto i{ begin(list) }; i != end(list); i++) {
		(*i)->render(window);
	}
}
void Hives::spawn(const Point& position) {
	list.push_back(new Hive(position));
}