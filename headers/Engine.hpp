//
// Created by Domakingo on 04/07/2024.
//

#ifndef CPP_SNAKE_ENGINE_HPP
#define CPP_SNAKE_ENGINE_HPP

#include "snakesection.hpp"
#include "apple.hpp"
#include "wall.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <vector>
#include <deque>
#include <fstream>

using namespace sf; // (SFML CLASS)
using namespace std;


class Engine {
private:
    // Window
    Vector2f resolution;
    RenderWindow window;
    const unsigned int FPS = 60;
    static const Time TimePerFrame;

    vector<SnakeSection> snake;

    int snakeDirection{};
    deque<int> directionQueue; // Queue for direction key presses
    int speed{};
    int sectionsToAdd{};
    int applesEatenThisLevel;
    int applesEatenTotal;
    unsigned long long int score;

    Apple apple;

    vector<Wall> wallSections;
    int currentLevel{};
    int maxLevels;
    vector<String> levels;

    Font mainFont;
    Text titleText;
    Text applesEatenText;
    Text currentLevelText;
    Text scoreText;
    Text gameOverText;
    Text pressRText;

    Time timeSinceLastMove;

    int currentGameState{};
    int lastGameState{}; // For storing the last state the game was in when pausing

public:
    enum Direction { UP, RIGHT, DOWN, LEFT };
    enum GameState { RUNNING, PAUSED, GAMEOVER };
    Engine();

    void input();
    void addDirection(int newDirection);
    void update();
    void draw();

    static void setupText(Text *textItem, const Font &font, const String &value, int size, Color color);

    void newSnake();
    void addSnakeSection();

    void moveApple();

    void checkLevelFiles();
    void loadLevel(int levelNumber);

    void startGame();
    void beginNextLevel();

    void togglePause();

    static void playPitchedSound(const String& fileName);

    // The main loop will be in the run function
    void run();
};


#endif //CPP_SNAKE_ENGINE_HPP
