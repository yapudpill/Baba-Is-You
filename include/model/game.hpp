#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include <vector>

#include "model/action.hpp"
#include "model/entity.hpp"
#include "model/grid.hpp"
#include "model/history.hpp"
#include "model/util.hpp"
#include "model/property.hpp"

/** Master class of the model */
class Game final {
  public:
    using cell = std::vector<Entity*>;

    explicit Game(const std::string &path);

    const Grid &getGrid() const { return grid; }

    Action moveAction(Entity *entity, const coordinates &cds, Direction d);
    Action stayAction();
    void applyAction(const Action &a);
    void move(Direction d);

    void undo();
    void redo();

    void actualiseRegle();
    void clearAll();

    mutable bool win = false;

  private:
    History history;
    Grid grid;
};

#endif // GAME_HPP
