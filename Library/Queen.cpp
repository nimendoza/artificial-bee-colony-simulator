#include "pch.h"
#include "Queen.h"
#include "Bees.h"
const float Queen::EGG_LAYING_INTERVAL{ 1.0F / TIME_SCALING };
const float Queen::MAX_EGGS_LAID{ 125.0F };

Queen::Queen(const Point& position, Hive& hive) : Bee(position, hive, QueenBee) {
	body.setFillColor(Color::Magenta);
	
	laysEggs.restart();

	Queen::populate();
}

void Queen::populate() {
	updateWhen[Idle] = [&](const double& time) {
		if (laysEggs.getElapsedTime().asSeconds() >= EGG_LAYING_INTERVAL) {
			laysEggs.restart();

			for (int i{ hive.count[OnlookerBee] }; i < 90; i++) {
				Bees::get()->spawn(position, hive, OnlookerBee);
			}
			for (int i{ hive.count[EmployeeBee] }; i < 10; i++) {
				Bees::get()->spawn(position, hive, EmployeeBee);
			}
			for (int i{ hive.count[DroneBee] }; i < 1; i++) {
				Bees::get()->spawn(position, hive, DroneBee);
			}
			for (int i{ hive.count[GuardBee] }; i < 20; i++) {
				Bees::get()->spawn(position, hive, GuardBee);
			}

			if (forDeletion) {
				Bees::get()->spawn(position, hive, QueenBee);
			}

			std::uniform_int_distribution<int> distribution(0, int(MAX_EGGS_LAID));
			int count{ distribution(engine) };
			for (int i{}; i < count; i++) {
				std::discrete_distribution<int> distribution_type{ 75, 9, 1, 17, 0 };
				switch (distribution_type(engine)) {
				case 0:
					Bees::get()->spawn(position, hive, EggBee, OnlookerBee);
					break;
				case 1:
					Bees::get()->spawn(position, hive, EggBee, EmployeeBee);
					break;
				case 2:
					Bees::get()->spawn(position, hive, EggBee, DroneBee);
					break;
				case 3:
					Bees::get()->spawn(position, hive, EggBee, GuardBee);
					break;
				}
			}
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