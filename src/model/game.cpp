#include "model/game.hpp"

#include <algorithm>
#include <vector>

#include "model/action.hpp"
#include "model/entity.hpp"
#include "model/property.hpp"
#include "model/util.hpp"

Game::Game(int w, int h): height{h}, width{w}, grid{new std::vector<Entity*>*[h]} {
  for (int i = 0; i < h; i++) {
    grid[i] = new std::vector<Entity*>[w];
  }
}

Game::~Game() {
  for (int i = 0; i < height; i++) delete[] grid[i];
  delete[] grid;
}

std::vector<std::pair<coordinates, Entity*>> Game::operator[](Property &p) const {
  std::vector<std::pair<coordinates, Entity*>> ret;

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      for (Entity *e : grid[i][j]) {
        if (e->hasProp(p)) {
          ret.push_back({{i, j}, e});
        }
      }
    }
  }

  return ret;
}

// tout doux : à ajouter dans le HPP
Action Game::moveAction(Direction d) const {
  // fonction appelé avec une **grid
  // regarder chaque vector d'entity et les entity qui ont la propriété
  // YOU -> les ajouter à la case indiquer par la direction

  Action a;
  for (std::pair<coordinates, Entity *> truc : (*this)[Property::YOU]) {
    coordinates nxt = next(truc.first, d);
    if (!inBounds(nxt)) break;

    for (Entity *e : grid[nxt.first][nxt.second]) {
      for (const Property *p : e->getProp()) {
        a += p->onEnter(*truc.second, d);
      }
    }
  }

  return a;
}

void Game::applyAction(Action a) {
  if (!a.canMove()) return;

  for (std::pair<coordinates, Entity*> truc : a.toRemove()) {
    // la cellule où on doit retiter l'entité
    cell cell = grid[truc.first.first][truc.first.second];

    // trouver la première occurrence de cette entité
    cell::iterator it = std::find(cell.begin(), cell.end(), truc.second);

    // supprimer l'entité
    cell.erase(it);
  }

  for (std::pair<coordinates, Entity*> truc : a.toAdd()) {
    cell cell = grid[truc.first.first][truc.first.second];
    cell.push_back(truc.second);
  }
}

void Game::move(Direction d) { applyAction(moveAction(d)); }

bool Game::inBounds(coordinates cds) const {
  return
    0 <= cds.first && cds.first < height &&
    0 <= cds.second && cds.second < width;
}