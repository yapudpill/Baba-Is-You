#include <iostream>

#include "model/basic_entity.hpp"
#include "model/entity.hpp"
#include "model/game.hpp"
#include "model/noun.hpp"
#include "model/operator.hpp"
#include "model/property.hpp"

/*void display_grid(Game &g);
int main() {
  Game g{5, 5};
  g.grid[0][0].push_back(&Noun::NBABA);
  g.grid[0][1].push_back(&Operator::IS);
  g.grid[0][2].push_back(&Property::YOU);

  g.grid[3][3].push_back(&BasicEntity::BABA);

  BasicEntity::BABA.addProp(Property::YOU);
  //std::cout << BasicEntity::BABA.hasProp(Property::YOU) << "\n";
  display_grid(g);
  g.move(Direction::Right);
  display_grid(g);
  BasicEntity::BABA.clearProp();
}

void display_grid(Game &g) {
    for(int i = 0; i < g.height; i++) {
      for(int j = 0; j < g.width; j++) {
        if(g.grid[i][j].empty()) {
            std::cout << "." ;
        }
        else {
          for (Entity* e : g.grid[i][j]) {
            if (Property *p = dynamic_cast<Property*>(e)) {
               std::cout << "P" ;
            }
            if (Operator *p = dynamic_cast<Operator*>(e)) {
              std::cout << "O" ;
            }
            if (Noun *p = dynamic_cast<Noun*>(e)) {
              std::cout << "N" ;
            }
          }
        }
        std::cout << " " ;
      }
      std::cout << std::endl;
    }
}*/