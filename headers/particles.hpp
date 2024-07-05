#ifndef CPP_SNAKE_PARTICLES_HPP
#define CPP_SNAKE_PARTICLES_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class Particles {
private:
    sf::Vector2f velocity;
    float distanceTraveled;
    float maxDistance{};
    sf::Uint8 opacity;

public:
    Particles(float x, float y, sf::Color color, float maxDistance, float speed, int particleSize);

    void update();

    sf::RectangleShape shape;
};

void generateParticles(std::vector<Particles>& particles, int count, float x, float y, sf::Color color, float maxDistance, float speed, int particleSize);

#endif //CPP_SNAKE_PARTICLES_HPP
