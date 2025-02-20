/**
 * @file main.cpp
 * @brief Entry point for the Evil Snake game
 *
 * This file contains the main function that initializes and runs
 * the game. It creates a Game instance and starts the main game loop.
 */

#include "../include/game.h"

/**
 * @brief Program entry point
 *
 * Creates a Game instance and runs the main game loop.
 * The game will continue running until the window is closed
 * or the user quits.
 *
 * @return int Returns 0 on successful execution
 */
int main()
{
    Game game;
    game.run();
    return 0;
}
