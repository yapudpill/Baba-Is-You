#ifndef ACTION_HPP
#define ACTION_HPP

#include "model/util.hpp"

class Action {
  public:
    Action() = default;
    Action(bool move);
    Action(local_blocks added, local_blocks removed);
    Action operator+(const Action &other);
    Action &operator+=(const Action &other);

    // conversion implicite vers bool "if (a) {...}"
    operator bool() const { return move; }
    local_blocks toAdd() const { return added; }
    local_blocks toRemove() const { return removed; }
    Action reverse() const;
    bool empty() const;

  private:
    bool move = true;
    local_blocks added, removed;
};

#endif // ACTION_HPP
