#ifndef BASIC_HPP
#define BASIC_HPP

#include "model/entity.hpp"

/* A basic entity is one that does nothing except existing. For example Baba,
Rock, Water... */
class BasicEntity: public Entity {
  public:
    static BasicEntity BABA, ROCK, WALL, FLAG;

  private:
    BasicEntity() = default;
};

#endif // BASIC_HPP
