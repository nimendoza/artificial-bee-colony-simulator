#include "Entity.h"
Entity::Entity(const Point& position, const Color& outline, const Color& fill) : position{ position }, forDeletion(false), fill{ fill }, outline{ outline }, node(nullptr), engine{} {
	std::random_device device;
	engine = std::default_random_engine(device());
}

float Entity::distance(const Point& a, const Point& b) {
	float dx{ b.x - a.x };
	float dy{ b.y - a.y };
	return sqrt((dx * dx) + (dy * dy));
}