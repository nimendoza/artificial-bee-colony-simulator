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
		state = Idle;
	};

	updateWhen[Travelling] = [&](const double& time) {
		state = Idle;
	};

	updateWhen[Harvesting] = [&](const double& time) {
		state = Idle;
	};

	updateWhen[Delivering] = [&](const double& time) {
		state = Idle;
	};

	updateWhen[Depositing] = [&](const double& time) {
		state = Idle;
	};
}