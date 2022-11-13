#include "pch.h"
#include "Drone.h"
Drone::Drone(const Point& position, Hive& hive) : Bee(position, hive, DroneBee) {
	body.setFillColor(Color::Blue);

	Drone::populate();
}

void Drone::populate() {
	updateWhen[Idle] = [&](const double& time) {
		return;
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