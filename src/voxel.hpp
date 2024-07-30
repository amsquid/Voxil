#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector3.hpp>
class Voxel {
public:
    sf::Vector3i position;
    int roughness;
    sf::Color color;
};