#include <SFML/System/Time.hpp>
#include <SFML/System/Vector3.hpp>

class Entity {
public:
    sf::Vector3f position;
    sf::Vector3f velocity;

    sf::Vector3f rotation;

    void move(sf::Time deltaTime) {
        float dt = deltaTime.asSeconds();

        this->position.x += velocity.x * dt;
        this->position.y += velocity.y * dt;
        this->position.z += velocity.z * dt;
    }
};

class Camera : public Entity {};