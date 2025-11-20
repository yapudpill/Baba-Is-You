#include "model/game.hpp"

#include <algorithm>
#include <fstream>
#include <limits>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "model/action.hpp"
#include "model/basic_entity.hpp"
#include "model/entity.hpp"
#include "model/operator.hpp"
#include "model/property.hpp"
#include "model/ref_entity.hpp"
#include "model/util.hpp"

const std::map<std::string, Entity*> getEntity {
  {"BABA", &BasicEntity::BABA},
  {"FLAG", &BasicEntity::FLAG},
  {"WALL", &BasicEntity::WALL},
  {"ROCK", &BasicEntity::ROCK},

  {"&BABA", &RefEntity::NBABA},
  {"&FLAG", &RefEntity::NFLAG},
  {"&WALL", &RefEntity::NWALL},
  {"&ROCK", &RefEntity::NROCK},

  {"YOU", &Property::YOU},
  {"WIN", &Property::WIN},
  {"STOP", &Property::STOP},
  {"PUSH", &Property::PUSH},

  {"IS", &Operator::IS}
};

Game::Game(const std::string &path) {
  std::ifstream file{path};
  if (!file) throw std::runtime_error("Failed to open file: " + path);

  if (!(file >> height >> width))
    throw std::runtime_error("Invalid or missing dimensions");
  // ignore the rest of the first line
  file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  grid = new cell*[height];
  for (int i = 0; i < height; i++) {
    grid[i] = new cell[width];
  }

  std::string tmp;
  for (int i = 0; i < height; i++) {
    if (!std::getline(file, tmp))
      throw std::runtime_error("Row count does not match the declared height");
    std::stringstream row{tmp};

    for (int j = 0; j < width; j++) {
      if (!std::getline(row, tmp, ',') && j != width - 1)
        throw std::runtime_error("Cell count does not match the declared width");
      std::stringstream cell{tmp};

      while (cell >> tmp) {
        std::map<std::string, Entity*>::const_iterator it = getEntity.find(tmp);
        if (it == getEntity.end())
          throw std::runtime_error("Unknown block ID: " + tmp);

        grid[i][j].push_back(it->second);
      }
    }
  }
}

Game::~Game() {
  for (int i = 0; i < height; i++) delete[] grid[i];
  delete[] grid;
}

std::vector<std::pair<coordinates, Entity*>> Game::operator[](const Property &p) const {
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

Game::cell &Game::operator[](const coordinates &cds) const {
  return grid[cds.first][cds.second];
}

Action Game::moveAction(Direction d) const {
  Action a;
  for (std::pair<coordinates, Entity*> to_move : (*this)[Property::YOU]) {
    coordinates nxt = next(to_move.first, d);
    if (!inBounds(nxt)) break;

    a += {true, {{nxt, to_move.second}}, {to_move}};
    for (Entity *e : (*this)[nxt]) {
      for (const Property *p : e->getProp()) {
        a += p->onEnter(*to_move.second, d);
      }
    }
  }
  return a;
}

void Game::applyAction(const Action &a) {
  if (!a.canMove()) return;

  for (std::pair<coordinates, Entity*> to_remove : a.toRemove()) {
    // the cell where we have to remove the entity
    cell &cell = (*this)[to_remove.first];

    // find the first occurrence of the entity and remove it
    cell.erase(std::find(cell.begin(), cell.end(), to_remove.second));
  }

  for (std::pair<coordinates, Entity*> to_add : a.toAdd()) {
    (*this)[to_add.first].push_back(to_add.second);
  }
}

void Game::move(Direction d) { applyAction(moveAction(d)); }

bool Game::inBounds(coordinates cds) const {
  return
    0 <= cds.first && cds.first < height &&
    0 <= cds.second && cds.second < width;
}
