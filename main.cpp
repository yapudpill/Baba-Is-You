#include <iostream>

#include "model/basic_entity.hpp"
#include "model/entity.hpp"
#include "model/game.hpp"
#include "model/noun.hpp"
#include "model/operator.hpp"
#include "model/property.hpp"

int main() {
  Game g{5, 5};
  g.grid[0][0].push_back(&Noun::NBABA);
  g.grid[0][1].push_back(&Operator::IS);
  g.grid[0][2].push_back(&Property::YOU);

  g.grid[3][3].push_back(&BasicEntity::BABA);

  BasicEntity::BABA.addProp(Property::YOU);
  std::cout << BasicEntity::BABA.hasProp(Property::YOU) << "\n";
  BasicEntity::BABA.clearProp();
}
