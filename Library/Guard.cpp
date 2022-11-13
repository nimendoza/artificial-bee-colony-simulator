#include "pch.h"
#include "Guard.h"
Guard::Guard(const Point& position, Hive& hive) : Bee(position, hive, GuardBee) {
	body.setFillColor(Color::Black);

	Guard::populate();
}

void Guard::populate() {
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