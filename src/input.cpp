//
// Created by Domakingo on 04/07/2024.
//

#include "Engine.hpp"

void Engine::input() {
    Event event{};

    while (window.pollEvent(event)) {
        // Window closed
        if (event.type == Event::Closed) {
            window.close();
        }

        // Handle keyboard input
        if (event.type == Event::KeyPressed) {
            // Quit
            if (event.key.code == Keyboard::Escape) {
                window.close();
            }

            // Pause
            if (event.key.code == Keyboard::P) {
                togglePause();
            }

            // Restart
            if (currentGameState != GameState::PAUSED) {
                if (event.key.code == Keyboard::R) {
                    startGame();
                }
            }

            //Directions
            if (event.key.code == Keyboard::Up || event.key.code == Keyboard::W) {
                addDirection(Direction::UP);
            }
            else if (event.key.code == Keyboard::Down || event.key.code == Keyboard::S) {
                addDirection(Direction::DOWN);
            }
            else if (event.key.code == Keyboard::Left || event.key.code == Keyboard::A) {
                addDirection(Direction::LEFT);
            }
            else if (event.key.code == Keyboard::Right || event.key.code == Keyboard::D) {
                addDirection(Direction::RIGHT);
            }
        }
    }
}

void Engine::addDirection(int newDirection) {
    if (directionQueue.empty()) {
        directionQueue.emplace_back(newDirection);
    }
    else {
        if (directionQueue.back() != newDirection) {
            directionQueue.emplace_back(newDirection);
        }
    }
}
