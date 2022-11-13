#include "pch.h"
#include "World.h"
#include "Hives.h"
#include "Bees.h"
#include "Foodsources.h"
World* World::instance = nullptr;

World::World() : Base() {}
World::~World() {
	if (instance != nullptr) {
		delete instance;
	}
}

World* World::get() {
	if (instance == nullptr) {
		instance = new World();
	}
	return instance;
}
void World::generate(const std::string& path) {
	std::ifstream file;
	file.open(path);
	int hives; file >> hives;
	int foods; file >> foods;
	for (int i{}; i < hives; i++) {
		int x; file >> x;
		int y; file >> y;
		Hives::get()->spawn(Point(float(x), float(y)));
		Hive* hive = Hives::get()->list.back();

		int onlookers; file >> onlookers;
		for (int j{}; j < onlookers; j++) {
			Bees::get()->spawn(hive->center, *hive, OnlookerBee);
		}

		int employees; file >> employees;
		for (int j{}; j < employees; j++) {
			Bees::get()->spawn(hive->center, *hive, EmployeeBee);
		}

		int queens; file >> queens;
		for (int j{}; j < queens; j++) {
			Bees::get()->spawn(hive->center, *hive, QueenBee);
		}

		int drones; file >> drones;
		for (int j{}; j < drones; j++) {
			Bees::get()->spawn(hive->center, *hive, DroneBee);
		}

		int guards; file >> guards;
		for (int j{}; j < guards; j++) {
			Bees::get()->spawn(hive->center, *hive, GuardBee);
		}
	}
	for (int i{}; i < foods; i++) {
		int x; file >> x;
		int y; file >> y;
		Foodsources::get()->spawn(Point(float(x), float(y)));
	}
}