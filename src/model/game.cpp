#include "model/game.hpp"

#include "model/entity.hpp"
#include <vector>

Game::Game(int w, int h): height{h}, width{w}, grid{new std::vector<Entity*>*[h]} {
  for (int i = 0; i < h; i++) {
    grid[i] = new std::vector<Entity*>[w];
  }
}

Game::~Game() {
  for (int i = 0; i < height; i++) delete[] grid[i];
  delete[] grid;
}

// tout doux : à ajouter dans le HPP
void Game::move(Direction d) {
  // fonction appelé avec une **grid
  // regarder chaque vector d'entity et les entity qui ont la propriété YOU -> les ajouter à la case indiquer par la direction
  for(int i = 0; i < height; i++) {
      for(int j = 0; j < width; j++) {
          for (Entity* e : grid[i][j]) {
            for(const Property* p : e->getProp()) {
              if(p->onEnter(*e, d)) {
                switch (d)
                {
                case Direction::Right:
                  //enlever e de sa pos et la mettre à droite
                  //grid[i][j].pop_back();
                  grid[i][j+1].push_back(e);
                  break;
                case Direction::Left:
                  //enlever e de sa pos et la mettre à droite
                  break;
                case Direction::Up:
                  //enlever e de sa pos et la mettre à droite
                  break;
                case Direction::Down:
                  //grid[i][j].pop_back();
                  grid[i+1][j].push_back(e);
                  //enlever e de sa pos et la mettre à droite
                  break;
                default:
                  break;
                }
              }
            }
          }
      }
  }
     
}