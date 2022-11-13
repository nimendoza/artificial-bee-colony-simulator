#pragma once
#include "Bee.h"
class Guard : public Bee {
public:
	explicit Guard(const Point& position, Hive& hive);
	~Guard() = default;

	void update(const double& time) override;
	void render(Window& window) override;
private:
	void populate() override;
};