#include "pch.h"
#include "Larva.h"
#include "Bees.h"
const float Larva::EMERGE_TIME_QUEEN{ 24 * 16.0F / TIME_SCALING };
const float Larva::EMERGE_TIME_DRONE{ 24 * 24.0F / TIME_SCALING };
const float Larva::EMERGE_TIME_WORKER{ 24 * 21.0F / TIME_SCALING };

Larva::Larva(const Point& position, Hive& hive, const BeeType& type) : Bee(position, hive, LarvaBee), type{ type } {
	body.setFillColor(Color::White);

	energyConsumptionRate /= 2;

	emerge = 0;
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
		emerge += time;
		if (emerge >= emergesIn) {
			develop();
		}
	};

	updateWhen[Scouting] = [&](const double& time) {
		emerge += time;
		state = Idle;
	};

	updateWhen[Travelling] = [&](const double& time) {
		emerge += time;
		state = Idle;
	};

	updateWhen[Harvesting] = [&](const double& time) {
		emerge += time;
		state = Idle;
	};

	updateWhen[Delivering] = [&](const double& time) {
		emerge += time;
		state = Idle;
	};

	updateWhen[Depositing] = [&](const double& time) {
		emerge += time;
		state = Idle;
	};
}
void Larva::develop() {
	forDeletion = true;
	Bees::get()->spawn(position, hive, type);
}