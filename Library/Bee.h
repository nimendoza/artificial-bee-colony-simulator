#pragma once
#include "Entity.h"
#include "Hive.h"
#include "Foodsource.h"
#include "BeeState.h"
class Bee : public Entity {
public:
	explicit Bee(const Point& point, Hive& hive, const BeeType& type);
	~Bee() = default;

	void update(const double& time) override;
	void update(const Point& position, const float& rotationR);
	void render(Window& window) override;
	void target(Foodsource* const foodsource);
	void target(const Point& position);
	void harvest(const float& amount);
	void deposit(float amount);

	bool at(const Foodsource& foodsource) const;
	bool at(Hive* const hive) const;
	bool near(const Foodsource& foodsource) const;
	bool hungry() const;

	const static double pesticide_chance;
	const static float CARRYING_CAPACITY;
	const static float SPEED;
	const static float BODY_RADIUS;
	const static float TARGET_RADIUS;
	const static float HARVESTING_DURATION;
	const static float WORK_DURATION;
	const static float REST_DURATION;
	const static float EXTRACTION_YIELD;
	const static float MAX_ENERGY;
	const static float FATIGUE_PENALTY;
	const static float ENERGY_CONSUMPTION_RATE;
	const static std::map<const BeeType, float> LIFESPAN;
	const static Color STANDARD_BODY_COLOR;
	const static Color NORMAL_COLOR;
	const static Color ALERT_COLOR;

	Hive& hive;
	BeeState state;
	bool resting;
protected:
	using updateCallback = std::function<void(const double&)>;

	virtual void populate() {}
	void detectCollisions();
	void handleCollisions();

	std::map<BeeState, updateCallback> updateWhen;

	const float PI{ 3.14159265259F };

	sf::CircleShape body;
	sf::RectangleShape face;
	sf::Clock harvestTimer;
	sf::Clock rest;
	sf::Clock work;
	sf::Clock life;
	Foodsource* foodsource;
	Point goal;
	float speed;
	float harvestDuration;
	float workDuration;
	float restDuration;
	float maxEnergy;
	float energy;
	float energyConsumptionRate;
	float fatiguePenalty;
	float extractionYield;
	float food;
	float lifespan;
};