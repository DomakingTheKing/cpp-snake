#include "Engine.hpp"
#include "soundengine.hpp"
#include "particles.hpp"
#include <iostream>
#include <thread>

void Engine::update() {
    // Update snake sections positions
    if (timeSinceLastMove.asSeconds() >= seconds(1.f / float(speed)).asSeconds()) {
        Vector2f thisSectionPosition = snake[0].getPosition();
        Vector2f lastSectionPosition = thisSectionPosition;

        // Is there anything in the input queue?
        if (!directionQueue.empty()) {
            // Make sure we don't reverse direction
            switch (snakeDirection) {
                case Direction::UP:
                    if (directionQueue.front() != Direction::DOWN && directionQueue.front() != Direction::UP) {
                        snakeDirection = directionQueue.front();
                        soundEngine.getChangeDirectionSfx()->setPitch(Engine::getRandomValue(0.5, 2));
                        soundEngine.playSound(soundEngine.getChangeDirectionSfx());
                    }
                    break;
                case Direction::DOWN:
                    if (directionQueue.front() != Direction::UP && directionQueue.front() != Direction::DOWN) {
                        snakeDirection = directionQueue.front();
                        soundEngine.getChangeDirectionSfx()->setPitch(Engine::getRandomValue(0.5, 2));
                        soundEngine.playSound(soundEngine.getChangeDirectionSfx());
                    }
                    break;
                case Direction::LEFT:
                    if (directionQueue.front() != Direction::RIGHT && directionQueue.front() != Direction::LEFT) {
                        snakeDirection = directionQueue.front();
                        soundEngine.getChangeDirectionSfx()->setPitch(Engine::getRandomValue(0.5, 2));
                        soundEngine.playSound(soundEngine.getChangeDirectionSfx());
                    }
                    break;
                case Direction::RIGHT:
                    if (directionQueue.front() != Direction::LEFT && directionQueue.front() != Direction::RIGHT) {
                        snakeDirection = directionQueue.front();
                        soundEngine.getChangeDirectionSfx()->setPitch(Engine::getRandomValue(0.5, 2));
                        soundEngine.playSound(soundEngine.getChangeDirectionSfx());
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
            soundEngine.getEatAppleSfx()->setPitch(Engine::getRandomValue(0.5, 2));
            soundEngine.playSound(soundEngine.getEatAppleSfx());

            generateParticles(particles, 10, apple.getSprite().getPosition().x, apple.getSprite().getPosition().y, sf::Color::Red, 160.0f, 999.0f, 10); // 999.0f = random speed

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
                soundEngine.playSound(soundEngine.getBonkSfx());
                // Game Over
                soundEngine.getCrowdBooLoseSfx()->setVolume(100);
                soundEngine.playSound(soundEngine.getCrowdBooLoseSfx());
                currentGameState = GameState::GAMEOVER;
            }
        }

        // Collision detection - Walls
        for (auto & wall : wallSections) {
            if (snake[0].getShape().getGlobalBounds().intersects(wall.getShape().getGlobalBounds())) {
                soundEngine.playSound(soundEngine.getBonkSfx());
                // Game Over
                soundEngine.getCrowdBooLoseSfx()->setVolume(100);
                soundEngine.playSound(soundEngine.getCrowdBooLoseSfx());
                currentGameState = GameState::GAMEOVER;
            }
        }

        // Reset the last move timer
        timeSinceLastMove = Time::Zero;
    } // END update snake sections positions
}
