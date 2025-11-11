#ifndef GAME_HPP
#define GAME_HPP

#include <vector>

#include "model/entity.hpp"

/** Master class of the model */
class Game final {
  public:
    const int height, width;
    Game(int h, int w);
    ~Game();
    std::vector<Entity*> **grid;
};

#endif // GAME_HPP
