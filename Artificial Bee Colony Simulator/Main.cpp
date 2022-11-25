#include "pch.h"

int main() {
	bool showing{ true };
	bool running{ true };

	sf::ContextSettings settings;
	settings.antialiasingLevel = 20;

	Point camera(0, 0);
	float zoom{ 1.0F };
	sf::View view(sf::FloatRect(0, 0, 800, 600));
	view.zoom(zoom);

	Plane window(sf::VideoMode(800, 600), "Artificial Bee Colony Simulator", sf::Style::Default);
	window.setVisible(showing);
}