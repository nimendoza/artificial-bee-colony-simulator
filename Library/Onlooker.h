#pragma once
#include "Bee.h"
class Onlooker : public Bee {
public:
	explicit Onlooker(const Point& position);
	~Onlooker() = default;

	void update(const double& time) override;
	void render(Window& window) override;
private:
	void populate() override;
};