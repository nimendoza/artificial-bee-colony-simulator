#include "pch.h"
#include "Node.h"
#include "Fonts.h"
Node::Node() : Entity(Point(), Color::White, Color::Transparent), size{}, hives{}, food{}, bees{}, border(), text() {

	border.setOutlineThickness(-10);
	border.setOutlineColor(outline);
	border.setFillColor(fill);

	text.setFont(Fonts::get()->font);
	text.setCharacterSize(64);
	text.setOutlineColor(Color::White);
}

void Node::render(Window& window) {
	std::stringstream s;
	s << "Hives: " << hives.size() << '\n'
		<< "Food sources: " << food.size() << '\n'
		<< "Bees: " << bees.size() << '\n';
	text.setString(s.str());
	text.setPosition(position + Point(10, 10));

	window.draw(border);
	window.draw(text);
}
void Node::setPosition(const Point& position) {
	Entity::setPosition(position);
	border.setPosition(position);
	text.setPosition(position + Point(15, 15));
}
void Node::setSize(const int& size) {
	this->size = size;
	border.setSize(Point(size, size));
}
void Node::remove(Hive* const hive) {
	for (auto i{ begin(hives) }; i != end(hives); i++) {
		if ((*i) == hive) {
			hives.erase(i);
			break;
		}
	}
}
void Node::remove(Foodsource* const foodsource) {
	for (auto i{ begin(food) }; i != end(food); i++) {
		if ((*i) == foodsource) {
			food.erase(i);
			break;
		}
	}
}
void Node::remove(Bee* const bee) {
	for (auto i{ begin(bees) }; i != end(bees); i++) {
		if ((*i) == bee) {
			bees.erase(i);
			break;
		}
	}
}
bool Node::contains(const Point& point) const {
	return
		point.x >= position.x &&
		point.x < (position.x + size) &&
		point.y >= position.y &&
		point.y < (position.y + size);
}