#pragma once
#include "pch.h"
#include "Base.h"
class Entity : public Base {
public:
	explicit Entity(const Point& position, const Color& outline, const Color& fill);
	
	virtual void update(const double& time) override {}
	virtual void render(Plane& window) override {}

	static float distance(const Point& a, const Point& b);

	Point position;
	bool forDeletion;
protected:
	Color fill;
	Color outline;
	class Node* node;
	std::default_random_engine engine;
};