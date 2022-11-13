#pragma once
#include "Bee.h"
class Onlooker : public Bee {
public:
	explicit Onlooker(const Point& position, Hive& hive);
	~Onlooker() = default;
private:
	void populate() override;
};