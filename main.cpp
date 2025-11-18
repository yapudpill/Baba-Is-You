#include <iostream>

#include "model/basic_entity.hpp"
#include "model/entity.hpp"
#include "model/game.hpp"
#include "model/ref_entity.hpp"
#include "model/operator.hpp"
#include "model/property.hpp"

void display_grid(Game &g);
int main() {
  Game g{"resource/level/level1"};

  BasicEntity::BABA.addProp(Property::YOU);
  display_grid(g);

  g.move(Direction::Right);
  display_grid(g);
}

void display_grid(Game &g) {
  for(int i = 0; i < g.getHeight(); i++) {
    for(int j = 0; j < g.getWidth(); j++) {
      if(g[{i, j}].empty()) {
          std::cout << "." ;
      } else {
        for (Entity* e : g[{i, j}]) {
          if (dynamic_cast<Property*>(e)) {
              std::cout << "P" ;
          } else if (dynamic_cast<Operator*>(e)) {
            std::cout << "O" ;
          } else if (dynamic_cast<RefEntity*>(e)) {
            std::cout << "N" ;
          } else if (dynamic_cast<BasicEntity*>(e)) {
            std::cout << "E" ;
          }
        }
      }
      std::cout << " " ;
    }
    std::cout << std::endl;
  }
}
