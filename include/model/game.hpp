#ifndef GAME_HPP
#define GAME_HPP

#include <vector>

#include "model/entity.hpp"
#include "model/direction.hpp"
#include "model/property.hpp"

/** Master class of the model */
class Game final {
  public:
    const int height, width;
    Game(int h, int w);
    ~Game();
    std::vector<Entity*> **grid;

    void move(Direction d);
};

#endif // GAME_HPP
