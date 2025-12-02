#ifndef ACTION_HPP
#define ACTION_HPP

#include "model/util.hpp"

class Action {
  public:
    Action() = default;
    Action(bool move);
    Action(local_entities added, local_entities removed);
    Action operator+(const Action &other);
    Action &operator+=(const Action &other);

    // conversion implicite vers bool "if (a) {...}"
    operator bool() const { return move; }
    local_entities toAdd() const { return added; }
    local_entities toRemove() const { return removed; }

  private:
    bool move = true;
    local_entities added, removed;
};

#endif // ACTION_HPP
