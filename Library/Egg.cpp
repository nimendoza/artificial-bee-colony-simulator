#include "pch.h"
#include "Egg.h"
#include "Bees.h"
const float Egg::INCUBATION_DURATION{ 24.0f * 3 / TIME_SCALING };

Egg::Egg(const Point& position, Hive& hive, const BeeType& type) : Bee(position, hive, EggBee) {
	body.setFillColor(Color::Green);

	hatching = 0;

	this->type = type;

	incubation = std::normal_distribution<float>(INCUBATION_DURATION, 12.0F / TIME_SCALING)(engine);

	Egg::populate();
}

void Egg::update(const double& time) {
	updateWhen[state](time);
}
void Egg::populate() {
	updateWhen[Idle] = [&](const double& time) {
		hatching += time;
		if (hatching >= incubation) {
			hatch();
		}
	};

	updateWhen[Scouting] = [&](const double& time) {
		hatching += time;
		state = Idle;
	};

	updateWhen[Travelling] = [&](const double& time) {
		hatching += time;
		state = Idle;
	};

	updateWhen[Harvesting] = [&](const double& time) {
		hatching += time;
		state = Idle;
	};

	updateWhen[Delivering] = [&](const double& time) {
		hatching += time;
		state = Idle;
	};

	updateWhen[Depositing] = [&](const double& time) {
		hatching += time;
		state = Idle;
	};
}
void Egg::hatch() {
	forDeletion = true;
	Bees::get()->spawn(position, hive, LarvaBee, type);
}