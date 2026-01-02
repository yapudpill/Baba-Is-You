#ifndef GAME_HPP
#define GAME_HPP

#include <string>

#include "model/action.hpp"
#include "model/grid.hpp"
#include "model/history.hpp"
#include "model/rule_manager.hpp"
#include "model/util.hpp"
#include "model/property.hpp"

/** Master class of the model */
class Game final {
  public:
    explicit Game(const std::string &path);
    Game &operator=(const Game &other);
    Game &operator=(Game &&other);

    const Grid &getGrid() const { return grid; }
    void move(Direction d);
    void undo();
    void redo();

    bool win = false;
  private:
    History history;
    Grid grid;
    RuleManager rules;
    const Action &applyAction(const Action &a);
};

#endif // GAME_HPP
