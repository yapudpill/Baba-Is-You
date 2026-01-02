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
#include "model/rule_manager.hpp"
#include "model/util.hpp"

const std::map<std::string, Entity*> getEntity {
  {"BABA", &BasicEntity::BABA},
  {"FLAG", &BasicEntity::FLAG},
  {"WALL", &BasicEntity::WALL},
  {"ROCK", &BasicEntity::ROCK},
  {"GRASS", &BasicEntity::GRASS},
  {"TILE", &BasicEntity::TILE},
  {"KEKE", &BasicEntity::KEKE},
  {"KEY", &BasicEntity::KEY},
  {"DOOR", &BasicEntity::DOOR},

  {"&BABA", &RefEntity::NBABA},
  {"&FLAG", &RefEntity::NFLAG},
  {"&WALL", &RefEntity::NWALL},
  {"&ROCK", &RefEntity::NROCK},
  {"&TEXT", &RefEntity::NTEXT},
  {"&GRASS", &RefEntity::NGRASS},
  {"&TILE", &RefEntity::NTILE},
  {"&KEKE", &RefEntity::NKEKE},
  {"&KEY", &RefEntity::NKEY},
  {"&DOOR", &RefEntity::NDOOR},

  {"YOU", &Property::YOU},
  {"WIN", &Property::WIN},
  {"STOP", &Property::STOP},
  {"PUSH", &Property::PUSH},
  {"DEFEAT", &Property::DEFEAT},
  {"MOVE", &Property::MOVE},
  {"OPEN", &Property::OPEN},
  {"SHUT", &Property::SHUT},

  {"IS", &Operator::IS}
};

Game::Game(const std::string &path): rules{grid, win} {
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

        grid(i, j).emplace_back(Direction::Right, it->second);
      }
    }
  }
}

Game &Game::operator=(const Game &other) {
  win = other.win;
  history = other.history;
  grid = other.grid;
  return *this;
}

Game &Game::operator=(Game &&other) {
  win = std::move(other.win);
  history = std::move(other.history);
  grid = std::move(other.grid);
  return *this;
}

const Action &Game::applyAction(const Action &a) {
  if (!a) return a;

  for (local_block to_add : a.toAdd()) {
    grid[to_add.first].push_back(to_add.second);
  }

  for (local_block to_remove : a.toRemove()) {
    // the cell where we have to remove the entity
    Grid::cell &cell = grid[to_remove.first];

    // find the first occurrence of the entity and remove it
    cell.erase(std::find(cell.begin(), cell.end(), to_remove.second));
  }

  return a;
}

void Game::move(Direction d) {
  Action total;

  //--- onEnter ---//
  total += applyAction(rules.update());

  // Moving YOU
  Action you_action;
  for (local_block &to_move : grid[Property::YOU]) {
    to_move.second.d = d;
    Action a = rules.moveAction(to_move.second, to_move.first);
    if (a) you_action += a;
  }
  total += applyAction(you_action);

  // Moving MOVE
  Action move_action;
  for (local_block &to_move : grid[Property::MOVE]) {
    Action a = rules.moveAction(to_move.second, to_move.first);
    if (a.empty()) {
      // If we cannot move, bounce and go in the opposite direction
      Grid::cell &cell = grid[to_move.first];
      Grid::cell::iterator it = std::find(cell.begin(), cell.end(), to_move.second);
      it->d = oppositeDirection(it->d);
    } else {
      move_action += a;
    }
  }
  total += applyAction(move_action);

  //--- onStay ---//
  total += applyAction(rules.update());
  total += applyAction(rules.stayAction());

  history.registerAction(total);
}

void Game::undo() {
  applyAction(history.undoAction());
}

void Game::redo() {
  applyAction(history.redoAction());
}
