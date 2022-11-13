#pragma once
#include "pch.h"
#include "Base.h"
class Entity : public Base {
public:
	explicit Entity(const Point& position, const Color& outline, const Color& fill);
	~Entity() = default;

	virtual void update(const double& time) override {}
	virtual void render(Window& window) override {}
	virtual void setPosition(const Point& position);

	static float distance(const Point& a, const Point& b);

	bool forDeletion;
	Point position;
protected:
	Color outline;
	Color fill;
	class Node* node;
	std::default_random_engine engine;
};

