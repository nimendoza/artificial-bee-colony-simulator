#include "pch.h"
#include "Bee.h"
#include "Node.h"
#include "Grid.h"
#include "Foodsources.h"
const float INF(1e10);
const float TOTAL_HOURS{ 24.0F / TIME_SCALING };

const float Bee::CARRYING_CAPACITY{ 10.0F };
const float Bee::SPEED{ 100.0F * TIME_SCALING };
const float Bee::BODY_RADIUS{ 5.0F };
const float Bee::TARGET_RADIUS{ 10.0F };
const float Bee::HARVESTING_DURATION{ 0.1F / TIME_SCALING };
const float Bee::WORK_DURATION{ 16.0F / TIME_SCALING };
const float Bee::REST_DURATION{ 8.0F / TIME_SCALING };
const float Bee::EXTRACTION_YIELD{ 10.0F };
const float Bee::MAX_ENERGY{ 50.0F * TIME_SCALING };
const float Bee::FATIGUE_PENALTY{ 24.0F * TIME_SCALING };
const float Bee::ENERGY_CONSUMPTION_RATE{ 1.0F * TIME_SCALING };
const std::map<const BeeType, float> Bee::LIFESPAN{
	{OnlookerBee, 24.0F * 42 / TIME_SCALING},
	{EmployeeBee, 24.0F * 42 / TIME_SCALING},
	{DroneBee, 24.0F * 30 * 3 / TIME_SCALING},
	{GuardBee, 24.0F * 42 / TIME_SCALING},
	{QueenBee, 24 * 30 * 24.0F / TIME_SCALING},
	{LarvaBee, INF},
	{EggBee, INF}
};
const Color Bee::STANDARD_BODY_COLOR{ Color::Yellow };
const Color Bee::NORMAL_COLOR{ Color::White };
const Color Bee::ALERT_COLOR{ Color::Red };

double infection_chance = 0;

Bee::Bee(const Point& position, Hive& hive, const BeeType& type) : Entity(position, NORMAL_COLOR, ALERT_COLOR), hive{ hive }, foodsource(nullptr), body(BODY_RADIUS), face(Point(BODY_RADIUS, 2)) {
	std::random_device device;
	engine = std::default_random_engine(device());
	
	state = Idle;

	body.setPointCount(360);
	body.setFillColor(STANDARD_BODY_COLOR);
	body.setOutlineColor(ALERT_COLOR);
	body.setOutlineThickness(-1);
	body.setPosition(position - Point(BODY_RADIUS, BODY_RADIUS));

	face.setFillColor(NORMAL_COLOR);
	face.setOutlineColor(NORMAL_COLOR);
	face.setPosition(position - Point(0, BODY_RADIUS));

	harvestTimer = 0;
	rest = 0;
	work = 0;
	life = 0;
	
	goal = hive.center;
	
	speed = std::normal_distribution<float>(SPEED, 10.0F / TIME_SCALING)(engine);
	harvestDuration = std::normal_distribution<float>(HARVESTING_DURATION, 0.05F / TIME_SCALING)(engine);
	workDuration = std::normal_distribution<float>(WORK_DURATION, 1.0F / TIME_SCALING)(engine);
	restDuration = TOTAL_HOURS - workDuration;
	maxEnergy = std::normal_distribution<float>(MAX_ENERGY, 20.0F * TIME_SCALING)(engine);
	energy = maxEnergy;
	energyConsumptionRate = std::normal_distribution<float>(ENERGY_CONSUMPTION_RATE, 1.0F / TIME_SCALING)(engine);
	fatiguePenalty = std::normal_distribution<float>(FATIGUE_PENALTY, 1.0F / TIME_SCALING)(engine);
	extractionYield = std::normal_distribution<float>(EXTRACTION_YIELD, 3.0F * TIME_SCALING)(engine);
	food = 0;
	lifespan = std::normal_distribution<float>((LIFESPAN.at(type) / std::discrete_distribution<int>{0, 100, infection_chance}(engine)), 24.0F / TIME_SCALING)(engine);
	resting = false;
}

void Bee::update(const double& time) {
	std::discrete_distribution<int> d{ 120000, 1 };
	if (d(engine)) {
		forDeletion = true;
	}

	if (resting) {
		if (at(&hive)) {
			energy += energyConsumptionRate * time;
			state = Idle;
		} else {
			energy -= energyConsumptionRate * time;
			state = Delivering;
		}

		rest += time;
		if (rest >= restDuration) {
			work = 0;
			resting = false;
		}
	} else {
		energy -= energyConsumptionRate * time;
		if (energy < maxEnergy) {
			if (state == Idle || state == Depositing) {
				energy += hive.remove(maxEnergy - energy);
			} else if (state == Harvesting) {
				if (foodsource != nullptr) {
					energy += foodsource->remove(maxEnergy - energy);
				} else {
					target(hive.center);
					state = Delivering;
				}
			} else if (hungry()) {
				float req{ std::min(maxEnergy - energy, food) };
				energy += req;
				food -= req;
			}
		}

		work += time;
		if (work >= workDuration) {
			rest = 0;
			resting = true;
		}
	}

	if (energy <= 0) {
		lifespan -= fatiguePenalty;
		energy = maxEnergy;
	}

	life += time;
	if (life >= lifespan) {
		forDeletion = true;
	}

	if (node != nullptr && !node->contains(position)) {
		node->remove(this);
		node = nullptr;
	}

	if (node == nullptr) {
		node = Grid::get()->nodeAt(position);
		node->bees.push_back(this);
	}

	updateWhen[state](time);
}
void Bee::update(const Point& position, const float& rotationR) {
	Entity::setPosition(position);

	auto rotation = rotationR * 180 / PI;
	face.setRotation(rotation);
}
void Bee::render(Window& window) {
	detectCollisions();

	body.setPosition(position - Point(BODY_RADIUS, BODY_RADIUS));
	face.setPosition(position);

	window.draw(body);
	if (state != Scouting) {
		window.draw(face);
	}
}
void Bee::target(Foodsource* const foodsource) {
	this->foodsource = foodsource;
	target(foodsource->center);
}
void Bee::target(const Point& point) {
	goal = point;
}
void Bee::harvest(const float& amount) {
	food += amount;
}
void Bee::deposit(float amount) {
	amount = std::min(amount, food);
	hive.add(food);
	food -= amount;
}
bool Bee::at(const Foodsource& foodsource) const {
	float left{ foodsource.position.x };
	float right{ left + foodsource.dimensions.x };
	float top{ foodsource.position.y };
	float bottom{ top + foodsource.dimensions.y };
	return
		(position.x + BODY_RADIUS) > left &&
		(position.x - BODY_RADIUS) < right &&
		(position.y + BODY_RADIUS) > top &&
		(position.y - BODY_RADIUS) < bottom;
}
bool Bee::at(Hive* const hive) const {
	float left{ hive->position.x };
	float right{ left + hive->dimensions.x };
	float top{ hive->position.y };
	float bottom{ top + hive->dimensions.y };
	return
		(position.x + BODY_RADIUS) > left &&
		(position.x - BODY_RADIUS) < right &&
		(position.y + BODY_RADIUS) > top &&
		(position.y - BODY_RADIUS) < bottom;
}
bool Bee::near(const Foodsource& foodsource) const {
	return (distance(position, foodsource.center) - BODY_RADIUS) < Foodsource::DETECTION_RADIUS;
}
bool Bee::hungry() const {
	return (energy / maxEnergy) < 0.50F;
}
void Bee::detectCollisions() {
	if (node != nullptr) {
		bool colliding{ false };
		auto hives = node->hives;
		for (auto i{ begin(hives) }; i != end(hives); i++) {
			if (at(*i)) {
				colliding = true;
				break;
			}
		}

		if (!colliding) {
			auto food = node->food;
			for (auto i{ begin(food) }; i != end(food); i++) {
				if (at(*(*i))) {
					colliding = true;
					break;
				}
			}
		}

		body.setOutlineColor(colliding ? ALERT_COLOR : NORMAL_COLOR);
	}
}
void Bee::handleCollisions() {
	auto foodSourceManager = Foodsources::get();
	bool foodSourceFound = false;
	auto foodSources = node->food;
	switch (state) {
	case Travelling:
		foodSourceFound = false;
		for (auto iter = foodSources.begin(); iter != foodSources.end(); ++iter) {
			if (at(*(*iter)) && (*iter)->viable()) {
				foodSourceFound = true;
				state = Harvesting;
				break;
			}
		}
	}
}