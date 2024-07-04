//
// Created by Domakingo on 04/07/2024.
//

#include "Engine.hpp"
#include "soundengine.hpp"
#include <iostream>
#include <thread>
#include <chrono>

void Engine::update() {
    // Update snake sections positions
    if (timeSinceLastMove.asSeconds() >= seconds(1.f / float(speed)).asSeconds()) {
        Vector2f thisSectionPosition = snake[0].getPosition();
        Vector2f lastSectionPosition = thisSectionPosition;

        // Is there anything in the input queue?
        if (!directionQueue.empty()) {
            // Make sure we don't reserve direction
            switch (snakeDirection) {
                case Direction::UP:
                    if (directionQueue.front() != Direction::DOWN && directionQueue.front() != Direction::UP) {
                        snakeDirection = directionQueue.front();
                        std::thread([&engine]() { sf::Sound sound = engine.getSound("example.wav", 50); sound.play(); }).detach();
                    }
                    break;
                case Direction::DOWN:
                    if (directionQueue.front() != Direction::UP && directionQueue.front() != Direction::DOWN) {
                        snakeDirection = directionQueue.front();
                        playPitchedSound("change_direction.wav", 30);
                    }
                    break;
                case Direction::LEFT:
                    if (directionQueue.front() != Direction::RIGHT && directionQueue.front() != Direction::LEFT) {
                        snakeDirection = directionQueue.front();
                        playPitchedSound("change_direction.wav", 30);
                    }
                    break;
                case Direction::RIGHT:
                    if (directionQueue.front() != Direction::LEFT && directionQueue.front() != Direction::RIGHT) {
                        snakeDirection = directionQueue.front();
                        playPitchedSound("change_direction.wav", 30);
                    }
                    break;
            }
            directionQueue.pop_front();
        }

        // Update Score
        score += snake.size() + (applesEatenTotal + 1);
        scoreText.setString(to_string(score));
        FloatRect scoreTextBounds = scoreText.getLocalBounds();
        scoreText.setPosition(Vector2f(resolution.x - scoreTextBounds.width - 40, 3));

        // Do we need to grow the snake?
        if (sectionsToAdd) {
            addSnakeSection();
            sectionsToAdd--;
        }

        // Update the snake's head position
        switch (snakeDirection) {
            case Direction::UP:
                snake[0].setPosition(Vector2f(thisSectionPosition.x, thisSectionPosition.y - 40));
                break;
            case Direction::DOWN:
                snake[0].setPosition(Vector2f(thisSectionPosition.x, thisSectionPosition.y + 40));
                break;
            case Direction::LEFT:
                snake[0].setPosition(Vector2f(thisSectionPosition.x - 40, thisSectionPosition.y));
                break;
            case Direction::RIGHT:
                snake[0].setPosition(Vector2f(thisSectionPosition.x + 40, thisSectionPosition.y));
                break;
        }

        // Update the snake tail positions
        for (int s = 1; s < snake.size(); s++) {
            thisSectionPosition = snake[s].getPosition();
            snake[s].setPosition(lastSectionPosition);
            lastSectionPosition = thisSectionPosition;
        }

        // Run snake section update function
        for (auto & section : snake) {
            section.update();
        }

        // Collision detection - Apple
        if (snake[0].getShape().getGlobalBounds().intersects(apple.getSprite().getGlobalBounds())) {
            playPitchedSound("eat_apple.wav", 80);

            applesEatenThisLevel++;
            applesEatenTotal++;

            applesEatenText.setString("apples " + to_string(applesEatenTotal));
            FloatRect currentLevelTextBounds = currentLevelText.getGlobalBounds();

            applesEatenText.setPosition(Vector2f(currentLevelTextBounds.left + currentLevelTextBounds.width + 56, 1));

            bool beginningNewLevel = false;
            if (applesEatenThisLevel >= 10) {
                // Begin the next level if there are more,
                // otherwise, just stay on the last level and keep getting harder
                if (currentLevel < maxLevels) {
                    beginningNewLevel = true;
                    beginNextLevel();
                }
            }

            if (!beginningNewLevel) {
                sectionsToAdd  += 3;
                speed++;
                moveApple();
            }
        }

        // Collision detection - Snake Body
        for (int s = 1; s < snake.size(); s++) {
            if (snake[0].getShape().getGlobalBounds().intersects(snake[s].getShape().getGlobalBounds())) {
                // Game Over
                playSound("crowd_boo_lose.wav", 80);
                currentGameState = GameState::GAMEOVER;
            }
        }

        // Collision detection - Walls
        for (auto & wall : wallSections) {
            if (snake[0].getShape().getGlobalBounds().intersects(wall.getShape().getGlobalBounds())) {
                // Game Over
                playSound("crowd_boo_lose.wav", 80);
                currentGameState = GameState::GAMEOVER;
            }
        }

        // Reset the last move timer
        timeSinceLastMove = Time::Zero;
    } // END update snake sections positions
}
