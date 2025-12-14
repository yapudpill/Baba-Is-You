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
  {"GRASS", &BasicEntity::GRASS},
  {"TILE", &BasicEntity::TILE},

  {"&BABA", &RefEntity::NBABA},
  {"&FLAG", &RefEntity::NFLAG},
  {"&WALL", &RefEntity::NWALL},
  {"&ROCK", &RefEntity::NROCK},
  {"&TEXT", &RefEntity::NTEXT},
  {"&GRASS", &RefEntity::NGRASS},
  {"&TILE", &RefEntity::NTILE},

  {"YOU", &Property::YOU},
  {"WIN", &Property::WIN},
  {"STOP", &Property::STOP},
  {"PUSH", &Property::PUSH},

  {"IS", &Operator::IS}
};

Game::Game(const std::string &path) {
  std::ifstream file{path};
  if (!file) throw std::runtime_error("Failed to open file: " + path);

  unsigned height, width;
  if (!(file >> height >> width))
    throw std::runtime_error("Invalid or missing dimensions");
  // ignore the rest of the first line
  file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  grid = {height, width};

  std::string tmp;
  for (unsigned i = 0; i < height; i++) {
    if (!std::getline(file, tmp))
      throw std::runtime_error("Row count does not match the declared height");
    std::istringstream row{tmp};

    for (unsigned j = 0; j < width; j++) {
      if (!std::getline(row, tmp, ',') && j != width - 1)
        throw std::runtime_error("Cell count does not match the declared width");
      std::istringstream cell{tmp};

      while (cell >> tmp) {
        std::map<std::string, Entity*>::const_iterator it = getEntity.find(tmp);
        if (it == getEntity.end())
          throw std::runtime_error("Unknown block ID: " + tmp);

        grid(i, j).push_back(it->second);
      }
    }
  }
}

/* Move entity 'e' currently in cell 'cds' in direction 'd' */
Action Game::moveAction(Entity *moving, const coordinates &cds, Direction d) {
  coordinates nxt = next(cds, d);
  if (!grid.inBounds(nxt)) return {false};

  Action a{{{nxt, moving}}, {{cds, moving}}};

  // pour chaque entité 'e' sur la case d'arrivée
  for (Entity *receiver : grid[nxt]) {
    // pour chaque propriété de l'entité 'e'
    for (const Property *p : receiver->getProp()) {
      // indiquer à la propriété que l'entité 'to_move' entre sur la case
      a += p->onEnter(*moving, d, *receiver, nxt, *this);
    }
  }

  return a;
}

Action Game::stayAction() {
  Action a;

  for (unsigned i = 0; i < grid.getHeight(); i++) {
    for (unsigned j = 0; j < grid.getWidth(); j++) {
      for (Entity *e1 : grid(i, j)) {
        for (Entity *e2 : grid(i, j)) {
          for (const Property *p : e2->getProp()) {
            a += p->onStay(*e1, *this);
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

  for (local_entity to_remove : a.toRemove()) {
    // the cell where we have to remove the entity
    cell &cell = grid[to_remove.first];

    // find the first occurrence of the entity and remove it
    cell.erase(std::find(cell.begin(), cell.end(), to_remove.second));
  }

  for (local_entity to_add : a.toAdd()) {
    grid[to_add.first].push_back(to_add.second);
  }
}

void Game::move(Direction d) {
  Action total;

  actualiseRegle();
  Action move_action;
  for (local_entity to_move : grid[Property::YOU]) {
    Action a = moveAction(to_move.second, to_move.first, d);
    if (a) move_action += a;
  }
  applyAction(move_action);
  total += move_action;

  actualiseRegle();
  Action stay_action{stayAction()};
  applyAction(stay_action);
  total += stay_action;

  history.registerAction(total);
}

void Game::clearAll() {
  for (unsigned i = 0; i < grid.getHeight(); i++) {
    for (unsigned j = 0; j < grid.getWidth(); j++) {
      for (Entity *e : grid(i, j)) {
        e->clearProp();
      }
    }
  }
}

void Game::actualiseRegle() {
  clearAll();
  for (coordinates cds : grid[&Operator::IS]) {

    coordinates left = next(cds, Direction::Left);
    coordinates right = next(cds, Direction::Right);
    coordinates up = next(cds, Direction::Up);
    coordinates down = next(cds, Direction::Down);

    if(grid.inBounds(left) && grid.inBounds(right)) { // horizontal
      RefEntity *a = grid.getRefEntity(left);
      Property *b = grid.getProperty(right);
      if(a && b) a->ref.addProp(*b);
    }

    if(grid.inBounds(up) && grid.inBounds(down)) { // vertical
      RefEntity * a = grid.getRefEntity(up);
      Property * b = grid.getProperty(down);
      if(a && b) a->ref.addProp(*b);
    }
  }
}

void Game::undo() {
  applyAction(history.undoAction());
}

void Game::redo() {
  applyAction(history.redoAction());
}
