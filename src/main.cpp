#include "../include/Constants.h"
#include "../include/Game.h"

int main() {
  Game game(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT,
            Constants::GRID_SIZE);
  game.run();
  return 0;
}
