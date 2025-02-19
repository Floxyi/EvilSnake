#include "../include/game.h"

#include "../include/constants.h"
#include "../include/font_manager.h"
#include "../include/game_utils.h"
#include "../include/screen_manager.h"
#include "../include/sound_manager.h"
#include "raylib.h"

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

    if (state == GameState::PLAYING) {
        if (IsKeyPressed(Constants::KEY_PAUSE)) {
            endTime = GetTime();
            state = GameState::PAUSED;
        }
    }

    if (state == GameState::PAUSED) {
        if (IsKeyPressed(Constants::KEY_CONTINUE)) {
            endTime = 0.0f;
            state = GameState::PLAYING;
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

void Game::handleDirectionChange(Direction dir)
{
    if (state == GameState::MENU) {
        SoundManager::getInstance().play(SoundManager::SOUND_START);
        startTime = GetTime();
        state = GameState::PLAYING;
    }
    snake.setDirection(dir);
}

void Game::changeGameMode()
{
    static const std::vector<GameMode> gameModes = {GameMode::NORMAL, GameMode::FAST, GameMode::WALLS};
    GameMode newMode = gameModes[GetRandomValue(0, gameModes.size() - 1)];

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

void Game::drawGameObjects()
{
    DrawRectangle(foodPosition.x, foodPosition.y, Constants::CELL_SIZE, Constants::CELL_SIZE, RED);
    snake.draw();
    for (const Vector2 &wallPosition : wallPositions) {
        DrawRectangle(wallPosition.x, wallPosition.y, Constants::CELL_SIZE, Constants::CELL_SIZE, BLACK);
    }
}

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

void Game::draw()
{
    BeginDrawing();
    drawGrid();
    drawGameObjects();
    drawUI();
    EndDrawing();
}

void Game::run()
{
    while (!WindowShouldClose()) {
        handleInput();
        update();
        draw();
    }

    CloseWindow();
}
