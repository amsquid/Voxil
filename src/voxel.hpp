#include <SFML/Graphics/Color.hpp>
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