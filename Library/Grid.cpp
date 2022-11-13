#include "pch.h"
#include "Grid.h"
Grid* Grid::instance = nullptr;

Grid::Grid() : gridSize(50), nodeSize(2000), origin(-(gridSize / int(2) * nodeSize), -(gridSize / int(2) * nodeSize)), visible(false) {
	nodes = new Node * [gridSize];
	for (int i{}; i < gridSize; i++) {
		nodes[i] = new Node[gridSize];
	}

	for (int i{}; i < gridSize; i++) {
		for (int j{}; j < gridSize; j++) {
			nodes[i][j].setSize(nodeSize);

			Point position(i * nodeSize, j * nodeSize);
			nodes[i][j].setPosition(origin + position);
		}
	}
}
Grid::~Grid() {
	for (int i{}; i < gridSize; i++) {
		delete[] nodes[i];
	}

	delete[] nodes;
}

Grid* Grid::get() {
	if (instance == nullptr) {
		instance = new Grid();
	}
	return instance;
}
void Grid::render(Window& window) {
	if (visible) {
		for (int i{}; i < gridSize; i++) {
			for (int j{}; j < gridSize; j++) {
				nodes[i][j].render(window);
			}
		}
	}
}
void Grid::toggle() {
	visible = !visible;
}
Node* Grid::nodeAt(const Point& position) const {
	Point offset((position - origin) / float(nodeSize));
	return &nodes[int(offset.x)][int(offset.y)];
}
std::vector<Node*> Grid::nodesby(Node* const node) const {
	std::vector<Node*> nodes{};
	for (int i{}; i < gridSize; i++) {
		for (int j{}; j < gridSize; j++) {
			if (&nodes[i][j] == node) {
				if (i > 0) {
					nodes.push_back(&nodes[i - 1][j]);
					if (j > 0) {
						nodes.push_back(&nodes[i - 1][j - 1]);
					}

					if ((j + 1) < gridSize) {
						nodes.push_back(&nodes[i - 1][j + 1]);
					}
				}

				if ((i + 1) < gridSize) {
					nodes.push_back(&nodes[i + 1][j]);
					if (j > 0) {
						nodes.push_back(&nodes[i + 1][j - 1]);
					}

					if ((j + 1) < gridSize) {
						nodes.push_back(&nodes[i + 1][j + 1]);
					}
				}

				if (j > 0) {
					nodes.push_back(&nodes[i][j - 1]);
				}

				if ((j + 1) < gridSize) {
					nodes.push_back(&nodes[i][j + 1]);
				}

				break;
			}
		}
	}

	return nodes;
}