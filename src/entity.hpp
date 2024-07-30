#include <SFML/System/Vector3.hpp>

class Entity {
public:
    sf::Vector3f position;
    sf::Vector3f rotation;
};

class Camera : public Entity {};