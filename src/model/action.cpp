#include "model/action.hpp"

#include <utility>
#include <vector>

#include "model/entity.hpp"
#include "model/util.hpp"

Action::Action(
  bool move,
  std::vector<std::pair<coordinates, Entity*>> added,
  std::vector<std::pair<coordinates, Entity*>> removed
): move{move}, added{added}, removed{removed} {}

Action::Action(): move{true} {}

Action Action::operator+(const Action &other) {
  std::vector<std::pair<coordinates, Entity*>> new_added{added};
  new_added.insert(new_added.end(), other.added.begin(), other.added.end());

  std::vector<std::pair<coordinates, Entity*>> new_removed{removed};
  new_removed.insert(new_removed.end(), other.removed.begin(), other.removed.end());

  return {move && other.move, new_added, new_removed};
}

Action &Action::operator+=(const Action &other) {
  move &= other.move;
  added.insert(added.end(), other.added.begin(), other.added.end());
  removed.insert(removed.end(), other.removed.begin(), other.removed.end());
  return *this;
}
