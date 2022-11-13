#include "pch.h"
#include "Egg.h"
const float Egg::INCUBATION_DURATION{ 24.0f * 3 / 2 };

Egg::Egg(const Point& position, Hive& hive, const BeeType& type) : Bee(position, hive, EggBee) {
	hatching.restart();

	this->type = type;

	incubation = std::normal_distribution<float>(INCUBATION_DURATION, 12.0F / 2)(generator);
}

void Egg::update(const double& time) {
	updateWhen[state](time);
}
void Egg::populate() {
	updateWhen[Idle] = [&](const double& time) {
		if (hatching.getElapsedTime().asSeconds() >= incubation) {
			hatch();
		}
	};

	updateWhen[Scouting] = [&](const double& time) {
		throw new std::exception("This shouldn't happen\n");
	};

	updateWhen[Travelling] = [&](const double& time) {
		throw new std::exception("This shouldn't happen\n");
	};

	updateWhen[Harvesting] = [&](const double& time) {
		throw new std::exception("This shouldn't happen\n");
	};

	updateWhen[Delivering] = [&](const double& time) {
		throw new std::exception("This shouldn't happen\n");
	};

	updateWhen[Depositing] = [&](const double& time) {
		throw new std::exception("This shouldn't happen\n");
	};
}

void Egg::hatch() {

}