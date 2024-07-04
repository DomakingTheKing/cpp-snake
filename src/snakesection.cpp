//
// Created by Domakingo on 04/07/2024.
//

#include "snakesection.hpp"

SnakeSection::SnakeSection(sf::Vector2f startPosition) {
    section.setSize(Vector2f(40, 40));
    section.setFillColor(Color::White);
    section.setPosition(startPosition);
    position = startPosition;
}

Vector2f SnakeSection::getPosition() {
    return position;
}

void SnakeSection::setPosition(sf::Vector2f newPosition) {
    position = newPosition;
}

RectangleShape SnakeSection::getShape() {
    return section;
}

void SnakeSection::update() {
    section.setPosition(position);
}