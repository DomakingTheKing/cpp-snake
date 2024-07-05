#include "Particles.hpp"
#include "Engine.hpp"
#include <cmath> // Per std::cos e std::sin

void generateParticles(std::vector<Particles>& particles, int count, float x, float y, sf::Color color, float maxDistance, float speed, int particleSize) {
    if (speed == 999.0f) {
        for (int i = 0; i < count; ++i) {
            particles.emplace_back(x, y, color, maxDistance, Engine::getRandomValue(1, 5), particleSize);
        }
    }
    else {
        for (int i = 0; i < count; ++i) {
            particles.emplace_back(x, y, color, maxDistance, speed, particleSize);
        }
    }

}

Particles::Particles(float x, float y, sf::Color color, float maxDistance, float speed, int particleSize)
        : distanceTraveled(0), maxDistance(maxDistance), opacity(255) {
    shape.setSize(sf::Vector2f(particleSize, particleSize)); // Dimensione del quadrato
    shape.setFillColor(color);
    shape.setPosition(x, y);

    // Genera una direzione casuale
    float angle = static_cast<float>(Engine::getRandomValue(0, 360));

    // Calcola la velocità in base all'angolo
    velocity.x = speed * std::cos(angle * 3.14159265 / 180);
    velocity.y = speed * std::sin(angle * 3.14159265 / 180);
}

void Particles::update() {
    shape.move(velocity);
    distanceTraveled += std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);

    // Calcola la nuova opacità
    if (distanceTraveled >= maxDistance) {
        opacity = 0;
    } else {
        opacity = static_cast<sf::Uint8>(255 * (1 - distanceTraveled / maxDistance));
    }

    // Aggiorna il colore della particella con la nuova opacità
    sf::Color color = shape.getFillColor();
    color.a = opacity;
    shape.setFillColor(color);
}
