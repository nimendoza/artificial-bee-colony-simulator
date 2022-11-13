#pragma once
#include "Bee.h"
class Queen : public Bee {
public:
	explicit Queen(const Point& position, Hive& hive);
	~Queen() = default;

	void update(const double& time) override;
	void render(Window& window) override;

	static const float EGG_LAYING_INTERVAL;
	static const float MAX_EGGS_LAID;
protected:
	void populate() override;

	sf::Clock laysEggs;
};