#pragma once
#include "Bee.h"
class Larva : public Bee {
public:
	explicit Larva(const Point& position, Hive& hive, const BeeType& type);
	~Larva() = default;

	static const float EMERGE_TIME_QUEEN;
	static const float EMERGE_TIME_DRONE;
	static const float EMERGE_TIME_WORKER;
private:
	void populate() override;
	void develop();

	float emerge;
	float emergesIn;
	BeeType type;
};