#ifndef ACTION_HPP
#define ACTION_HPP

#include <utility>
#include <vector>

#include "model/entity.hpp"
#include "model/util.hpp"

class Action {
  public:
    Action();
    Action(bool move, std::vector<std::pair<coordinates, Entity*>> added,
                      std::vector<std::pair<coordinates, Entity*>> removed);
    Action operator+(const Action &other);
    Action &operator+=(const Action &other);

    bool canMove() const { return move; }
    std::vector<std::pair<coordinates, Entity*>> toAdd() const { return added; }
    std::vector<std::pair<coordinates, Entity*>> toRemove() const { return removed; }

  private:
    bool move;
    std::vector<std::pair<coordinates, Entity*>> added, removed;
};

#endif // ACTION_HPP
