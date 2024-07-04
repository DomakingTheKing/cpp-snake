//
// Created by Domakingo on 04/07/2024.
//

#include "Engine.hpp"

void Engine::draw() {
    window.clear(Color::Black);

    // Draw Grid
    sf::Color gridColor(25, 25, 25);
    int cellSize = 40;
    sf::Vector2u windowSize = window.getSize();

    // Draw vertical lines
    for (int i = 0; i * cellSize < windowSize.x; ++i) {
        auto x = static_cast<float>(i * cellSize);
        sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(x, 0), gridColor),
                sf::Vertex(sf::Vector2f(x, static_cast<float>(windowSize.y)), gridColor)
        };
        window.draw(line, 2, sf::Lines);
    }

    // Draw horizontal lines
    for (int i = 0; i * cellSize < windowSize.y; ++i) {
        auto y = static_cast<float>(i * cellSize);
        sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(0, y), gridColor),
                sf::Vertex(sf::Vector2f(static_cast<float>(windowSize.x), y), gridColor)
        };
        window.draw(line, 2, sf::Lines);
    }

    // Draw walls
    for (auto & wall : wallSections) {
        window.draw(wall.getShape());
    }

    // Draw apple
    window.draw(apple.getSprite());

    // Draw snake sections
    for (auto & section : snake) {
        window.draw(section.getShape());
    }

    // Draw Text
    window.draw(titleText);
    window.draw(currentLevelText);
    window.draw(applesEatenText);
    window.draw(scoreText);

    // Draw GameOver
    if (currentGameState == GameState::GAMEOVER) {
        window.draw(gameOverText);
        window.draw(pressRText);
    }

    window.display();
}