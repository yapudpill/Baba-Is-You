#include "model/basic_entity.hpp"
#include "model/game.hpp"
#include "model/operator.hpp"
#include "model/property.hpp"

int main() {
  Game g{5, 5};
  g.grid[0][0].push_back(&BasicEntity::BABA);
  g.grid[0][1].push_back(&Operator::IS);
  g.grid[0][2].push_back(&Property::YOU);

}
