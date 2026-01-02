#ifndef ACTION_HPP
#define ACTION_HPP

#include "model/util.hpp"

class Action {
  public:
    Action(bool do_action = true);
    Action(local_blocks added, local_blocks removed, bool do_move = true);
    Action &operator+=(const Action &other);

    // conversion implicite vers bool "if (a) {...}"
    explicit operator bool() const { return do_action; }
    local_blocks toAdd() const { return added; }
    local_blocks toRemove() const { return removed; }
    bool doMove() const { return do_move; }
    Action reverse() const;
    bool empty() const;

  private:
    bool do_action = true, do_move = true;
    local_blocks added, removed;
};

Action operator+(const Action &a1, const Action &a2);

#endif // ACTION_HPP
