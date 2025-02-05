#include "../include/Game.h"

#include "../include/Constants.h"
#include "../include/FontManager.h"
#include "../include/GameUtils.h"
#include "../include/ScreenManager.h"
#include "../include/SoundManager.h"
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
    wallPositions = {};

    snake.speed = Constants::DEFAULT_SNAKE_SPEED;
    snake.resetToPosition(GameUtils::getRandomGridPosition());
    foodPosition = GameUtils::getRandomWallPosition(snake.body, foodPosition);
}

bool Game::isGameFinished() const
{
    return score >= Constants::CELL_AMOUNT_Y * Constants::WINDOW_WIDTH / Constants::CELL_SIZE;
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
        if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) {
            handleDirectionChange(Direction::UP);
        }
        if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) {
            handleDirectionChange(Direction::DOWN);
        }
        if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) {
            handleDirectionChange(Direction::LEFT);
        }
        if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) {
            handleDirectionChange(Direction::RIGHT);
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
    int random = GetRandomValue(0, 2);

    if (random == 0 && mode != GameMode::NORMAL) {
        mode = GameMode::NORMAL;
        snake.speed = Constants::DEFAULT_SNAKE_SPEED;
        wallPositions = {};
        SoundManager::getInstance().play(SoundManager::SOUND_START);
    }

    if (random == 1 && mode != GameMode::FAST) {
        mode = GameMode::FAST;
        snake.speed = Constants::FAST_SNAKE_SPEED;
        wallPositions = {};
        SoundManager::getInstance().play(SoundManager::SOUND_START);
    }

    if (random == 2 && mode != GameMode::WALLS) {
        mode = GameMode::WALLS;
        snake.speed = Constants::DEFAULT_SNAKE_SPEED;
        wallPositions = {};
        for (int i = 0; i < Constants::WALL_AMOUNT; i++) {
            wallPositions.push_back(GameUtils::getRandomGridPosition());
        }
        SoundManager::getInstance().play(SoundManager::SOUND_START);
    }
}

void Game::update()
{
    if (isGameFinished()) {
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
            ScreenManager::getInstance().drawGameFinishedScreen(
                score, GameUtils::getFormattedGameTime(startTime, endTime));
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
