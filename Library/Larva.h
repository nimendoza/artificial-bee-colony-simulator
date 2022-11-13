#pragma once
#include "Bee.h"
class Larva : public Bee {
public:
	explicit Larva(const Point& position, Hive& hive, const BeeType& type);
	~Larva() = default;

	void update(const double& time) override;
	void render(Window& window) override;

	static const float EMERGE_TIME_QUEEN;
	static const float EMERGE_TIME_DRONE;
	static const float EMERGE_TIME_WORKER;
private:
	void populate() override;
	void emerge();

	sf::Clock emerge;
	BeeType type;
};