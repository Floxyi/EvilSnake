/**
 * @file game.cpp
 * @brief Implementation of the Game class for the Evil Snake game
 *
 * This file contains the implementation of the main game loop, game state management,
 * input handling, and rendering logic for the Evil Snake game. The game features
 * multiple modes (normal, fast, and walls) and states (menu, playing, paused, etc.).
 */

#include "../include/game.h"

#include "../include/constants.h"
#include "../include/font_manager.h"
#include "../include/game_utils.h"
#include "../include/screen_manager.h"
#include "../include/sound_manager.h"
#include "raylib.h"

/**
 * @brief Constructor for the Game class
 *
 * Initializes the game window, loads resources, and sets up initial game state.
 * The snake is placed at a random position and the first food item is spawned.
 */
Game::Game()
    : state(GameState::MENU),
      mode(GameMode::NORMAL),
      score(0),
      timeSinceLastMove(0.0f),
      timeSinceLastEventCheck(0.0f),
      startTime(0.0f),
      endTime(0.0f),
      snake(GameUtils::getRandomGridPosition()),
      wallPositions{}
{
    foodPosition = GameUtils::getRandomFoodPosition(snake.body, wallPositions);
    InitWindow(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT, "Evil Snake");
    FontManager::getInstance().initFonts();
    SoundManager::getInstance().initSounds();
}

/**
 * @brief Resets the game to its initial state
 *
 * Clears all game progress and returns to the menu state. This includes:
 * - Resetting score and timing information
 * - Clearing wall positions
 * - Resetting snake position and speed
 * - Generating new food position
 */
void Game::reset()
{
    score = 0;
    startTime = 0.0f;
    endTime = 0.0f;
    state = GameState::MENU;
    mode = GameMode::NORMAL;
    wallPositions.clear();

    snake.speed = Constants::DEFAULT_SNAKE_SPEED;
    snake.resetToPosition(GameUtils::getRandomGridPosition());
    foodPosition = GameUtils::getRandomFoodPosition(snake.body, wallPositions);
}

/**
 * @brief Handles all input events for the game
 *
 * Processes keyboard input based on the current game state, including:
 * - Screenshot functionality (available in all states)
 * - Game navigation (quit, pause, resume)
 * - Snake movement controls (WASD and arrow keys)
 * - Menu navigation
 */
void Game::handleInput()
{
    if (IsKeyPressed(Constants::KEY_SCREENSHOT)) {
        GameUtils::takeScreenshot();
    }

    if (state == GameState::PLAYING || state == GameState::FINISHED || state == GameState::GAME_OVER ||
        state == GameState::PAUSED) {
        if (IsKeyPressed(Constants::KEY_QUIT)) {
            reset();
        }
    }

    if (state == GameState::PLAYING || state == GameState::PAUSED) {
        if (IsKeyPressed(Constants::KEY_PAUSE)) {
            endTime = GetTime();
            state = state == GameState::PLAYING ? GameState::PAUSED : GameState::PLAYING;
        }
    }

    if (state == GameState::MENU) {
        if (IsKeyPressed(Constants::KEY_OPEN_SCREENSHOTS)) {
            GameUtils::openScreenshotsFolder();
        }
    }

    if (state == GameState::PLAYING || state == GameState::MENU) {
        std::unordered_map<int, Direction> keyMap = {
            {KEY_UP, Direction::UP},
            {KEY_W, Direction::UP},
            {KEY_DOWN, Direction::DOWN},
            {KEY_S, Direction::DOWN},
            {KEY_LEFT, Direction::LEFT},
            {KEY_A, Direction::LEFT},
            {KEY_RIGHT, Direction::RIGHT},
            {KEY_D, Direction::RIGHT},
        };

        for (const auto &[key, dir] : keyMap) {
            if (IsKeyPressed(key)) {
                handleDirectionChange(dir);
            }
        }
    }
}

/**
 * @brief Handles direction changes for the snake
 *
 * @param dir The new direction to set for the snake
 *
 * If called from the menu state, this also starts the game.
 * Otherwise, it updates the snake's direction during gameplay.
 */
void Game::handleDirectionChange(Direction dir)
{
    if (state == GameState::MENU) {
        SoundManager::getInstance().play(SoundManager::SOUND_START);
        startTime = GetTime();
        state = GameState::PLAYING;
    }
    snake.setDirection(dir);
}

/**
 * @brief Changes the current game mode randomly
 *
 * Switches between three possible modes:
 * - NORMAL: Default snake speed, no walls
 * - FAST: Increased snake speed, no walls
 * - WALLS: Default speed with randomly placed wall obstacles
 *
 * The mode change is accompanied by a sound effect and appropriate game modifications.
 */
void Game::changeGameMode()
{
    static const std::vector<GameMode> gameModes = {GameMode::NORMAL, GameMode::FAST, GameMode::WALLS};
    GameMode newMode = gameModes[GetRandomValue(0, (int) gameModes.size() - 1)];

    if (mode == newMode) return;

    mode = newMode;
    snake.speed = (mode == GameMode::FAST) ? Constants::FAST_SNAKE_SPEED : Constants::DEFAULT_SNAKE_SPEED;
    wallPositions.clear();

    if (mode == GameMode::WALLS) {
        for (int i = 0; i < Constants::WALL_AMOUNT; i++) {
            wallPositions.push_back(GameUtils::getRandomGridPosition());
        }
    }

    SoundManager::getInstance().play(SoundManager::SOUND_START);
}

/**
 * @brief Updates the game state
 *
 * Handles game logic including:
 * - Checking for win condition
 * - Moving the snake
 * - Detecting collisions
 * - Managing food collection
 * - Triggering game mode changes
 */
void Game::update()
{
    if (score >= Constants::WINNING_SCORE) {
        state = GameState::FINISHED;
    }

    if (state != GameState::PLAYING) {
        return;
    }

    timeSinceLastMove += GetFrameTime();
    timeSinceLastEventCheck += GetFrameTime();

    if (timeSinceLastEventCheck >= Constants::EVENT_INTERVAL) {
        timeSinceLastEventCheck = 0.0f;
        changeGameMode();
    }

    if (timeSinceLastMove >= snake.speed) {
        timeSinceLastMove = 0.0f;

        if (snake.moveAndCheckForFood(foodPosition)) {
            SoundManager::getInstance().play(SoundManager::SOUND_EAT);
            score++;
            foodPosition = GameUtils::getRandomFoodPosition(snake.body, wallPositions);
        }

        if (snake.hasCollided(wallPositions)) {
            SoundManager::getInstance().play(SoundManager::SOUND_EXPLOSION);
            endTime = GetTime();
            state = GameState::GAME_OVER;
        }
    }
}

/**
 * @brief Draws the game grid
 *
 * Renders the background grid that serves as the game board.
 * The grid is drawn using light gray lines on a white background.
 */
void Game::drawGrid()
{
    ClearBackground(RAYWHITE);
    for (int x = 0; x < Constants::WINDOW_WIDTH; x += Constants::CELL_SIZE) {
        DrawLine(x, 0, x, Constants::WINDOW_HEIGHT, LIGHTGRAY);
    }
    for (int y = 0; y < Constants::WINDOW_HEIGHT; y += Constants::CELL_SIZE) {
        DrawLine(0, y, Constants::WINDOW_WIDTH, y, LIGHTGRAY);
    }
}

/**
 * @brief Draws all game objects
 *
 * Renders the main game elements:
 * - Food (red square)
 * - Snake (handled by Snake class)
 * - Walls (black squares, only in WALLS mode)
 */
void Game::drawGameObjects()
{
    DrawRectangle(foodPosition.x, foodPosition.y, Constants::CELL_SIZE, Constants::CELL_SIZE, RED);
    snake.draw();
    for (const Vector2 &wallPosition : wallPositions) {
        DrawRectangle(wallPosition.x, wallPosition.y, Constants::CELL_SIZE, Constants::CELL_SIZE, BLACK);
    }
}

/**
 * @brief Draws the user interface
 *
 * Renders the appropriate UI elements based on the current game state:
 * - Menu screen
 * - Playing screen (score, mode, time)
 * - Pause screen
 * - Game over screen
 * - Victory screen
 */
void Game::drawUI()
{
    switch (state) {
        case GameState::MENU:
            ScreenManager::getInstance().drawMenuScreen();
            break;
        case GameState::PLAYING:
            ScreenManager::getInstance().drawPlayingScreen(
                score, GameUtils::getFormattedGameMode(mode), GameUtils::getFormattedGameTime(startTime, GetTime()));
            break;
        case GameState::PAUSED:
            ScreenManager::getInstance().drawPauseScreen(score, GameUtils::getFormattedGameTime(startTime, endTime));
            break;
        case GameState::GAME_OVER:
            ScreenManager::getInstance().drawGameOverScreen(score, GameUtils::getFormattedGameTime(startTime, endTime));
            break;
        case GameState::FINISHED:
            ScreenManager::getInstance().drawFinishedScreen(score, GameUtils::getFormattedGameTime(startTime, endTime));
            break;
    }
}

/**
 * @brief Performs the complete draw cycle
 *
 * Handles all rendering operations in the correct order:
 * 1. Begin the drawing context
 * 2. Draw the background grid
 * 3. Draw game objects
 * 4. Draw UI elements
 * 5. End the drawing context
 */
void Game::draw()
{
    BeginDrawing();
    drawGrid();
    drawGameObjects();
    drawUI();
    EndDrawing();
}

/**
 * @brief Main game loop
 *
 * Runs the game until the window is closed:
 * 1. Process input
 * 2. Update game state
 * 3. Render frame
 *
 * Properly closes the window when the game ends.
 */
void Game::run()
{
    while (!WindowShouldClose()) {
        handleInput();
        update();
        draw();
    }

    CloseWindow();
}
