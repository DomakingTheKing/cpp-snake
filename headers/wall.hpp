//
// Created by Domakingo on 04/07/2024.
//

#ifndef CPP_SNAKE_WALL_HPP
#define CPP_SNAKE_WALL_HPP

#include <SFML/Graphics.hpp>
#include <opencv2/core/types.hpp>

class Wall {
private:
    sf::RectangleShape wallShape;

public:
    Wall(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color);
    Wall(const sf::Vector2f& position, const sf::Vector2f& size, const cv::Scalar& color);

    sf::RectangleShape getShape() const;
};

#endif //CPP_SNAKE_WALL_HPP
