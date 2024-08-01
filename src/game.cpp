#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/VertexBuffer.hpp>
#include <SFML/System/Vector2.hpp>

#include <SFML/System/Vector3.hpp>
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

	sf::VertexArray verticies(sf::Quads, voxels.size() * 4);
	int i = 0;

	for(it = voxels.begin(); it < voxels.end(); it++) {		
		float x = it->position.x * .005f;
		float y = it->position.y * .005f;
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
		//if(distance > 0.6f) continue;

		float xProjected = xRot2 / (zRot2 * 0.001f);
		float yProjected = yRot2 / (zRot2 * 0.001f);

		float xDraw = xProjected + (Game::window->getSize().x / 2);
		float yDraw = yProjected + (Game::window->getSize().y / 2);

		float size = 1 / (zRot2 / 10);
		//float size = 10;

		//std::cout << distance << " " << size << "\n";

		if(
			(xDraw < -size || xDraw > window->getSize().x) ||
			(yDraw < -size || yDraw > window->getSize().y)
		) {
			continue;
		}

		//std::cout << xProjected << " " << yProjected << "\n";

		verticies[i * 4 + 0].position = sf::Vector2f(xDraw + (size / 2), yDraw + (size / 2));
		verticies[i * 4 + 1].position = sf::Vector2f(xDraw - (size / 2), yDraw + (size / 2));
		verticies[i * 4 + 2].position = sf::Vector2f(xDraw - (size / 2), yDraw - (size / 2));
		verticies[i * 4 + 3].position = sf::Vector2f(xDraw + (size / 2), yDraw - (size / 2));

		verticies[i * 4 + 0].color = it->color;
		verticies[i * 4 + 1].color = it->color;
		verticies[i * 4 + 2].color = it->color;
		verticies[i * 4 + 3].color = it->color;

		drawn++;
		

		i++;
	}

	Game::window->draw(verticies);

	std::cout << "DRAWN: " << drawn << " FPS: " << Game::fps << "\n";

	Game::window->display();
}

void Game::update() {
	// Resetting Camera Velocity
	camera.velocity = sf::Vector3f();

	// Movement and Rotation of camera
	if(keysPressed.at(sf::Keyboard::Scan::W)) camera.velocity.z = 0.1f;
	if(keysPressed.at(sf::Keyboard::Scan::S)) camera.velocity.z = -0.1f;
	if(keysPressed.at(sf::Keyboard::Scan::A)) camera.velocity.x = -0.1f;
	if(keysPressed.at(sf::Keyboard::Scan::D)) camera.velocity.x = 0.1f;
	if(keysPressed.at(sf::Keyboard::Scan::Space)) camera.velocity.y = -0.1f;
	if(keysPressed.at(sf::Keyboard::Scan::LControl)) camera.velocity.y = 0.1f;

	if(keysPressed.at(sf::Keyboard::Scan::Up)) camera.rotation.y -= 0.02f;
	if(keysPressed.at(sf::Keyboard::Scan::Down)) camera.rotation.y += 0.02f;
	if(keysPressed.at(sf::Keyboard::Scan::Left)) camera.rotation.x -= 0.02f;
	if(keysPressed.at(sf::Keyboard::Scan::Right)) camera.rotation.x += 0.02f;

	// Moving entities
	std::vector<Entity>::iterator it;

	for(it = entities.begin(); it < entities.end(); it++) {
		it->move(Game::deltaTime);
	}

	camera.move(Game::deltaTime);
}

void Game::pollEvents() {
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
}

void Game::loop() {
	sf::Clock deltaClock;
	sf::Clock fpsClock;

	Game::deltaTime = deltaClock.restart(); // Presetting the deltatime

	float currentTime;
	float lastTime;

	while(Game::window->isOpen()) {
		Game::pollEvents();

		Game::deltaTime = deltaClock.restart();

		Game::update();
		Game::draw();

		frameCount++;

		if(fpsClock.getElapsedTime() >= fpsUpdate) {
			fps = frameCount / fpsUpdate.asSeconds();
			frameCount = 0;
			fpsClock.restart();
		}
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

			voxel.color = sf::Color(64 + rand() % 50, 255 - rand() % 50, 71 + rand() % 50);

			voxels.push_back(voxel);
		}

	}

	for(int y = 0; y > -20; y--) {
		Voxel voxel(0, y, 1);

		voxel.color = sf::Color(rand() % 255, rand() % 255, rand() % 255);

		voxels.push_back(voxel);
	}

	Game::loop();
}

void Game::stopGame() {
	std::cout << "Stopping Game\n";

	Game::window->close();
}