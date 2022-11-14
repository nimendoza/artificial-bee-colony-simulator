#include "pch.h"
#include "Guard.h"
Guard::Guard(const Point& position, Hive& hive) : Bee(position, hive, GuardBee) {
	body.setFillColor(Color::Black);

	hive.guards.push_back(this);

	Guard::populate();
}

void Guard::populate() {
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