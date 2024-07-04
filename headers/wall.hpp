//
// Created by Domakingo on 04/07/2024.
//

#ifndef CPP_SNAKE_WALL_HPP
#define CPP_SNAKE_WALL_HPP

#include <SFML/Graphics.hpp>

using namespace sf;

class Wall {
private:
    RectangleShape wallShape;

public:
    Wall(Vector2f position, Vector2f size, Color color);

    RectangleShape getShape();
};


#endif //CPP_SNAKE_WALL_HPP
