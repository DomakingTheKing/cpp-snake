//
// Created by Domakingo on 04/07/2024.
//

#include "wall.hpp"

Wall::Wall(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color) {
    wallShape.setSize(size);
    wallShape.setFillColor(color);
    wallShape.setPosition(position);
}

Wall::Wall(const sf::Vector2f& position, const sf::Vector2f& size, const cv::Scalar& color) {
    wallShape.setSize(size);
    wallShape.setFillColor(sf::Color(static_cast<sf::Uint8>(color[0]),
                                     static_cast<sf::Uint8>(color[1]),
                                     static_cast<sf::Uint8>(color[2]),
                                     static_cast<sf::Uint8>(color[3])));
    wallShape.setPosition(position);
}

sf::RectangleShape Wall::getShape() const {
    return wallShape;
}
