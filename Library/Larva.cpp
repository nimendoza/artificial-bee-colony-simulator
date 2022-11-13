#include "pch.h"
#include "Larva.h"
#include "Bees.h"
const float Larva::EMERGE_TIME_QUEEN{ 24 * 16.0F / 1 };
const float Larva::EMERGE_TIME_DRONE{ 24 * 24.0F / 1 };
const float Larva::EMERGE_TIME_WORKER{ 24 * 21.0F / 1 };

Larva::Larva(const Point& position, Hive& hive, const BeeType& type) : Bee(position, hive, LarvaBee), type{ type } {
	body.setFillColor(Color::White);

	energyConsumptionRate /= 2;

	emerge.restart();
	switch (type) {
	case QueenBee:
		emergesIn = EMERGE_TIME_QUEEN;
		break;
	case DroneBee:
		emergesIn = EMERGE_TIME_DRONE;
		break;
	case EmployeeBee:
	case OnlookerBee:
	case GuardBee:
		emergesIn = EMERGE_TIME_WORKER;
		break;
	}

	Larva::populate();
}

void Larva::populate() {
	updateWhen[Idle] = [&](const double& time) {
		if (emerge.getElapsedTime().asSeconds() >= emergesIn) {
			develop();
		}
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
void Larva::develop() {
	forDeletion = true;
	Bees::get()->spawn(position, hive, type);
}