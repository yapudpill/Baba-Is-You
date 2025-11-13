#include "model/game.hpp"

#include "model/entity.hpp"
#include "model/direction.hpp"
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
void move(Direction d) {
  // fonction appelé avec une **grid
  // regarder chaque vector d'entity et les entity qui ont la propriété YOU -> les ajouter à la case indiquer par la direction
  // une bonne chose serait qu'on indique à move les trucs qui bougent et qu'ils bougent tout les objets du meme type d'un coup sans avoir besoin de faire une boucle
}