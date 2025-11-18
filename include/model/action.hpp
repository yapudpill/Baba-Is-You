#ifndef ACTION_HPP
#define ACTION_HPP

#include "model/entity.hpp"
#include "model/util.hpp"
#include <utility>
#include <vector>
class Action {
  public:
    Action operator+(const Action &other);
    Action &operator+=(const Action &other);
    bool canMove;

  public:
    std::vector<std::pair<coordinates, Entity*>> added, removed;
};

#endif // ACTION_HPP
