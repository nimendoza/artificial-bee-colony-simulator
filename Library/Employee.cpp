#include "pch.h"
#include "Employee.h"
#include "Foodsources.h"
Employee::Employee(const Point& position, Hive& hive) : Bee(position, hive, EmployeeBee), data{} {
	state = Scouting;
	
	body.setFillColor(Color::Cyan);

	Employee::populate();
}

void Employee::populate() {
	updateWhen[Idle] = [&](const double& time) {
		if (!resting) {
			state = Scouting;
		}
	};

	updateWhen[Scouting] = [&](const double& time) {
		getTarget();

		if (foodsource != nullptr) {
			if (distance(goal, position) <= TARGET_RADIUS) {
				dance();
				state = Harvesting;
				harvestTimer.restart();
			} else {
				Point newPosition = position;
				float rotationR{ atan2(goal.y - position.y, goal.x - position.x) };
				newPosition.x += (cos(rotationR) * speed * time);
				newPosition.y += (sin(rotationR) * speed * time);
				Bee::update(newPosition, rotationR);
			}
		}
	};

	updateWhen[Travelling] = [&](const double& time) {
		target(foodsource);

		if (distance(goal, position) <= TARGET_RADIUS) {
			state = Harvesting;
			harvestTimer.restart();
		} else {
			Point newPosition = position;
			float rotationR{ atan2(goal.y - position.y, goal.x - position.x) };
			newPosition.x += (cos(rotationR) * speed * time);
			newPosition.y += (sin(rotationR) * speed * time);
			Bee::update(newPosition, rotationR);
		}
	};

	updateWhen[Harvesting] = [&](const double& time) {
		if (harvestTimer.getElapsedTime().asSeconds() >= harvestDuration) {
			if (food > CARRYING_CAPACITY) {
				updateWhen[Delivering](time);
			} else if (extractionYield + food > CARRYING_CAPACITY) {
				float f = extractionYield - food + CARRYING_CAPACITY;
				harvest(foodsource->remove(f));
			} else {
				harvest(foodsource->remove(extractionYield));
			}
			state = Delivering;
		}
	};

	updateWhen[Delivering] = [&](const double& time) {
		target(hive.center);

		if (distance(goal, position) <= TARGET_RADIUS) {
			state = Depositing;
			harvestTimer.restart();
		} else {
			Point newPosition = position;
			float rotationR{ atan2(goal.y - position.y, goal.x - position.x) };
			newPosition.x += (cos(rotationR) * speed * time);
			newPosition.y += (sin(rotationR) * speed * time);
			Bee::update(newPosition, rotationR);
		}
	};

	updateWhen[Depositing] = [&](const double& time) {
		if (harvestTimer.getElapsedTime().asSeconds() >= harvestDuration) {
			if (resting) {
				state = Idle;
			} else {
				dance();
				deposit(food);
				if (!foodsource->viable()) {
					hive.remove(foodsource);
					foodsource = nullptr;
				}

				state = (foodsource == nullptr) ? Scouting : Travelling;
			}
		}
	};
}
void Employee::dance() const {
	hive.dance();
}
void Employee::getTarget() {
	auto food = Foodsources::get()->list;
	std::sort(begin(food), end(food), [&](Foodsource* const a, Foodsource* const b) {
		return distance(hive.center, a->center) < distance(hive.center, b->center);
		});
	for (auto i{ begin(Foodsources::get()->list) }; i < end(Foodsources::get()->list); i++) {
		if (hive.data.find(*i) == end(hive.data) && (*i)->viable()) {
			foodsource = (*i);
			target(foodsource);
			state = Travelling;
			data.first = foodsource->amount();
			data.second = distance(foodsource->center, hive.center);
			hive.data[foodsource] = data;
			break;
		}
	}
}