#include "model/action.hpp"
#include "model/util.hpp"
#include <utility>

Action::Action(bool move): move{move} {}

Action::Action(local_blocks added,local_blocks removed):
  move{true}, added{added}, removed{removed} {}

Action Action::operator+(const Action &other) {
  if (!*this || !other) return {false};

  local_blocks new_added{added};
  new_added.insert(new_added.end(), other.added.begin(), other.added.end());

  local_blocks new_removed{removed};
  new_removed.insert(new_removed.end(), other.removed.begin(), other.removed.end());

  return {new_added, new_removed};
}

Action &Action::operator+=(const Action &other) {
  if (!other) {
    move = false;
  } else {
    added.insert(added.end(), other.added.begin(), other.added.end());
    removed.insert(removed.end(), other.removed.begin(), other.removed.end());
  }
  return *this;
}

Action Action::reverse() {
  Action copy{*this};
  std::swap(copy.added, copy.removed);
  return copy;
}
