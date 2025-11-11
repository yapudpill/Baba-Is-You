#include "model/game.hpp"

#include "model/entity.hpp"
#include <vector>

Game::Game(int w, int h): height{h}, width{w}, grid{new std::vector<Entity*>*[h]} {
  for (int i = 0; i < h; i++) {
    grid[i] = new std::vector<Entity*>[w];
  }
}

Game::~Game() {
  for (int i = 0; i < height; i++) delete[] grid[i];
  delete[] grid;
}
