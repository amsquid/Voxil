#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <iostream>
#include <vector>

#include "game.hpp"

void Game::draw() {
	std::vector<Voxel>::iterator it;

	Game::window->clear();

	for(it = voxels.begin(); it < voxels.end(); it++) {		
		int x = it->position.x;
		int y = it->position.y;
		int z = it->position.z;

		float xOffset = x - camera.position.x;
		float yOffset = y - camera.position.y;
		float zOffset = z - camera.position.z;

		if(zOffset <= 0) continue;

		float xProjected = xOffset / zOffset;
		float yProjected = yOffset / zOffset;

		sf::RectangleShape shape(sf::Vector2f(10, 10));
		shape.setFillColor(sf::Color::White);

		shape.setPosition(
			xProjected + (Game::window->getSize().x / 2), 
			yProjected + (Game::window->getSize().y / 2)
		);

		
		Game::window->draw(shape);
	}

	Game::window->display();
}

void Game::update() {
	sf::Event event;

	while (Game::window->pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			Game::stopGame();
			
		if(event.type == sf::Event::KeyPressed) {
			keysPressed.at(event.key.scancode) = true;
		}

		if(event.type == sf::Event::KeyReleased) {
			keysPressed.at(event.key.scancode) = false;
		}
	}

	if(!keysPressed.at(sf::Keyboard::Scan::LShift)) {
		if(keysPressed.at(sf::Keyboard::Scan::W)) camera.position.y -= 0.01f;
		if(keysPressed.at(sf::Keyboard::Scan::S)) camera.position.y += 0.01f;
		if(keysPressed.at(sf::Keyboard::Scan::A)) camera.position.x -= 0.01f;
		if(keysPressed.at(sf::Keyboard::Scan::D)) camera.position.x += 0.01f;
	} else {
		if(keysPressed.at(sf::Keyboard::Scan::W)) camera.position.z += 0.001f;
		if(keysPressed.at(sf::Keyboard::Scan::S)) camera.position.z -= 0.001f;

	}


}

void Game::loop() {
	while(Game::window->isOpen()) {
		Game::update();
		Game::draw();
	}
}

void Game::startGame() {
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Voxil", sf::Style::Close | sf::Style::Titlebar);
	Game::window = &window;

	Game::window->setKeyRepeatEnabled(false);

	for(int i = 0; i < sf::Keyboard::Scan::ScancodeCount; i++) {
		keysPressed.push_back(false);
	}

	for(int x = -10; x < 10; x++) {
		for(int z = -10; z < 10; z++) {
			voxels.push_back(Voxel(x, 0, z));
		}
	}



	Game::loop();
}

void Game::stopGame() {
	std::cout << "Stopping Game\n";

	Game::window->close();
}