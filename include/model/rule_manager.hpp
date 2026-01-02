#ifndef RULE_MANAGER_HPP
#define RULE_MANAGER_HPP

#include "model/action.hpp"
#include "model/grid.hpp"
#include "model/util.hpp"

class RuleManager {
  public:
    RuleManager(Grid &grid, bool &win);
    Action update();
    Action stayAction();
    Action moveAction(Block &moving, const coordinates &cds);
    void setWin() { winFlag = true; }

  private:
    Grid &grid;
    bool &winFlag;
    void clear();
    Action updateDirection(const coordinates &cds, Direction d1, Direction d2);
};

#endif // RULE_MANAGER_HPP
