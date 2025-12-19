#include "model/util.hpp"

#include <stdexcept>

#include "model/entity.hpp"

coordinates next(coordinates cds, Direction d) {
  switch (d) {
    case Direction::Right: return {cds.first, cds.second + 1};
    case Direction::Left:  return {cds.first, cds.second - 1};
    case Direction::Up:    return {cds.first - 1, cds.second};
    case Direction::Down:  return {cds.first + 1, cds.second};
    default: throw std::logic_error("Unknown direction");
  }
}

Block::Block(Direction d, Entity *e): d{d}, e{e} {}

bool Block::operator==(const Block &other) {
  return d == other.d && e == other.e;
}
