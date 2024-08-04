#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>
class Voxel {
public:
    Voxel(int x, int y, int z) {
        Voxel::position = sf::Vector3i(x, y, z);
    }

    sf::Vector3i position;
    int roughness;
    sf::Color color;
};

class Square {
public:
	Square(float x, float y, float size, sf::Color color) {
		Square::position = sf::Vector2f(x, y);
		Square::color = color;
		Square::size = size;
	}
	
	sf::Vector2f position;
	float size;
	sf::Color color;
};