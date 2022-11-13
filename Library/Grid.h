#pragma once
#include "Base.h"
#include "Node.h"
class Grid : public Base {
private:
	Grid();

	static Grid* instance;

	Node** nodes;
	int gridSize;
	int nodeSize;
	Point origin;
	bool visible;
public:
	~Grid();

	void update(const double& time) override;
	void render(Window& window) override;
	void toggle();

	static Grid* get();

	Node* nodeAt(const Point& position) const;
	std::vector<Node*> nodesby(Node* const node) const;
};