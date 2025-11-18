#ifndef GAME_HPP
#define GAME_HPP

#include <utility>
#include <vector>

#include "model/action.hpp"
#include "model/entity.hpp"
#include "model/util.hpp"
#include "model/property.hpp"

/** Master class of the model */
class Game final {
  public:
    using cell = std::vector<Entity*>;

    const int height, width;
    Game(int h, int w);
    ~Game();

    std::vector<std::pair<coordinates, Entity*>> operator[](Property &p) const;

    cell **grid;


    Action moveAction(Direction d) const;
    void applyAction(Action a);
    void move(Direction d);

  private:
    bool inBounds(coordinates cds) const;
};

#endif // GAME_HPP
