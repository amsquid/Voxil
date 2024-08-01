#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>

#include "voxel.hpp"
#include "entity.hpp"

class Game {
public:
	std::vector<bool> keysPressed;
	std::vector<Voxel> voxels;

	std::vector<Entity> entities;

	void startGame();
	void stopGame();

	sf::Time deltaTime;

	Camera camera;

private:
	sf::RenderWindow* window;

	void loop();
	void update();
	void draw();
};