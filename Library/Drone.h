#pragma once
#include "Bee.h"
class Drone : public Bee {
public:
	explicit Drone(const Point& position, Hive& hive);
	~Drone() = default;
private:
	void populate() override;
};