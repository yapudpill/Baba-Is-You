#include "model/history.hpp"

#include "model/action.hpp"

void History::registerAction(Action a) {
  undo.push_front(a.reverse());
  redo.clear();
}

Action History::undoAction() {
  if (undo.empty()) return {};

  Action a{undo.front()};
  undo.pop_front();
  redo.push_front(a.reverse());
  return a;
}

Action History::redoAction() {
  if (redo.empty()) return {};

  Action a{redo.front()};
  redo.pop_front();
  undo.push_front(a.reverse());
  return a;
}
