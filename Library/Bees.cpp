#include "pch.h"
#include "Bees.h"
#include "Onlooker.h"
#include "Employee.h"
#include "Guard.h"
#include "Drone.h"
#include "Queen.h"
#include "Larva.h"
#include "Egg.h"
Bees* Bees::instance = nullptr;

Bees::Bees() : list{} {}
Bees::~Bees() {
	for (auto i{ begin(list) }; i != end(list); i++) {
		for (auto j{ begin(i->second) }; j != end(i->second); j++) {
			delete (*j);
		}

		i->second.clear();
	}
}

void Bees::update(const double& deltaTime) {
	for (auto i{ begin(list) }; i != end(list); i++) {
		for (auto j{ begin(i->second) }; j != end(i->second); j++) {
			if (*j != nullptr) {
				(*j)->update(deltaTime);
			}
		}
	}

	cleanup();
}
void Bees::render(Window& window) {
	for (auto i{ begin(list) }; i != end(list); i++) {
		for (auto j{ begin(i->second) }; j != end(i->second); j++) {
			(*j)->render(window);
		}
	}
}
void Bees::spawn(const Point& point, Hive& hive, const BeeType& beeType) {
	switch (beeType) {
	case OnlookerBee:
		list[beeType].push_back(new Onlooker(point, hive));
		hive.count[ForagerBee]++;
		break;
	case EmployeeBee:
		list[beeType].push_back(new Employee(point, hive));
		hive.count[ForagerBee]++;
		break;
	case DroneBee:
		list[beeType].push_back(new Drone(point, hive));
		break;
	case QueenBee:
		list[beeType].push_back(new Queen(point, hive));
		break;
	case GuardBee:
		list[beeType].push_back(new Guard(point, hive));
		break;
	}
	hive.count[AllBeeTypes]++;
	hive.count[beeType]++;
}
void Bees::spawn(const Point& point, Hive& hive, const BeeType& beeType, const BeeType& larvaType) {
	switch (beeType) {
	case LarvaBee:
		list[beeType].push_back(new Larva(point, hive, larvaType));
		break;
	case EggBee:
		list[beeType].push_back(new Egg(point, hive, larvaType));
		break;
	}
	hive.count[AllBeeTypes]++;
	hive.count[beeType]++;
}
void Bees::cleanup() {
	for (auto j{begin(list)}; j != end(list); j++) {
		BeeType beeType = j->first;
		bool removed{ true };
		do {
			removed = false;
			for (auto i{ begin(list[beeType]) }; i != end(list[beeType]); i++) {
				if ((*i)->forDeletion) {
					(*i)->hive.count[beeType]--;
					(*i)->hive.count[AllBeeTypes]--;
					if (beeType == OnlookerBee || beeType == EmployeeBee) {
						(*i)->hive.count[ForagerBee]--;
					}
					delete (*i);
					list[beeType].erase(i);
					removed = true;
					break;
				}
			}
		} while (removed);
	}
}
Bees* Bees::get() {
	if (instance == nullptr) {
		instance = new Bees();
	}
	return instance;
}