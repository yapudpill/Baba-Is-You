#include "model/game.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>

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

local_entities Game::operator[](const Property &p) const {
  local_entities ret;

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

/* Move entity 'e' currently in cell 'cds' in direction 'd' */
Action Game::moveAction(Entity *moving, const coordinates &cds, Direction d) const {
  coordinates nxt = next(cds, d);
  if (!inBounds(nxt)) return {false};

  Action a{{{nxt, moving}}, {{cds, moving}}};

  // pour chaque entité 'e' sur la case d'arrivée
  for (Entity *receiver : (*this)[nxt]) {
    // pour chaque propriété de l'entité 'e'
    for (const Property *p : receiver->getProp()) {
      // indiquer à la propriété que l'entité 'to_move' entre sur la case
      a += p->onEnter(*moving, d, *receiver, nxt, *this);
    }
  }

  return a;
}

Action Game::stayAction() const {
  Action a;

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      for (Entity *e1 : (*this)[{i, j}]) {
        for (Entity *e2 : (*this)[{i, j}]) {
          for (const Property *p : e2->getProp()) {
            a += p->onStay(*e1);
          }
        }
      }
    }
  }

  if (!a) throw std::logic_error("onStay returned false");

  return a;
};

void Game::applyAction(const Action &a) {
  if (!a) return;

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

void Game::move(Direction d) {
  Action action;
  for (std::pair<coordinates, Entity*> to_move : (*this)[Property::YOU]) {
    Action a = moveAction(to_move.second, to_move.first, d);
    if (a) action += a;
  }
  applyAction(action);


  applyAction(stayAction());
}

bool Game::inBounds(coordinates cds) const {
  return
    0 <= cds.first && cds.first < height &&
    0 <= cds.second && cds.second < width;
}
