#pragma once
#include "Entity.h"
#include "BeeType.h"
class Hive : public Entity {
public:
	explicit Hive(const Point& position);
	~Hive() = default;

	void update(const double& time) override;
	void render(Window& window) override;
	void remove(class Bee* const bee);
	void remove(class Foodsource* const foodsource);
	float remove(float food);
	void add(class Onlooker* const bee);
	void add(const float& food);
	void validate();
	void dance();

	static const float WIDTH;
	static const float HEIGHT;
	static const float DANCE_DURATION;
	static const float NO_ATTACK_CHANCE;
	static const float FOOD_PENALTY;
	static const int GUARD_PENALTY;
	
	Point dimensions;
	Point center;
	std::map<BeeType, int> count;
	std::vector<class Bee*> idles;
	std::vector<class Bee*> guards;
	std::map<class Foodsource* const, std::pair<float*, float>> data;
	float food;
private:
	static float compute(const std::pair<float*, float>& data, const float& minY, const float& maxY, const float& minD, const float& maxD);

	sf::RectangleShape body;
	sf::Text text;
	float danceTimer;
	bool dancing;
};

