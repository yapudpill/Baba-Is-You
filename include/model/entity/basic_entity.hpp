#ifndef BASIC_HPP
#define BASIC_HPP

#include <set>

#include "model/entity/entity.hpp"

/* A basic entity is one that does nothing except existing. For example Baba,
Rock, Water... */
class BasicEntity: public Entity {
  public:
    static BasicEntity BABA, ROCK, WALL, FLAG, GRASS, TILE, KEKE, KEY, DOOR;

    bool hasProp(const Property &p) const override;
    void addProp(const Property &p) override;
    void clearProp() override;
    const std::set<const Property*> getProp() const override;

  private:
    std::set<const Property*> properties;
    BasicEntity() = default;
    BasicEntity(const BasicEntity&) = delete;
};

#endif // BASIC_HPP
