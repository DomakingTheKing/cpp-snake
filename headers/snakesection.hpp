//
// Created by Domakingo on 04/07/2024.
//

#ifndef CPP_SNAKE_SNAKESECTION_HPP
#define CPP_SNAKE_SNAKESECTION_HPP

#include <SFML/Graphics.hpp>

using namespace sf;

class SnakeSection {
private:
    Vector2f position;
    RectangleShape section;

public:
    explicit SnakeSection(Vector2f startPosition);

    Vector2f getPosition();
    void setPosition(Vector2f newPosition);

    RectangleShape getShape();

    void update();

};


#endif //CPP_SNAKE_SNAKESECTION_HPP
