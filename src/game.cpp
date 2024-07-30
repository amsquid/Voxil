#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

#include <iostream>

#include "game.hpp"

void Game::draw() {
	sf::RectangleShape shape(sf::Vector2f(100, 100));
	shape.setFillColor(sf::Color::Green);

	Game::window->clear();
	Game::window->draw(shape);
	Game::window->display();
}

void Game::update() {
	sf::Event event;

	while (Game::window->pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			Game::stopGame();
	}
}

void Game::loop() {
	while(this->window->isOpen()) {
		Game::update();
		Game::draw();
	}
}

void Game::startGame() {
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Voxil");
	Game::window = &window;

	Game::loop();
}

void Game::stopGame() {
	std::cout << "Stopping Game\n";

	Game::window->close();
}