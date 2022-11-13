#pragma once
#include "Base.h"
#include "Hive.h"
class Hives : public Base {
private:
	Hives();

	static Hives* instance;
public:
	~Hives();

	void update(const double& time) override;
	void render(Window& window) override;
	void spawn(const Point& position);

	static Hives* get();

	std::vector<Hive*> list;
};

