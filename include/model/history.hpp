#ifndef HISTORY_HPP
#define HISTORY_HPP

#include <deque>

#include "model/action.hpp"

class History {
  public:
    void registerAction(Action a);
    Action undoAction();
    Action redoAction();

  private:
    std::deque<Action> undo, redo;
};

#endif // HISTORY_HPP
