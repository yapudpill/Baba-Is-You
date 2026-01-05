#ifndef MODEL_UTIL_HPP
#define MODEL_UTIL_HPP

#include <utility>
#include <vector>

#include "model/entity/entity.hpp"

enum class Direction {Right, Left, Up, Down};
Direction oppositeDirection(Direction d);

using coordinates = std::pair<unsigned, unsigned>;
coordinates next(coordinates cds, Direction d);

class Block {
  public:
    Block(Direction d, Entity *e);

    Direction d;
    Entity *entity() { return e; };
    const Entity *entity() const { return e; }
    bool operator==(const Block &other);

  private:
    Entity *e;
};

using local_block = std::pair<coordinates, Block>;
using local_blocks = std::vector<local_block>;

#endif // MODEL_UTIL_HPP
