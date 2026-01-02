#include "model/rule_manager.hpp"

#include <vector>

#include "model/action.hpp"
#include "model/grid.hpp"
#include "model/operator.hpp"
#include "model/property.hpp"
#include "model/ref_entity.hpp"
#include "model/util.hpp"

RuleManager::RuleManager(Grid &grid, bool &win): grid{grid}, winFlag{win} {}

void RuleManager::clear() {
  for (unsigned i = 0; i < grid.getHeight(); i++) {
    for (unsigned j = 0; j < grid.getWidth(); j++) {
      for (Block &b : grid(i, j)) {
        b.entity()->clearProp();
      }
    }
  }
}

Action RuleManager::update() {
  clear();

  Action act;
  for (const coordinates &cds : grid[&Operator::IS]) {
    act += updateDirection(cds, Direction::Left, Direction::Right);
    act += updateDirection(cds, Direction::Up, Direction::Down);
  }

  return act;
}

Action RuleManager::updateDirection(const coordinates &cds, Direction d1, Direction d2) {
  Action act;
  coordinates cds1 = next(cds, d1);
  coordinates cds2 = next(cds, d2);

  std::vector<RefEntity*> refs1 = grid.getCast<RefEntity>(cds1);
  std::vector<RefEntity*> refs2 = grid.getCast<RefEntity>(cds2);
  std::vector<Property*> props = grid.getCast<Property>(cds2);

  for (RefEntity *r1 : refs1) {

    // Rule of the form BABA IS YOU
    for (Property *p : props) r1->ref.addProp(*p);

    // Rule of the form BABA IS WALL
    for (RefEntity *r2 : refs2) {
      for (unsigned i = 0; i < grid.getHeight(); i++) {
        for (unsigned j = 0; j < grid.getWidth(); j++) {
          for (const Block &b : grid(i, j)) {
            if (b.entity() == &r1->ref) {
              act += {{{{i, j}, {b.d, &r2->ref}}}, {{{{i, j}, {b.d, &r1->ref}}}}};
            }
          }
        }
      }
    }
  }

  return act;
}

Action RuleManager::stayAction() {
  Action a;

  for (unsigned i = 0; i < grid.getHeight(); i++) {
    for (unsigned j = 0; j < grid.getWidth(); j++) {
      for (Block &staying : grid(i, j)) {
        for (Block &receiver : grid(i, j)) {
          for (const Property *p : receiver.entity()->getProp()) {
            a += p->onStay(staying, receiver, {i, j}, *this);
          }
        }
      }
    }
  }

  return a;
}

// Move block moving which is currently in position cds
Action RuleManager::moveAction(Block &moving, const coordinates &cds) {
  coordinates nxt = next(cds, moving.d);
  if (!grid.inBounds(nxt)) return false;

  Action act;

  // For each receiving block...
  for (Block &receiver : grid[nxt]) {
    // ...for each property of the receiving block...
    for (const Property *p : receiver.entity()->getProp()) {
      // ...indicate to the property that the moving entity is wishing to enter
      act += p->onEnter(moving, receiver, nxt, *this);
    }
  }

  if (act.doMove()) act += {{{nxt, moving}}, {{cds, moving}}};

  return act;
}
