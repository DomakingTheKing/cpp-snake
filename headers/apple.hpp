//
// Created by Domakingo on 04/07/2024.
//

#ifndef CPP_SNAKE_APPLE_HPP
#define CPP_SNAKE_APPLE_HPP

#include <SFML/Graphics.hpp>

using namespace sf;

class Apple {
private:
    RectangleShape sprite;

public:
    Apple();

    void setPosition(Vector2f newPosition);
    RectangleShape getSprite();
};


#endif //CPP_SNAKE_APPLE_HPP
