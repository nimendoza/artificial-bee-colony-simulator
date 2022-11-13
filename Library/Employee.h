#pragma once
#include "Bee.h"
class Employee : public Bee {
public:
	explicit Employee(const Point& position, Hive& hive);
	~Employee() = default;

	void update(const double& time) override;
	void render(Window& window) override;
private:
	void populate() override;
	void dance() const;
	void getTarget();

	std::pair<float*, float> data;
};