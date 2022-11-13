#include "pch.h"
#include "Foodsource.h"
#include "Node.h"
#include "Grid.h"
#include "Fonts.h"
const float Foodsource::WIDHT{ 200.0F };
const float Foodsource::HEIGHT{ 200.0F };
const float Foodsource::REGENERATION_TIME{ 24.0F / 2 };
const float Foodsource::DETECTION_RADIUS{ 400.0F };
const float Foodsource::MAX_FOOD_AMOUNT{ 1000.0F };

Foodsource::Foodsource(const Point& position) : Entity(position, Color::White, Color::Green), dimensions(WIDHT, HEIGHT), body(dimensions), food{ MAX_FOOD_AMOUNT }, text(), center(position.x + dimensions.x / 2, position.y + dimensions.y / 2) {
	body.setPosition(position);
	body.setOutlineThickness(-10);
	body.setOutlineColor(outline);
	body.setFillColor(fill);

	text.setCharacterSize(16);
	text.setOutlineColor(Color::White);
	text.setFillColor(Color::White);
	text.setPosition(position + Point(10, 10));
	regeneration.restart();

	text.setFont(Fonts::get()->font);
}

void Foodsource::update(const double& time) {
	if (regeneration.getElapsedTime().asSeconds() >= REGENERATION_TIME) {
		food = MAX_FOOD_AMOUNT;
		regeneration.restart();
	}

	if (node != nullptr && !node->contains(position)) {
		node->remove(this);
		node = nullptr;
	}

	if (node == nullptr) {
		node = Grid::get()->nodeAt(position);
		node->food.push_back(this);
	}
}
void Foodsource::render(Window& window) {
	body.setFillColor(Color(22, 22 + 96 * (this->food / MAX_FOOD_AMOUNT), 22));

	std::stringstream s;
	s << "Food: " << this->food << '\n';
	text.setString(s.str());

	window.draw(body);
	window.draw(text);
}
float Foodsource::remove(const float food) {
	float amount = std::min(food, this->food);
	this->food -= amount;
	return amount;
}
float* Foodsource::amount() {
	return &food;
}
bool Foodsource::viable() const {
	return food > 0;
}