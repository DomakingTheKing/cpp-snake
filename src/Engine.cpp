//
// Created by Domakingo on 04/07/2024.
//

#include <SFML/Audio.hpp>
#include <iostream>
#include <cstdlib> // for rand() and srand()
#include <thread>  // for std::thread

#include <random>
#include "Engine.hpp"

using namespace std;

const sf::Time Engine::TimePerFrame = seconds(1.f / 60.f);

Engine::Engine() {
    SoundEngine soundEngine;

    resolution = Vector2f(1280, 960);
    window.create(VideoMode(static_cast<unsigned int>(resolution.x), static_cast<unsigned int>(resolution.y)), "Snake", Style::Default);
    window.setFramerateLimit(FPS);
    maxLevels = 0;
    checkLevelFiles();

    startGame();

    mainFont.loadFromFile("assets/fonts/retro.ttf");
    setupText(&titleText, mainFont, "SNAKE", 48, Color::Black);
    FloatRect titleTextBounds = titleText.getLocalBounds();
    titleText.setPosition(Vector2f(resolution.x / 2 - titleTextBounds.width / 2, -9));

    setupText(&currentLevelText, mainFont, "level 1", 32, Color::Black);
    currentLevelText.setPosition(Vector2f(40, 3));

    FloatRect currentLevelTextBounds = currentLevelText.getGlobalBounds();
    setupText(&applesEatenText, mainFont, "apples 0", 32, Color::Black);
    applesEatenText.setPosition(Vector2f(currentLevelTextBounds.left + currentLevelTextBounds.width + 56, 1));

    setupText(&scoreText, mainFont, to_string(score), 32, Color::Black);
    FloatRect scoreTextBounds = scoreText.getLocalBounds();
    scoreText.setPosition(Vector2f(resolution.x - scoreTextBounds.width - 40, 3));

    setupText(&gameOverText, mainFont, "GAME OVER", 108, Color::Yellow);
    FloatRect gameOverTextBounds = gameOverText.getLocalBounds();
    gameOverText.setPosition(Vector2f(resolution.x / 2 - gameOverTextBounds.width / 2, 300));
    gameOverText.setOutlineColor(Color::Black);
    gameOverText.setOutlineThickness(2);

    setupText(&pressRText, mainFont, "Press R to try again", 50, Color::Green);
    FloatRect pressRTextBounds = pressRText.getLocalBounds();
    pressRText.setPosition(Vector2f(resolution.x / 2 - pressRTextBounds.width / 2, 425));
    pressRText.setOutlineColor(Color::Black);
    pressRText.setOutlineThickness(2);
}

void Engine::startGame() {
    score = 0;
    speed = 5;
    snakeDirection = Direction::RIGHT;
    directionQueue.clear();

    wallSections.clear();

    timeSinceLastMove = Time::Zero;

    sectionsToAdd = 0;

    currentGameState = GameState::RUNNING;
    lastGameState = currentGameState;

    currentLevel = 1;
    loadLevel(currentLevel);

    applesEatenThisLevel = 0;
    applesEatenTotal = 0;
    currentLevelText.setString("level " + to_string(currentLevel));
    applesEatenText.setString("apples " + to_string(applesEatenTotal));

    FloatRect currentLevelTextBounds = currentLevelText.getGlobalBounds();
    applesEatenText.setPosition(Vector2f(currentLevelTextBounds.left + currentLevelTextBounds.width + 56, 1));

    scoreText.setString(to_string(score));
    FloatRect scoreTextBounds = scoreText.getLocalBounds();
    scoreText.setPosition(Vector2f(resolution.x - scoreTextBounds.width - 40, 3));

    FloatRect gameOverTextBounds = gameOverText.getLocalBounds();
    gameOverText.setPosition(Vector2f(resolution.x / 2 - gameOverTextBounds.width / 2, 300));
    gameOverText.setOutlineColor(Color::Black);
    gameOverText.setOutlineThickness(2);

    FloatRect pressRTextBounds = pressRText.getLocalBounds();
    pressRText.setPosition(Vector2f(resolution.x / 2 - pressRTextBounds.width / 2, 425));
    pressRText.setOutlineColor(Color::Black);
    pressRText.setOutlineThickness(2);

    newSnake();
    moveApple();
}

/**
 * Increment the level number, load the next level and reset the snake
 */
void Engine::beginNextLevel() {
    currentLevel++;
    wallSections.clear();
    directionQueue.clear();
    speed = 5 + currentLevel;
    snakeDirection = Direction::RIGHT;
    sectionsToAdd = 0;
    applesEatenThisLevel = 0;

    loadLevel(currentLevel);

    currentLevelText.setString("level " + to_string(currentLevel));

    FloatRect currentLevelTextBounds = currentLevelText.getGlobalBounds();
    applesEatenText.setPosition(Vector2f(currentLevelTextBounds.left + currentLevelTextBounds.width + 56, 1));

    newSnake();
    moveApple();
}

void Engine::newSnake() {
    snake.clear();
    snake.emplace_back(Vector2f(120, 120));
    snake.emplace_back(Vector2f(80, 120));
    snake.emplace_back(Vector2f(40, 120));
}

void Engine::addSnakeSection() {
    // Add the section at the same position as the last section of the snake, it will follow normally
    Vector2f newSectionPosition = snake[snake.size()-1].getPosition();
    snake.emplace_back(newSectionPosition);
}

void Engine::moveApple() {
    // Find a location to place the apple
    // Must not be inside the snake or a wall

    // Divide the field into sections the size of the apple - remove 2 to exclude the exterior walls
    Vector2f appleResolution = Vector2f(resolution.x / 40 - 2, resolution.y / 40 - 2);
    Vector2f newAppleLocation;
    bool badLocation;

    // Use C++11 random library
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disX(1, static_cast<int>(appleResolution.x));
    std::uniform_int_distribution<> disY(1, static_cast<int>(appleResolution.y));

    // Loop until we find a valid location
    do {
        badLocation = false;
        // Generate a random location
        newAppleLocation.x = static_cast<float>(disX(gen)) * 40;
        newAppleLocation.y = static_cast<float>(disY(gen)) * 40;

        // Check if it is in the snake
        for (auto & section : snake) {
            if (section.getShape().getGlobalBounds().intersects(Rect<float>(newAppleLocation.x, newAppleLocation.y, 40, 40))) {
                badLocation = true;
                break;
            }
        }

        // Check if it is in the walls
        for (auto & wall : wallSections) {
            if (wall.getShape().getGlobalBounds().intersects(Rect<float>(newAppleLocation.x, newAppleLocation.y, 40, 40))) {
                badLocation = true;
                break;
            }
        }

    } while (badLocation);

    apple.setPosition(newAppleLocation);
}

void Engine::togglePause() {
    if (currentGameState == GameState::RUNNING) {
        lastGameState = currentGameState;
        currentGameState = GameState::PAUSED;
    }
    else if (currentGameState == GameState::PAUSED) {
        currentGameState = lastGameState;
    }
}

void Engine::setupText(sf::Text *textItem, const sf::Font &font, const sf::String &value, int size, sf::Color color) {
    textItem->setFont(font);
    textItem->setString(value);
    textItem->setCharacterSize(size);
    textItem->setFillColor(color);
}

/**
 * Check the levels manifest file and make sure that we can open each level file.
 * add good level file names to the 'levels' vector and increment the maxLevels var.
 */
void Engine::checkLevelFiles() {
    // Load the levels manifest file
    ifstream levelsManifest ("assets/levels/levels.txt");
    ifstream testFile;
    for (string manifestLine; getline(levelsManifest, manifestLine);) {
        // Check that we can open the level file
        testFile.open("assets/levels/" + manifestLine);
        if (testFile.is_open()) {
            // The level file opens, add it to the list of available levels
            levels.emplace_back("assets/levels/" + manifestLine);
            testFile.close();
            maxLevels++;
        }
    }
}

/**
 * Load a level from a file and check for 'x' characters to add wall sections.
 * @param levelNumber int - the number of the level to load.
 */
void Engine::loadLevel(int levelNumber) {
    string levelFile = levels[levelNumber - 1];
    ifstream level(levelFile);
    string line;
    if (level.is_open()) {
        for (int y = 0; y < 24; y++) {
            getline(level, line);
            // Rimuovi eventuali caratteri di fine riga
            if (!line.empty() && (line.back() == '\n' || line.back() == '\r')) {
                line.pop_back();
            }
            for (int x = 0; x < 32; x++) {
                if (line[x] == 'w') {
                    wallSections.emplace_back(Vector2f(static_cast<float>(x) * 40, static_cast<float>(y) * 40), Vector2f(40, 40), Color::White);
                }
                else if (line[x] == 'x') {
                    wallSections.emplace_back(Vector2f(static_cast<float>(x) * 40, static_cast<float>(y) * 40), Vector2f(40, 40), Color::Yellow);
                }
            }
        }
    } else {
        cerr << "Errore: impossibile aprire il file " << levelFile << endl;
    }
    level.close();
}

double Engine::getRandomValue(float min, float max) {
    // Usa la libreria di numeri casuali di C++11
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(min, max);

    return dis(gen);
}

void Engine::run() {
    Clock clock;

    // Main loop - Runs until the window is closed
    while (window.isOpen()) {
        Time dt = clock.restart();

        if (currentGameState == GameState::PAUSED || currentGameState == GameState::GAMEOVER) {
            input();

            // Draw the gameover screen
            if (currentGameState == GameState::GAMEOVER) {
                draw();
            }

            sleep(milliseconds(2)); // For not overloading CPU
            continue;
        }

        timeSinceLastMove += dt;

        input();
        update();
        draw();
    }
}
