#include "model/basic_entity.hpp"

#include "model/property.hpp"

BasicEntity BasicEntity::BABA;
BasicEntity BasicEntity::ROCK;
BasicEntity BasicEntity::FLAG;
BasicEntity BasicEntity::WALL;
BasicEntity BasicEntity::GRASS;
BasicEntity BasicEntity::TILE;
BasicEntity BasicEntity::KEKE;
BasicEntity BasicEntity::KEY;
BasicEntity BasicEntity::DOOR;

bool BasicEntity::hasProp(const Property &p) const {
  return properties.find(&p) != properties.end();
}

void BasicEntity::addProp(const Property &p) {
  properties.insert(&p);
}

void BasicEntity::clearProp() {
  properties.clear();
}

const std::set<const Property*> BasicEntity::getProp() const {
  return properties;
}
