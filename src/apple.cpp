//
// Created by Domakingo on 04/07/2024.
//

#include "apple.hpp"

Apple::Apple() {
    Vector2f startPosition(400, 300);
    sprite.setSize(Vector2f(40, 40));
    sprite.setFillColor(Color::Red);
    sprite.setPosition(startPosition);
}

void Apple::setPosition(sf::Vector2f newPosition) {
    sprite.setPosition(newPosition);
}

RectangleShape Apple::getSprite() {
    return sprite;
}
