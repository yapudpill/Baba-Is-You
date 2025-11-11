#include "model/basic_entity.hpp"
#include "model/game.hpp"
#include "model/operator.hpp"
#include "model/property.hpp"
#include <iostream>

int main() {
  Game g{5, 5};
  g.grid[0][0].push_back(&BasicEntity::BABA);
  g.grid[0][1].push_back(&Operator::IS);
  g.grid[0][2].push_back(&Property::YOU);

  BasicEntity::BABA.addProperty(Property::YOU);
  std::cout << BasicEntity::BABA.hasProperty(Property::YOU) << "\n";
  BasicEntity::BABA.delProperty(Property::YOU);
}
