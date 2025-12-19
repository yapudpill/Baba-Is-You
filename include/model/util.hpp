#ifndef MODEL_UTIL_HPP
#define MODEL_UTIL_HPP

#include <utility>
#include <vector>

#include "model/entity.hpp"

enum class Direction {Right, Left, Up, Down};

using coordinates = std::pair<unsigned, unsigned>;
coordinates next(coordinates cds, Direction d);

class Block {
  public:
    Block(Direction d, Entity *e);

    Direction d;
    Entity *entity() { return e; };
    const Entity *entity() const { return e; }
    void setEntity(Entity *e) { this->e = e; }

    bool operator==(const Block &other);

  private:
    Entity *e;
};

using local_entity = std::pair<coordinates, Block>;
using local_entities = std::vector<local_entity>;

#endif // MODEL_UTIL_HPP
