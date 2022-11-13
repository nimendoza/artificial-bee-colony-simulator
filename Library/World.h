#pragma once
#include "Base.h"
class World : public Base {
private:
	World();

	static World* instance;
public:
	~World();

	static World* get();

	void update(const double& time) override {}
	void render(Window& window) override {}
	void generate(const std::string& path);
};