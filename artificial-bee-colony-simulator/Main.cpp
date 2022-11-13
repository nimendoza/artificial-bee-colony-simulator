#include "World.h"
#include "Hives.h"
#include "Bees.h"
#include "Foodsources.h"
#include "Grid.h"
const int TICKS(24 * 30 * 3 / 2);
const float CAMERA_SPEED{ 300.0F };

int main() {
	// TOGGLE FROM DEBUG TO RELEASE

	bool rendering = true;
	bool running = true;

	sf::ContextSettings settings;
	settings.antialiasingLevel = 20;

	Point camera(0, 0);
	float zoom{ 1.00F };
	sf::View view(sf::FloatRect(0, 0, 800, 600));
	view.setCenter(Hives::get()->list[0]->center);
	view.zoom(zoom);

	Window window(sf::VideoMode(800, 600), "Artificial Bee Colony Simulator", sf::Style::Default);
	window.setVisible(rendering);

	// CHANGE THIS
	std::string directory = "C:/Users/Owner/OneDrive/Documents/Programming/artificial-bee-colony-simulator";

	std::stringstream outputPath;
	outputPath << directory << "/Utilities/Output 0.txt";

	std::ofstream output(outputPath.str());
	output << "[Hive #]" << '\t'
		<< "[Food Amount]" << '\t'
		<< "[Total Bees]" << '\t'
		<< "[Forager Bees]" << '\t'
		<< "[Queen Bees]" << '\t'
		<< "[Drone Bees]" << '\t'
		<< "[Guard Bees]" << '\t'
		<< "[Larva]" << '\t'
		<< "[Eggs]" << '\n';

	std::stringstream inputPath;
	inputPath << directory << "/Utilities/Map 0.txt";
	World::get()->generate(inputPath.str());

	sf::Clock views; views.restart();
	sf::Clock clock; clock.restart();
	sf::Clock master; master.restart();
	while (master.getElapsedTime().asSeconds() <= TICKS) {
		if (running) {
			double time = clock.restart().asSeconds();
			Hives::get()->update(time);
			Bees::get()->update(time);
			Foodsources::get()->update(time);

			int count{ 1 };
			for (auto i{ Hives::get()->list.begin() }; i != Hives::get()->list.end(); i++, count++) {
				output << count << '\t'
					<< (*i)->food << '\t'
					<< (*i)->count[AllBeeTypes] << '\t'
					<< (*i)->count[ForagerBee] << '\t'
					<< (*i)->count[QueenBee] << '\t'
					<< (*i)->count[DroneBee] << '\t'
					<< (*i)->count[GuardBee] << '\t'
					<< (*i)->count[LarvaBee] << '\t'
					<< (*i)->count[EggBee] << '\n';
			}
		}

		if (rendering) {
			sf::Event event;
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					window.close();
				}

				if (event.type == sf::Event::KeyPressed) {
					if (event.key.code == sf::Keyboard::Numpad1) {
						Grid::get()->toggle();
					}

					if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A) {
						camera.x = -CAMERA_SPEED;
					} else if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D) {
						camera.x = CAMERA_SPEED;
					} else if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W) {
						camera.y = -CAMERA_SPEED;
					} else if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S) {
						camera.y = CAMERA_SPEED;
					} else {
						camera = sf::Vector2f(0, 0);
					}

					window.setView(view);
				}

				if (event.type == sf::Event::KeyReleased) {
					if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A) {
						camera.x = 0;
					} else if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D) {
						camera.x = 0;
					} else if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W) {
						camera.y = 0;
					} else if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S) {
						camera.y = 0;
					}
				}

				if (event.type == sf::Event::MouseWheelScrolled) {
					float scaleFactor = 1.0f - (2 * event.mouseWheelScroll.delta / 100.0f);
					if (zoom - 2 * event.mouseWheelScroll.delta / 100.0f > 0.0f) {
						zoom -= 2 * event.mouseWheelScroll.delta / 100.0f;
					}

					view.zoom(scaleFactor);
					window.setView(view);
				}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				window.close();
			}

			auto deltaTime = views.restart().asSeconds();
			view.move(camera* zoom* deltaTime);

			window.clear();
			window.setView(view);

			Hives::get()->render(window);
			Foodsources::get()->render(window);
			Bees::get()->render(window);
			Grid::get()->render(window);

			window.display();
		}
	}
}