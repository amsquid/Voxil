#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>

#include "game.hpp"

void Game::draw() {
	std::vector<Voxel>::iterator it;

	Game::window->clear();

	int drawn = 0;

	for(it = voxels.begin(); it < voxels.end(); it++) {		
		float x = it->position.x * .005f;
		float y = it->position.y;
		float z = it->position.z * .005f;

		float xOffset = x - camera.position.x;
		float yOffset = y - camera.position.y;
		float zOffset = z - camera.position.z;

		float xRot1 = (xOffset * cos(camera.rotation.x)) - (zOffset * sin(camera.rotation.x));
		float yRot1 = yOffset;
		float zRot1 = (xOffset * sin(camera.rotation.x)) + (zOffset * cos(camera.rotation.x));

		float xRot2 = xRot1;
		float yRot2 = (yRot1 * cos(camera.rotation.y)) - (zRot1 * sin(camera.rotation.y));
		float zRot2 = (yRot1 * sin(camera.rotation.y)) + (zRot1 * cos(camera.rotation.y));

		float distance = sqrt(
			pow(x - camera.position.x, 2) +
			pow(y - camera.position.y, 2) +
			pow(z - camera.position.z, 2)
		);

		if(zRot2 <= 0) continue;
		if(distance > 0.6f) continue;

		float xProjected = xRot2 / (zRot2 * 0.001f);
		float yProjected = yRot2 / (zRot2 * 0.001f);

		float xDraw = xProjected + (Game::window->getSize().x / 2);
		float yDraw = yProjected + (Game::window->getSize().y / 2);

		float size = 1 / (zRot2 / 10);
		//float size = 10;

		std::cout << distance << " " << size << "\n";

		if(
			(xDraw < -size || xDraw > window->getSize().x) ||
			(yDraw < -size || yDraw > window->getSize().y)
		) {
			continue;
		}

		//std::cout << xProjected << " " << yProjected << "\n";

		sf::VertexArray quad(sf::Quads, 4);

		quad[0].position = sf::Vector2f(xDraw + (size / 2), yDraw + (size / 2));
		quad[1].position = sf::Vector2f(xDraw - (size / 2), yDraw + (size / 2));
		quad[2].position = sf::Vector2f(xDraw - (size / 2), yDraw - (size / 2));
		quad[3].position = sf::Vector2f(xDraw + (size / 2), yDraw - (size / 2));

		quad[0].color = sf::Color::Red;
		quad[1].color = sf::Color::Green;
		quad[2].color = sf::Color::Yellow;
		quad[3].color = sf::Color::Blue;

		drawn++;
		
		Game::window->draw(quad);
	}

	std::cout << "DRAWN: " << drawn << "\n";

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

	if(keysPressed.at(sf::Keyboard::Scan::W)) camera.position.z += 0.01f;
	if(keysPressed.at(sf::Keyboard::Scan::S)) camera.position.z -= 0.01f;
	if(keysPressed.at(sf::Keyboard::Scan::A)) camera.position.x -= 0.01f;
	if(keysPressed.at(sf::Keyboard::Scan::D)) camera.position.x += 0.01f;
	if(keysPressed.at(sf::Keyboard::Scan::Space)) camera.position.y -= 0.01f;
	if(keysPressed.at(sf::Keyboard::Scan::LControl)) camera.position.y += 0.01f;

	if(keysPressed.at(sf::Keyboard::Scan::Up)) camera.rotation.y -= 0.01f;
	if(keysPressed.at(sf::Keyboard::Scan::Down)) camera.rotation.y += 0.01f;
	if(keysPressed.at(sf::Keyboard::Scan::Left)) camera.rotation.x -= 0.01f;
	if(keysPressed.at(sf::Keyboard::Scan::Right)) camera.rotation.x += 0.01f;


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

	Game::window->setFramerateLimit(60);

	for(int i = 0; i < sf::Keyboard::Scan::ScancodeCount; i++) {
		keysPressed.push_back(false);
	}

	for(int x = -100; x < 100; x++) {
		for(int z = -100; z < 100; z++) {
			Voxel voxel(x, 0, z);

			voxel.color = sf::Color(rand() % 255, rand() % 255, rand() % 255);

			voxels.push_back(voxel);
		}
	}

	//voxels.push_back(Voxel(0,0,1));

	Game::loop();
}

void Game::stopGame() {
	std::cout << "Stopping Game\n";

	Game::window->close();
}