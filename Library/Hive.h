#pragma once
#include "Entity.h"
#include "BeeType.h"
class Hive : public Entity {
public:
	explicit Hive(const Point& position);
	~Hive() = default;

	void update(const double& time) override;
	void render(Plane& window) override;
	void remove(class Foodsource* const foodsource);
	void remove(class Bee* const bee);
	void add(class Bee* const bee);
	void add(const float& food);
	void validate();
	void dance();

	static const float WIDTH;
	static const float HEIGHT;
	static const float DANCE_DURATION;

	Point dimensions;
	Point center;
	std::map<BeeType, int> count;
	std::map<BeeType, std::vector<class Bee*>> bees;
	std::map<class Foodsource* const, std::pair<float*, float>> data;
	float food;
private:
	static float compute(const std::pair<float*, float>& data, const float& minY, const float& maxY, const float& minD, const float& maxD);

	sf::RectangleShape body;
	sf::Text text;
	sf::Clock danceTimer;
	bool dancing;
};