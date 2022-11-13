#pragma once
#include "Entity.h"
#include "Hive.h"
#include "Foodsource.h"
#include "Bee.h"
class Node : public Entity {
public:
	explicit Node();
	~Node() = default;

	void update(const double& time) override;
	void render(Window& window) override;
	void setPosition(const Point& position) override;
	void setSize(const int& size);
	void remove(Hive* const hive);
	void remove(Bee* const bee);

	bool contains(const Point& point) const;

	std::vector<Hive*> hives;
	std::vector<Foodsource*> food;
	std::vector<Bee*> bees;
private:
	int size;
	sf::RectangleShape border;
	sf::Text text;
};