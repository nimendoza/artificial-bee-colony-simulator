#pragma once
#include "Entity.h"
#include "Hive.h"
class Foodsource : public Entity {
public:
	explicit Foodsource(const Point& position);
	~Foodsource() = default;

	void update(const double& time) override;
	void render(Window& window) override;
	float remove(const float food);
	float* amount();
	
	bool viable() const;

	static const float WIDHT;
	static const float HEIGHT;
	static const float REGENERATION_TIME;
	static const float DETECTION_RADIUS;
	static const float MAX_FOOD_AMOUNT;

	Point center;
	Point dimensions;
private:
	sf::Text text;
	sf::RectangleShape body;
	float regeneration;
	float food;
};