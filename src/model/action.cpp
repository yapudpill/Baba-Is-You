#include "model/action.hpp"

Action::Action(bool move): move{move} {}

Action::Action(local_entities added,local_entities removed):
  move{true}, added{added}, removed{removed} {}

Action Action::operator+(const Action &other) {
  if (!*this || !other) return {false};

  local_entities new_added{added};
  new_added.insert(new_added.end(), other.added.begin(), other.added.end());

  local_entities new_removed{removed};
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
