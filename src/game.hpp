#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>
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
	sf::Time fpsUpdate = sf::seconds(1);

	float fps = 0.0f;
	int frameCount;

	Camera camera;

private:
	sf::RenderWindow* window;

	void loop();
	void pollEvents();
	void update();
	void draw();
};