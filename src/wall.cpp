//
// Created by Domakingo on 04/07/2024.
//

#include "wall.hpp"

Wall::Wall(sf::Vector2f position, sf::Vector2f size, Color color) {
    wallShape.setSize(size);
    wallShape.setFillColor(color);
    wallShape.setPosition(position);
}

RectangleShape Wall::getShape() {
    return wallShape;
}
