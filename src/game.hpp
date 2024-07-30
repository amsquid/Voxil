#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>

#include "voxel.hpp"
#include "entity.hpp"

class Game {
public:
	std::vector<bool> keysPressed;
	std::vector<Voxel> voxels;

	void startGame();
	void stopGame();

	Camera camera;

private:
	sf::RenderWindow* window;

	void loop();
	void update();
	void draw();
};