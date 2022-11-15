#include "pch.h"
#include "Larva.h"
#include "Bees.h"

std::default_random_engine generator;
std::normal_distribution<float> distribution(11.0, 5.0);
const float Larva::EMERGE_TIME_QUEEN{ 24 * distribution(generator) / TIME_SCALING };
const float Larva::EMERGE_TIME_DRONE{ 24 * distribution(generator) / TIME_SCALING };
const float Larva::EMERGE_TIME_WORKER{ 24 * distribution(generator) / TIME_SCALING };

Larva::Larva(const Point& position, Hive& hive, const BeeType& type) : Bee(position, hive, LarvaBee) {
	body.setFillColor(Color::White);

	this->type = type;

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
}