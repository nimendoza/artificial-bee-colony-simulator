#pragma once
#include "Base.h"
#include "Foodsource.h"
class Foodsources : public Base {
private:
	Foodsources();

	static Foodsources* instance;
public:
	~Foodsources();

	void update(const double& time) override;
	void render(Window& window) override;
	void spawn(const Point& position);
	void sort(Hive* hive);
	Hive* current;

	static Foodsources* get();

	std::vector<Foodsource*> list;
};