#include "model/action.hpp"
#include "model/util.hpp"
#include <utility>

Action::Action(bool do_action): do_action{do_action} {}

Action::Action(local_blocks added,local_blocks removed, bool do_move):
  do_move{do_move}, added{added}, removed{removed} {}

Action Action::operator+(const Action &other) {
  if (!*this || !other) return {false};

  local_blocks new_added{added};
  new_added.insert(new_added.end(), other.added.begin(), other.added.end());

  local_blocks new_removed{removed};
  new_removed.insert(new_removed.end(), other.removed.begin(), other.removed.end());

  return {new_added, new_removed, do_move && other.do_move};
}

Action &Action::operator+=(const Action &other) {
  if (!other) {
    do_action = false;
  } else {
    do_move &= other.do_move;
    added.insert(added.end(), other.added.begin(), other.added.end());
    removed.insert(removed.end(), other.removed.begin(), other.removed.end());
  }
  return *this;
}

Action Action::reverse() const {
  Action copy{*this};
  std::swap(copy.added, copy.removed);
  return copy;
}

bool Action::empty() const {
  return !do_action || (added.empty() && removed.empty());
}
