#include "pch.h"
#include "Entity.h"
Entity::Entity(const Point& position, const Color& outlineColor, const Color& fillColor) : position{ position }, outline{ outlineColor }, fill{ fillColor }, forDeletion(false), node(nullptr), engine() {}

float Entity::distance(const Point& a, const Point& b) {
	float dx{ a.x - b.x };
	float dy{ a.y - b.y };
	return sqrt((dx * dx) + (dy * dy));
}
void Entity::setPosition(const Point& position) {
	this->position = position;
}