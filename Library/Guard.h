#pragma once
#include "Bee.h"
class Guard : public Bee {
public:
	explicit Guard(const Point& position, Hive& hive);
	~Guard() = default;
private:
	void populate() override;
};