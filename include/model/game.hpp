#ifndef GAME_HPP
#define GAME_HPP

#include <string>

#include "model/action.hpp"
#include "model/entity/property.hpp"
#include "model/grid.hpp"
#include "model/history.hpp"
#include "model/rule_manager.hpp"
#include "model/util.hpp"

/** Master class of the model */
class Game final {
  public:
    explicit Game(const std::string &path);
    Game &operator=(const Game &other);
    Game &operator=(Game &&other);

    const Grid &getGrid() const { return grid; }
    bool isWin() const { return win; }
    void move(Direction d);
    void undo();
    void redo();

  private:
    bool win = false;
    History history;
    Grid grid;
    RuleManager rules;
    const Action &applyAction(const Action &a);
};

#endif // GAME_HPP
