#pragma once
#include "Bee.h"
class Egg : public Bee {
public:
	explicit Egg(const Point& position, Hive& hive, const BeeType& type);
	~Egg() = default;

	void update(const double& time) override;

	static const float INCUBATION_DURATION;
private:
	void populate() override;
	void hatch();

	sf::Clock hatching;
	float incubation;
};