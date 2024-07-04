//
// Created by domak on 04/07/2024.
//

#ifndef CPP_SNAKE_SOUNDENGINE_HPP
#define CPP_SNAKE_SOUNDENGINE_HPP

#include <SFML/Audio.hpp>
#include <iostream>

class SoundEngine {
public:
    sf::Sound getSound(const sf::String& fileName, int volume);
};

#endif // CPP_SNAKE_SOUNDENGINE_HPP
